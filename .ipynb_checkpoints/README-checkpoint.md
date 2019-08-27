# **Autonomous Vehicle Path Planning for Highway Driving**
---
**Self-Driving Car Engineer Nanodegree Program**

[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

[//]: # (Image References)
[image0]: ./images/113_miles_best.png "113 Miles Best"
[image1]: ./images/112_miles_efficiency_2_lane_change.png "Efficiency Lane Change"

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
3. Sensor Fusion data.

Details of the Simulator and the Input Data are provided in the later sections of this README file.

## Project Implementation Details
---
Project implementation details can be found in a separate [Model_Documentation.md](./Model_Documentation.md) markdown file.

## Project Result
---

The car's current best drive was 113.81 miles without incident.

The following screenshots show the car's current best drive result and it making an "Efficiency" Double Lane Change, using a target distance of 100m on a spline with sparse forward-looking points at {100m, 200m, 300m}.

113.81 Current Best | Efficiency Lane Change
:---------:|:----------:
![][image0]|![][image1]

More images with different maneuvers can be found in the project implementation document [Model_Documentation.md](./Model_Documentation.md)

## Simulator
---
You can download the Term3 Simulator which contains the Path Planning Project from the releases tab (https://github.com/udacity/self-driving-car-sim/releases/tag/T3_v1.2).

To run the simulator on Mac/Linux, first make the binary file executable with the following command:
```shell
sudo chmod u+x {simulator_file_name}
```
## Input Data
---
### The map of the highway is in data/highway_map.txt
Each waypoint in the list contains  [x,y,s,dx,dy] values. x and y are the waypoint's map coordinate position, the s value is the distance along the road to get to that waypoint in meters, the dx and dy values define the unit normal vector pointing outward of the highway loop.

The highway's waypoints loop around so the frenet s value, distance along the road, goes from 0 to 6945.554.


Here is the data provided from the Simulator to the C++ Program

### Main car's localization Data (No Noise)

["x"] The car's x position in map coordinates

["y"] The car's y position in map coordinates

["s"] The car's s position in frenet coordinates

["d"] The car's d position in frenet coordinates

["yaw"] The car's yaw angle in the map

["speed"] The car's speed in MPH

### Previous path data given to the Planner

//Note: Return the previous list but with processed points removed, can be a nice tool to show how far along
the path has processed since last time. 

["previous_path_x"] The previous list of x points previously given to the simulator

["previous_path_y"] The previous list of y points previously given to the simulator

### Previous path's end s and d values 

["end_path_s"] The previous list's last point's frenet s value

["end_path_d"] The previous list's last point's frenet d value

### Sensor Fusion Data, a list of all other car's attributes on the same side of the road. (No Noise)

["sensor_fusion"] A 2d vector of cars and then that car's [car's unique ID, car's x position in map coordinates, car's y position in map coordinates, car's x velocity in m/s, car's y velocity in m/s, car's s position in frenet coordinates, car's d position in frenet coordinates. 

### Details

1. The car uses a perfect controller and will visit every (x,y) point it recieves in the list every .02 seconds. The units for the (x,y) points are in meters and the spacing of the points determines the speed of the car. The vector going from a point to the next point in the list dictates the angle of the car. Acceleration both in the tangential and normal directions is measured along with the jerk, the rate of change of total Acceleration. The (x,y) point paths that the planner recieves should not have a total acceleration that goes over 10 m/s^2, also the jerk should not go over 50 m/s^3. (NOTE: As this is BETA, these requirements might change. Also currently jerk is over a .02 second interval, it would probably be better to average total acceleration over 1 second and measure jerk from that.

2. There will be some latency between the simulator running and the path planner returning a path, with optimized code usually its not very long maybe just 1-3 time steps. During this delay the simulator will continue using points that it was last given, because of this its a good idea to store the last points you have used so you can have a smooth transition. previous_path_x, and previous_path_y can be helpful for this transition since they show the last points given to the simulator controller with the processed points already removed. You would either return a path that extends this previous path or make sure to create a new path that has a smooth transition with this last path.

## Basic Build Instructions
---
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./path_planning`.

## Dependencies
---
* cmake >= 3.5
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `install-mac.sh` or `install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```

## Code Style
---
I have did my best to stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).
