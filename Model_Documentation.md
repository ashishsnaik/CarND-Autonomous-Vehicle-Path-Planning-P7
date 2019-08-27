# **Autonomous Vehicle Path Planning for Highway Driving - Model Documentation**
---
[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

[//]: # (Image References)
[image0]: ./images/spline_diagram.jpeg "Spline Diagram"
[image1]: ./images/113_miles.png "133 Miles"
[image2]: ./images/112_miles_efficiency_2_lane_change.png "Efficiency Lane Change"
[image3]: ./images/103_miles_lane_change.png "Long Spline Lane Change"
[image4]: ./images/short_spline_lane_change.png "Long Spline Lane Change"

## Project Goals
---
My goal in this project is to implement a Path Planning algorithm for an Autonomous Vehicle driving on a 3-Lane Highway, using C++.

The self-driving car should:
1. Safely navigate around a virtual highway with other traffic that is driving +-10 MPH of the 50 MPH speed limit.
2. Drive as close as possible to the 50 MPH speed limit, which means passing slower traffic when possible keeping in mind that other cars will try to change lanes too. 
3. Avoid hitting other cars at all cost as well as drive inside of the marked road lanes at all times, unless going from one lane to another. 
4. Be able to make one complete loop around the 6946m highway. Since the car is trying to go 50 MPH, it should take a little over 5 minutes to complete 1 loop. 
5. Not experience total acceleration over 10 m/s^2 and jerk that is greater than 10 m/s^3.

## Project Setup
---
The project uses a Udacity Simulator, which provides the following inputs to the C++ program:
1. Map of the highway (sparse list of waypoints).
2. Localization data.
3. Sensor Fusion data

Details of the Simulator and input data are provided in the later sections of this README file.

* Number of Highway Lanes (each side): 3
* Speed Limit: 50 MPH
* Vehicle Position Update Interval: 20 ms

## Source Code
---
All the source code resides in the [Src](./src/) folder and my path planning code resides within the [main.cpp](./src/main.cpp) and [helpers.h](./src/helpers.h), which contains the helper functions. The only external library used by the code is the [Spline Library](./src/spline.h), for generating smooth trajectories.

## Implementation Details
---

At a high level, the path planning algorithm considers  Safety, comfort, efficiency

The vehicle (car) operates as a finite state machine (FSM) with three possible states, Keep-Lane (KL), Lane-Change-Left (LCL), and Lane-Change-Right (LCR), with Keep-Lane (KL) being the default state.

Based on the sensor fusion (localization) data, the car constantly scans the traffic and tries to identifies six key vehicles on the road - the closest vehicle ahead, the closest vehicle behind, in all the three lanes ([main.cpp](./src/main.cpp) *ln 161-250*). The navigation decisions such as follow lane, speed-up, slow-down, change lane, etc, are based on this scan results ([main.cpp](./src/main.cpp) *ln 273-430*). The decision to keep or change lane is based on two conditions:

1. is our car following the vehicle in front too close? 
2. is there a more efficient lane to be in

Another lane is considered an efficiency lane, if we are within a certain distance (100m for now) from the front vehicle and the other lane is more vacant ([main.cpp](./src/main.cpp) *ln 282-316*). The 'following too close' condition checks whether we are following at at-least a minimum safe distance (fn: 'IsVehicleInFrontTooClose(...)' [helpers.h](./src/helpers.h) *ln 163-208*).

### Collision and Speed Control

The car tries to maintain the highest possible speed (below 50 MPH speed limit) that is safe in case closely following a vehicle and is unable to change lanes due to traffic. Curently, lane changes are done only when there is a sufficient enough gap (pre-defined) between the front and rear vehicles in the new lane as defined by the constants `kMinLaneChangeDistanceFront` and `kMinLaneChangeDistanceRear` ([main.cpp](./src/main.cpp) *ln 44,45*). In the later versions of the code, these would be variable, based on the speeds of those vehicles.

### Prediction
When predicting trajectories for other traffic vehicles, currently the planner assumes that the vehicles will progress in their lanes with constant velocities ([main.cpp](./src/main.cpp) *ln 191*).

### Trajectory Generation

Trajectory Generation is done using the external [Spline Library](./src/spline.h) and the code can be found in ([main.cpp](./src/main.cpp) *ln 433-592*). 

To generate the path, the planner defines a spline with 5 points, 2 points at the current car position followed by 3 evenly and sparsely spaced points, defined by the `spline_points_spacing` variable ([main.cpp](./src/main.cpp) *ln 60*). These points are in the XY-coordinate system.

Before feeding the points to the spline, they are transformed such that the origin of the points is shifted to where the car position is and the yaw is rotated to represent the car heading at 0 degrees (x-axis). After that the planner generates N evenly spaced spline points to the spline end such that each point is reached every 0.02sec maintaining the desired constant speed. This is done using the formula N * 0.02 * velocity = d, where d is distance of the target point from the car's current position, as shown below. 

**Spline Diagram**

![alt text][image0]

The spline points are then re-oriented back to the map coordinates before sending those to control module (simulator in this case) as the trajectory.

I used two splines:
1. Short spline: points {30, 60, 90} with target distance 30m
2. Long spline: point {100, 200, 300} with target distance 100m

The planner uses the short spline for normal traffic lane changes ('following too close' condition) and the long spline when doing the efficiency lane change. The long spline smoothens out the tragectory and helps, especially in case the car makes a double lane change to reach the efficiency lane, by keeping the jerk and the normal component (AccN) of the total accleration low.

## Project Results
---

The car's current best drive was 113.81 miles without incident.

### Navigation Screenshot Samples
Below are a few screen shots showing different behaviors of the planner:

113 Miles | Efficiency Double Lane Change
:---------:|:----------:
![][image1]|![][image2]

Long Spline Lane Change | Short Spline Lane Change
:---------:|:----------:
![][image3]|![][image4]

### Navigation Video Sample
*Comming Soon!*

## Forward Looking
---
There are are few things I plan to improve/experiment with for the later versions of the path planner code:

1. Although, with the current implementation, I did not need to implement checks for the jerk and accleration, the next version of the code would make use of them. 
2. The minimum gap between cars in the adjoining lane required for safely lane change is currently constant. To improve the lane change behavior, I plan to dynamically calculate it based on the vehicle speeds.
3. The self-driving car, when, due to unavailability of lane-change, is required to keep following a vehicle closely, could follow the vehicle at a stable speed instead of oscillating.
4. The planner could alternatively experiment using Jerk Minimizing Trajectories (JMT) and Cost Functions for possible improvements in the navigation.