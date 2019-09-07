#include <uWS/uWS.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Eigen-3.3/Eigen/Core"
#include "Eigen-3.3/Eigen/QR"
#include "helpers.h"
#include "json.hpp"
#include "spline.h"

// for convenience
using nlohmann::json;
using std::string;
using std::vector;

// define variable for lane number
// 0 = leftmost (fast) lane. we start in lane 1
// NOTE: we have to define this at a global scope as we are passing it to a lambda function
// which works at global scope and hence can't see local variables
int ego_lane = 1;
int prev_ego_lane = ego_lane;
// reference velocity (set it to zero so the initial
// acceleration jerk is not high when starting from rest)
double ref_vel = 0.0; // mph

// enum defining states of the finite state machine
enum VehicleState {
    KL, // Keep Lane
    LCL, // Lane Change - Left
    LCR // Lane Change - Right
};

VehicleState ego_state = KL;

// macros
#define LEFT_LANE 0
#define CENTER_LANE 1
#define RIGHT_LANE 2

const double kHighPositiveValue = 99999.0;
const double kHighNegativeValue = -99999.0;
// minimum vehicle distances for lane change
const double kMinLaneChangeDistanceFront = kSafeFollowDistance; // meters
const double kMinLaneChangeDistanceRear = -15.0; // meters
// distance from front vehicle where we start checking for a
// better/more efficient lane to change to
const double kEfficiencyLaneChangeDistance = 100.0; // meters
// start of sparse spline points ahead
const int kEfficiencySplineStart_d_High = 100; // meters
const int kEfficiencySplineStart_d_Low = 70; // meters
// (front vehicle distance) threshold to decide which
// spline start point to use (_high or _low) to avoid
// colliding with the front vehicle
const double kSafeEfficiencySplineDistance = 40.0; // meters
// minimum value of spline sparse start point
const int kMinSplineStart_d = 30;
int spline_start_d = kMinSplineStart_d;
// sparse spline point spacing
vector<int> spline_points_spacing = {spline_start_d, spline_start_d*2, spline_start_d*3};
// spline target distance
double spline_target_x = spline_start_d;


