# ROS-SLAM Building Map & Navigation
## Introduction
* Motivation

  With the outbreak of the global epidemic and the increasing number of patients, medical resources and manpower are rapidly depleted, and many medical staff are exhausted. Therefore, I want to use the ROS system to simulate SLAM and then put it into physical operation. As the fundation of 【Automatic Disinfection and Patrol Robot】
* SLAM
  
  Matching, error reduction and map construction are achieved through probability statistics and features. There are two SALM practices in two dimensions:
  1. Filter: 
     * Using Kalman filter (KF), Particle filter (PF), etc. First establish a set of robot motion modeling, and then apply KF for state prediction and measurement update. However, since KF is a linear system, it cannot be accurately estimated in actual scenarios. PF does not rely on the equation of motion, and uses large-scale particle points to simulate, which is also used in gmapping of ROS. But the biggest problem is that it cannot deal with large-scale spaces, errors will continue to accumulate, and consistent maps cannot be obtained.
    
  2. Graph optimization (G2O): 
     * It is currently a relatively mainstream solution, relying on the front-end and back-end to do the processing, the front-end obtains the position, and the back-end is responsible for obtaining the optimized position by minimizing observations and residual estimation.

     <img width="441" alt="image" src="https://user-images.githubusercontent.com/73687292/207352657-4a88f300-565d-455d-ba4e-64a84fee296c.png">

## Tools
* **Python & C++**
* **Matlab** is used for IMU error calculation and for plotting 2D and 3D visualizations of data.
* **MobaXterm** is used to run simulations, as there were compatibility issues with Xming.
* **ROS** stands for Robot Operating System.
* **SLAM** - Simultaneous Localization and Mapping
* **URDF - Unified Robot Description Format**, a format used to describe robots where robots are composed of individual components (Links) connected through joints (Joints).
## ROS
### Node
* In essence, there is a workspace (src) containing multiple packages, with each package containing several nodes. Data transmission is achieved using Topics, and each node can be written in different programming languages.
<p align="center">
<img src= https://i.imgur.com/pazDHNG.png width="400px">
</p>

### Topic
* It's somewhat akin to the hashtag mechanism. Nodes can utilize it to publish information about a specific topic, and if there's a node responsible for monitoring that topic, it can receive this information. This is what's referred to as the publisher and subscriber mechanism. The relationship between publishers and subscribers can be one-to-one, one-to-many, many-to-one, or many-to-many because the topic checks who has published new information and who has subscribed to it and then disseminates it.
<p align="center">
<img src= https://i.imgur.com/b8RWHOg.png width="400px">
</p>

* When two nodes are transmitting data through a Topic, they must first agree on the format of this transmission, which means specifying the message type for that Topic. Each Topic needs to define what kind of message type it will use. This can include message types like actionlib_msgs for controlling actions, nav_msgs for navigation, sensor_msgs for sensors, and so on. Some are predefined by others, while you can also define your custom message types.
### Service
* A service corresponds to both a server and a client, and these two entities can communicate through the service. In other words, the client sends a request to the server, and the server then responds with the corresponding response to the client.
<p align="center">
<img src= https://i.imgur.com/cXWHKpS.png width="400px">
</p>

* On the other hand, with topics, the same message is transmitted, essentially what the publisher publishes. However, with services, a set of messages is exchanged, specifically a request and a response. The server responds differently to various requests.
### Launch File
* Some of the self-defined parameters set in the parameter server will disappear when the server is shut down. They won't be present the next time it is opened. This is why launch files exist. These files are used to store default parameters or pre-execution scripts, somewhat similar to shell scripts.
## Pratice & Final Result

### GMAPPING
* Because Gmapping requires actual data for map modeling, Gazebo is needed to allow Rviz to create maps. Directly opening an empty map and using Gazebo's plugins to generate the map is much faster than writing code for it. In the upper-left corner, there are three tools available: Move, Rotate, and Scale.
```shell=
roslaunch turtlebot3_gazebo turtlebot3_empty_world.launch //(自己拉地圖)
python3 spawn_model -urdf -model turtlebot3_$(env TURTLEBOT3_MODEL) -x -2.0 -y -0.5 -z 0.0 -param robot_description
roslaunch turtlebot3_slam turtlebot3_slam.launch slam_methods:=gmapping
roslaunch turtlebot3_gazebo turtlebot3_simulation.launch
```
* Finally, save the image in RViz, and it can then be used in AMCL.
```shell=
rosrun map_server map_saver -f mymap
```
<p align="center">
<img src= https://i.imgur.com/ldM08I8.png width="400px">
<img src= https://i.imgur.com/Z3CLUlz.png width="400px">
</p>

