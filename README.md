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

## ROS
### Node
### Topic
### Service
### Parameter
### Launch File

## Pratice & Final Result

## GMAPPING
![](https://i.imgur.com/ldM08I8.png)
![](https://i.imgur.com/Z3CLUlz.png)
## MOVE_BASE
![](https://i.imgur.com/e9w9yHX.png)
![](https://i.imgur.com/qYoMPW3.png)
## AMCL
![](https://i.imgur.com/NDTm4FG.png)
![](https://i.imgur.com/BHGyA1m.png)
![](https://i.imgur.com/R9e7IP5.png)
## REFERENCE
https://github.com/pirobot/rbx1

https://github.com/vanadiumlabs/arbotix_ros