int main() {
  uWS::Hub h;

  // Load up map values for waypoint's x,y,s and d normalized normal vectors
  vector<double> map_waypoints_x;
  vector<double> map_waypoints_y;
  vector<double> map_waypoints_s;
  vector<double> map_waypoints_dx;
  vector<double> map_waypoints_dy;

  // Waypoint map to read from
  string map_file_ = "../data/highway_map.csv";
  // The max s value before wrapping around the track back to 0
  double max_s = 6945.554;

  std::ifstream in_map_(map_file_.c_str(), std::ifstream::in);

  string line;
  while (getline(in_map_, line)) {
    std::istringstream iss(line);
    double x;
    double y;
    float s;
    float d_x;
    float d_y;
    iss >> x;
    iss >> y;
    iss >> s;
    iss >> d_x;
    iss >> d_y;
    map_waypoints_x.push_back(x);
    map_waypoints_y.push_back(y);
    map_waypoints_s.push_back(s);
    map_waypoints_dx.push_back(d_x);
    map_waypoints_dy.push_back(d_y);
  }

  h.onMessage([&map_waypoints_x,&map_waypoints_y,&map_waypoints_s,
               &map_waypoints_dx,&map_waypoints_dy]
              (uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length,
               uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {

      auto s = hasData(data);

      if (s != "") {
        auto j = json::parse(s);
        
        string event = j[0].get<string>();
        
        if (event == "telemetry") {
          // j[1] is the data JSON object
          
          // Main car's localization Data
          double car_x = j[1]["x"];
          double car_y = j[1]["y"];
          double car_s = j[1]["s"];
          double car_d = j[1]["d"];
          double car_yaw = j[1]["yaw"];
          double car_speed = j[1]["speed"];

          // Previous path data given to the Planner
          auto previous_path_x = j[1]["previous_path_x"];
          auto previous_path_y = j[1]["previous_path_y"];
          // Previous path's end s and d values 
          double end_path_s = j[1]["end_path_s"];
          double end_path_d = j[1]["end_path_d"];

          // Sensor Fusion Data, a list of all other cars on
          // the same side of the road
          auto sensor_fusion = j[1]["sensor_fusion"];

          json msgJson;

          /**
           * Define a path made up of (x,y) points that the car will visit
           * sequentially every .02 seconds
           */

          // get the previous path size
          // this will be the previous path xy vectors we sent the simulator minus
          // the number of points the simulator has used so far, OR IT COULD BE ZERO initially
          int prev_size = previous_path_x.size();

          // use sensor fusion data to check other cars and their vicinity.
          // this is to avoid collision
          if (prev_size >0) {
            car_s = end_path_s;
          }

          // vectors of vehicles in each lane
          // we only need to track distances and speeds of 6 vehicles: one in front of us,
          // one in our rear, in all the 3 lanes
          vector<vector<double>> closest_vehicles_lane0 {{-1, kHighNegativeValue, kHighPositiveValue},
                                                         {-1, kHighPositiveValue, kHighPositiveValue}};
          vector<vector<double>> closest_vehicles_lane1 {{-1, kHighNegativeValue, kHighPositiveValue},
                                                         {-1, kHighPositiveValue, kHighPositiveValue}};
          vector<vector<double>> closest_vehicles_lane2 {{-1, kHighNegativeValue, kHighPositiveValue},
                                                         {-1, kHighPositiveValue, kHighPositiveValue}};

          double closest_vehicle_dist_front_lane0 = kHighPositiveValue;
          double closest_vehicle_dist_rear_lane0 = kHighNegativeValue;
          double closest_vehicle_dist_front_lane1 = kHighPositiveValue;
          double closest_vehicle_dist_rear_lane1 = kHighNegativeValue;
          double closest_vehicle_dist_front_lane2 = kHighPositiveValue;
          double closest_vehicle_dist_rear_lane2 = kHighNegativeValue;

          // check whether there is a vehicle in our lane.
          // sensor fusion input data format for each vehicle is:
          // [id, x, y, vx, vy, s, d]
          for (unsigned int i = 0; i < sensor_fusion.size(); ++i) {

            vector<double> current_vehicle = sensor_fusion[i];

            double vehicle_d = current_vehicle[6];
            double vehicle_s = current_vehicle[5];
            double vx = current_vehicle[3];
            double vy = current_vehicle[4];
            double vehicle_speed = sqrt(vx*vx + vy*vy);
            double vehicle_id = current_vehicle[0];

            // project the vehicles s value using the previous path points
            // (assuming constant velocity)
            vehicle_s += ((double)prev_size * 0.02 * vehicle_speed);

            double vehicle_dist_from_ego = (vehicle_s - car_s);

            // id, distance from ego vehicle, speed
            vector<double> current_vehicle_info = {vehicle_id, vehicle_dist_from_ego, vehicle_speed};

            // now scan for vehicles in each lane
            // we are also checking whether the vehicle is between lanes (on a lane line),
            // ex.: if the vehicle's d is less than 3.0 it's in lane 0, but if d is between
            // 3.0 and 5.0, then its in both lane 0 and lane 1.
            // this will accommodate for vehicles changing lanes in front of us.
            // (Assumption: vehicle width is 2 units)

            if (vehicle_d < 5.0) { // in lane 0 fully or partially
              // closest behind?
              if (vehicle_dist_from_ego < 0 && vehicle_dist_from_ego > closest_vehicle_dist_rear_lane0) {
                closest_vehicle_dist_rear_lane0 = vehicle_dist_from_ego;
                closest_vehicles_lane0[0] = current_vehicle_info;
              }
              // closest in front?
              if (vehicle_dist_from_ego >= 0 && vehicle_dist_from_ego < closest_vehicle_dist_front_lane0) {
                closest_vehicle_dist_front_lane0 = vehicle_dist_from_ego;
                closest_vehicles_lane0[1] = current_vehicle_info;
              }
            }

            if (vehicle_d > 3.0 && vehicle_d < 9.0) { // in lane 1 fully or partially, is it the closest?
              // closest behind?
              if (vehicle_dist_from_ego < 0 && vehicle_dist_from_ego > closest_vehicle_dist_rear_lane1) {
                closest_vehicle_dist_rear_lane1 = vehicle_dist_from_ego;
                closest_vehicles_lane1[0] = current_vehicle_info;
              }
              // closest in front?
              if (vehicle_dist_from_ego >= 0 && vehicle_dist_from_ego < closest_vehicle_dist_front_lane1) {
                closest_vehicle_dist_front_lane1 = vehicle_dist_from_ego;
                closest_vehicles_lane1[1] = current_vehicle_info;
              }
            }

            if (vehicle_d > 7.0) { // in lane 2 fully or partially, is it the closest?
              // closest behind?
              if (vehicle_dist_from_ego < 0 && vehicle_dist_from_ego > closest_vehicle_dist_rear_lane2) {
                closest_vehicle_dist_rear_lane2 = vehicle_dist_from_ego;
                closest_vehicles_lane2[0] = current_vehicle_info;
              }
              // closest in front?
              if (vehicle_dist_from_ego >= 0 && vehicle_dist_from_ego < closest_vehicle_dist_front_lane2) {
                closest_vehicle_dist_front_lane2 = vehicle_dist_from_ego;
                closest_vehicles_lane2[1] = current_vehicle_info;
              }
            }
          } // sensor fusion

          // maintain a vector of vehicles closest front and rear vehicles in each lane
          // idx 0 = lane 0 etc.
          vector<vector<vector<double>>> non_ego_vehicles;
          non_ego_vehicles.push_back(closest_vehicles_lane0);
          non_ego_vehicles.push_back(closest_vehicles_lane1);
          non_ego_vehicles.push_back(closest_vehicles_lane2);

          // verbose for debugging...
          std::cout << std::endl << "***" << std::endl;
          std::cout << "Ego car lane: " << ego_lane << std::endl;

          std::cout << std::endl << "Closest Non-ego Vehicles: ";
          for (unsigned int i = 0; i < non_ego_vehicles.size(); ++i){

            vector<vector<double>> other_lane = non_ego_vehicles[i];

            std::cout << std::endl << "Lane " << i << ":" << std::endl;

            for (unsigned int j = 0; j < other_lane.size(); ++j) {
              vector<double> info = other_lane[j];
              string vehicle_location = (j == 0) ? "(Rear)  " : "(Front) ";
              std::cout << vehicle_location << "id: " << info[0] << " dist: " << info[1] << " vel: " << info[2];
              std::cout << std::endl;
            }
          }

          std::cout << std::endl;

          // flag set, if we are too close behind a car in the same lane
          bool following_too_close = IsVehicleInFrontTooClose(ego_lane, car_s,
                                                              car_speed, non_ego_vehicles);

          // if we are within a certain distance behind a vehicle, we also scan the other
          // two lanes to check whether there is a more vacant lane we might want to move to
          bool efficiency_lane_change = false;
          double front_vehicle_distance = non_ego_vehicles[ego_lane][1][1];

          if (front_vehicle_distance < kEfficiencyLaneChangeDistance) {

            vector<int> lanes_to_scan = {(ego_lane + 1) % 3, (ego_lane + 2) % 3};
            std::cout << "Lanes to scan: " << lanes_to_scan[0] << ", " << lanes_to_scan[1] << std::endl;

            bool effiency_lane_available = false;
            bool center_lane_clear = true;

            for (unsigned int i = 0; i < lanes_to_scan.size(); ++i) {
              int lane_number = lanes_to_scan[i];
              // if any of the other lanes has a vehicle at least twice farther
              // away then the front vehicle in current lane, change lanes
              if ((non_ego_vehicles[lane_number][1][1] > 2.0*non_ego_vehicles[ego_lane][1][1]) &&
                  (non_ego_vehicles[lane_number][0][1] <= kMinLaneChangeDistanceRear)) {
                effiency_lane_available = true;
                std::cout << "Lane " << lane_number << "... Efficiency lane available... \t ";
              }

              // if we are in the side lane, ensure that the middle lane is free in case
              // the free lane is on the other end (this is also done in the lane-change
              // states, but could cause wiggling of the car if not ensured here)
              if (ego_lane != CENTER_LANE &&
                  (non_ego_vehicles[CENTER_LANE][0][1] > kMinLaneChangeDistanceRear ||
                  non_ego_vehicles[CENTER_LANE][1][1] < kMinLaneChangeDistanceFront)) {
                center_lane_clear = false;
              }

              if (effiency_lane_available && center_lane_clear) {
                std::cout << "Center lane clear..."<< std::endl;
                efficiency_lane_change = true;
                std::cout << "Change Lanes!"<< std::endl;
                break;
              }
            }
          }

          // finite state machine
          switch(ego_state) {

          case KL: // Keep Lane

            if (efficiency_lane_change || following_too_close) {

              // check whether we can change lane, and we change to a lane
              // only if the vehicles in front and rear in the target lane
              // are at safe distances from us
              if (ego_lane == LEFT_LANE ) { // we are in left-most lane

                if (closest_vehicles_lane1[0][1] <= kMinLaneChangeDistanceRear &&
                    closest_vehicles_lane1[1][1] >= kMinLaneChangeDistanceFront) {
                  // move to center-lane (lane 1)
                  ego_state = LCR;
                }
              } else if (ego_lane == RIGHT_LANE) { // we are in right-most lane
                if (closest_vehicles_lane1[0][1] <= kMinLaneChangeDistanceRear &&
                    closest_vehicles_lane1[1][1] >= kMinLaneChangeDistanceFront) {
                  // move to center lane (lane 1)
                  ego_state = LCL;
                }

              } else if (ego_lane == CENTER_LANE) { // we are in the center lane
                // check whether both left and right lanes are available to change to
                // if both lanes are available
                //    move to the lane in which the vehicle we would be following is quite farther ahead than
                //    the one in other lane, if vehicles in both lanes are not quite apart, laterally, we move
                //    to the lane in which the vehicle is moving faster.
                // else move to the lane that is available (if one is)

                VehicleState next_ego_state = ego_state;

                bool LCL_available = false;
                bool LCR_available = false;

                double left_lane_front_vehicle_distance = closest_vehicles_lane0[1][1];
                double left_lane_front_vehicle_speed = closest_vehicles_lane0[1][2];
                double right_lane_front_vehicle_distance = closest_vehicles_lane2[1][1];
                double right_lane_front_vehicle_speed = closest_vehicles_lane2[1][2];

                double left_ahead_of_right_distance = left_lane_front_vehicle_distance -
                                                      right_lane_front_vehicle_distance;

                // if there is sufficient gap in the left lane, mark it as available
                if (closest_vehicles_lane0[0][1] <= kMinLaneChangeDistanceRear &&
                    closest_vehicles_lane0[1][1] >= kMinLaneChangeDistanceFront) {
                  LCL_available = true;
                }
                // if there is sufficient gap in the right lane, mark it as available
                if (closest_vehicles_lane2[0][1] <= kMinLaneChangeDistanceRear &&
                    closest_vehicles_lane2[1][1] >= kMinLaneChangeDistanceFront) {
                  LCR_available = true;
                }

                // if both lanes are available
                if (LCL_available && LCR_available) {
                  // follow lane in which the vehicle in front is farther away
                  if (left_ahead_of_right_distance >= kSafeFollowDistance){
                    next_ego_state = LCL;
                  } else if (left_ahead_of_right_distance <= -kSafeFollowDistance) {
                    next_ego_state = LCR;
                  } else{  // if neither of the vehicles are laterally not far apart, follow the faster one
                           // with preference to the left lane (fast-lane) if speeds are equal.
                    next_ego_state = (left_lane_front_vehicle_speed >= right_lane_front_vehicle_speed) ? LCL : LCR;
                  }
                } else if (LCL_available) {
                  next_ego_state = LCL;
                } else if (LCR_available) {
                  next_ego_state = LCR;
                }
                // else, we will keep in the same lane

                ego_state = next_ego_state;

              } else { // THIS SHOULD NEVER HAPPEN!!
                if (ego_lane < LEFT_LANE){
                  ego_state = LCR; // wrong side of the highway, get out of on-coming traffic asap :-)
                } else {
                  ref_vel -= 1.0; // on the right shoulder, stop soon
                }
              }

              // if we are too close and cannot change lanes, reduce the speed
              if (ego_state == KL && following_too_close) {
                ref_vel -= 0.447;
              }

            } else if (ref_vel < 49.5) {
              ref_vel += 0.447;
            }
            break;
          case LCL: // Lane Change - Left
            // store the previous ego lane
            prev_ego_lane = ego_lane;
            ego_lane = (ego_lane > LEFT_LANE) ? --ego_lane : ego_lane;
            std::cout << "Executing LC-Left" << std::endl;
            ego_state = KL;
            std::cout << "New Ego lane " << ego_lane << "  Prev Ego lane: " << prev_ego_lane  << std::endl << std::endl;
            break;
          case LCR: // Lane Change - Right
            // store the previous ego lane
            prev_ego_lane = ego_lane;
            ego_lane = (ego_lane < RIGHT_LANE) ? ++ego_lane : ego_lane;
            std::cout << "Executing LC-Right" << std::endl;
            ego_state = KL;
            std::cout << "New lane " << ego_lane << "  Prev Ego lane: " << prev_ego_lane  << std::endl << std::endl;
            break;
          default:
            ego_state = KL;
            std::cout << "Default: Keep-Lane..." << std::endl << std::endl;
          }

          //
          // Trajectory Generation Using Splines
          //

          // 1.
          // create a list of widely spaced (x,y) waypoints, evenly spaced at minimum 30m
          // ahead of the current car location, later we will interpolate these waypoints
          // with a spline and fill it in with more points that control speed
          vector<double> ptsx;
          vector<double> ptsy;

          // 2.
          // keep the current car config (x, y, yaw states) as a reference
          // either we will reference the starting point as where the car is or at the previous path end point
          double ref_x = car_x;
          double ref_y = car_y;
          double ref_yaw = deg2rad(car_yaw);

          // 3.
          // here we are going to create 5 widely spaced (x,y) way points, these are going to be 2 points
          // representing the current car position (a tangent to the current car yaw/orientation)
          // and 3 points that are widely spaced at a minimum of 30m distance

          // if the previous list of points has less than 2 points (list is almost empty), use the current
          // car location as the starting reference by creating a tangent (2-points)
          if (prev_size < 2) {

            // use the path that makes tangent to the car position
            double prev_car_x = ref_x - cos(ref_yaw);
            double prev_car_y = ref_y - sin(ref_yaw);

            ptsx.push_back(prev_car_x);
            ptsx.push_back(ref_x);

            ptsy.push_back(prev_car_y);
            ptsy.push_back(ref_y);

          } else { // use the previous path's end points as starting reference

            ref_x = previous_path_x[prev_size-1];
            ref_y = previous_path_y[prev_size-1];

            double ref_x_prev = previous_path_x[prev_size-2];
            double ref_y_prev = previous_path_y[prev_size-2];
            ref_yaw = atan2(ref_y-ref_y_prev, ref_x-ref_x_prev);

            // use two points that male the path tangent to the previous path's end point
            ptsx.push_back(ref_x_prev);
            ptsx.push_back(ref_x);

            ptsy.push_back(ref_y_prev);
            ptsy.push_back(ref_y);

          }

          // 4.
          // now add 3 evenly spaced Frenet points (converted to x,y) to the starting
          // reference we use these points from the current car_s location

          if (efficiency_lane_change) {
            // if in both, the new ego_lane and the current ego_lane, the front vehicle is
            // at least kSafeEfficiencySplineDistance ahead, set the spline base to _High, else
            // to _Low
            if ((non_ego_vehicles[ego_lane][1][1] >= kSafeEfficiencySplineDistance) &&
                (non_ego_vehicles[prev_ego_lane][1][1] >= kSafeEfficiencySplineDistance)){
              spline_start_d = kEfficiencySplineStart_d_High;
            } else {
              spline_start_d = kEfficiencySplineStart_d_Low;
            }
          } else {
            // shrink the spline curve
            if (spline_start_d > kMinSplineStart_d) spline_start_d -= 5;
          }

          spline_points_spacing = {spline_start_d, spline_start_d*2, spline_start_d*3};
          double spline_target_x = spline_start_d;

          vector<double> next_wp0 = getXY((car_s + spline_points_spacing[0]), (2 + 4*ego_lane),
                                          map_waypoints_s, map_waypoints_x, map_waypoints_y);
          vector<double> next_wp1 = getXY((car_s + spline_points_spacing[1]), (2 + 4*ego_lane),
                                          map_waypoints_s, map_waypoints_x, map_waypoints_y);
          vector<double> next_wp2 = getXY((car_s + spline_points_spacing[2]), (2 + 4*ego_lane),
                                          map_waypoints_s, map_waypoints_x, map_waypoints_y);

          std::cout << "Spline points: " << spline_points_spacing[0] << ", " <<
              spline_points_spacing[1] << ", " << spline_points_spacing[2] << std::endl;


          ptsx.push_back(next_wp0[0]);
          ptsx.push_back(next_wp1[0]);
          ptsx.push_back(next_wp2[0]);

          ptsy.push_back(next_wp0[1]);
          ptsy.push_back(next_wp1[1]);
          ptsy.push_back(next_wp2[1]);

          // 5.
          // now we shift the origin to where the car position is and rotate the yaw such
          // that the car is heading at 0 degrees.
          // this is to generate N (=50 here) evenly spaced spline points to 90m such that
          // each point is reached every 0.02sec maintaining constant speed at ref speed
          // i.e. make sure that the last point of the previous path is as (0,0) and
          // angles at 0 degrees and the spline points are created with that reference.
          // we will re-orient the spline points back to map coordinates before sending
          // those to control module (simulator in this case)

          for (unsigned int i = 0; i < ptsx.size(); ++i) {
           // shift car reference angle to 0 degrees
           double shift_x = ptsx[i] - ref_x;
           double shift_y = ptsy[i] - ref_y;

           ptsx[i] = (shift_x * cos(0 - ref_yaw) - shift_y * sin(0 - ref_yaw));
           ptsy[i] = (shift_x * sin(0 - ref_yaw) + shift_y * cos(0 - ref_yaw));
          }

          // create a spline
          tk::spline s;

          // set (x,y) points to the spline
          s.set_points(ptsx, ptsy);

          // define the actual (x,y) points we will use for the planner
          vector<double> next_x_vals;
          vector<double> next_y_vals;

          // start with all the previous path points we have from last time
          for (unsigned int i = 0; i < previous_path_x.size(); ++i) {
           next_x_vals.push_back(previous_path_x[i]);
           next_y_vals.push_back(previous_path_y[i]);
          }

          // calculate how to break up the spline points so we travel at out desired
          // reference speed
          double target_x = spline_target_x;
          double target_y = s(target_x);
          double target_dist = sqrt((target_x*target_x) + (target_y*target_y));
          double x_add_on = 0;
          std::cout << "Spline Target_X: " << target_x << std::endl;

          // fill in the rest of the values from the spline
          for (unsigned int i = 0; i < 50-previous_path_x.size(); ++i) {

            double N = (target_dist/(0.02*ref_vel/2.24));
            double x_point = x_add_on + (target_x/N);
            double y_point = s(x_point);

            x_add_on = x_point;

            double x_ref = x_point;
            double y_ref = y_point;

            // rotate back to normal after rotating it earlier
            x_point = (x_ref * cos(ref_yaw) - y_ref * sin(ref_yaw));
            y_point = (x_ref * sin(ref_yaw) + y_ref * cos(ref_yaw));

            x_point += ref_x;
            y_point += ref_y;

            next_x_vals.push_back(x_point);
            next_y_vals.push_back(y_point);
          }

          msgJson["next_x"] = next_x_vals;
          msgJson["next_y"] = next_y_vals;

          auto msg = "42[\"control\","+ msgJson.dump()+"]";

          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code,
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}