### MOVE_BASE
* The move_base package provides navigation functionalities, including:
  * Global Path Planning:
     * Conducts overall path planning based on a given target location.
     * In ROS, global path planning is the initial step where the shortest path for the robot to reach its destination is computed. The navfn package utilizes the Dijkstra's algorithm to calculate the minimum-cost path on the costmap.
  * Local Path Planning:
     * Performs path planning for avoiding obstacles in the current environment.
     * Local path planning is implemented through the base_local_planner. It employs algorithms such as Trajectory Rollout and Dynamic Window approaches to compute the robot's velocity and angular velocity to be executed in each time step. The algorithm follows these key steps:
       1. Gather the current robot state (dx, dy, dtheta).
       2. For each sampled data point, calculate a path that the robot should follow after a certain duration.
       3. Assign weights to each path based on predefined criteria.
       4. Select the optimal path based on the assigned weights.
       5. Repeat steps 1 to 4 until the destination is reached.
```shell=
roslaunch rbx1_nav fake_move_base_map_with_obstacles.launch
python3 move_base_square.py
rosrun rviz rviz -d rospack find rbx1_nav/nav_obstacles.rviz
```
<p align="center">
<img src= https://i.imgur.com/e9w9yHX.png width="400px">
</p>

* Combime the previous work. First, include the walls and obstacles in the launch file, so you don't have to use multiple rosrun commands. Also, remember to update the frame_id in the wall and obstacle parameters to match the changes in the global TF (transform) frame, which should typically be set to "map."
```shell=
roslaunch project_robot project_robot.launch
roslaunch rbx1_nav fake_move_base_map_with_obstacles.launch
python3 move_base_square.py
```
<p align="center">
<img src= https://i.imgur.com/qYoMPW3.png width="400px">
</p>

### Final result
```shell=
roslaunch project_robot.launch
roslaunch project_robot_nav.launch
```
<p align="center">
<img src=https://i.imgur.com/v16e8D7.png  width="450px">
<img src=https://i.imgur.com/C460fvx.png  width="450px">
<img src=https://i.imgur.com/BHGyA1m.png  width="450px">
<img src=https://i.imgur.com/R9e7IP5.png  width="400px">
</p>

## REFERENCE
1. https://github.com/pirobot/rbx1
2. https://github.com/vanadiumlabs/arbotix_ros
3. https://gino6178.medium.com/ros-開發與實戰-安裝melodic-4a2d76ceb68b
4. https://cse.sc.edu/~jokane/agitr/agitr-letter.pdf
5. http://wiki.ros.org/cn
6. https://www.guyuehome.com/category/column/ros-exploring
7. https://emanual.robotis.com/docs/en/platform/turtlebot3/overview/#overview
8. https://tr-ros-tutorial.readthedocs.io/zh_CN/latest/_source/setup/0.1.准备工作.html
9. https://clearpathrobotics.com/ros-robot-operating-system-cheat-sheet/
10. https://blog.csdn.net/uunubt/article/details/81183867
11. https://automaticaddison.com/how-to-launch-the-turtlebot3-simulation-with-ros/
12. https://pojenlai.wordpress.com/2012/12/14/ros教學系列文整理/
13. https://rosonjetson.wordpress.com/2015/08/30/ros-自學指南/
14. https://medium.com/pyladies-taiwan/reinforcement-learning-進階篇-deep-q-learning-26b10935a745
15. https://b9532026.wordpress.com/2010/03/30/apt-get-指令一覽-2/
16. https://blog.techbridge.cc/2016/09/28/ros-collision-avoiding-robot/
17. https://blog.techbridge.cc/2016/05/14/ros-object-recognition-kitchen/
