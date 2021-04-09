#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<stdlib.h> //for rand() and RANDMAX

int main(int argc, char** argv){
  
  ros::NodeHandle nh;//initialize the node ros::init(argc,argv,“turtle_publlisher_node”);
  
  //create a publisher
  ros::Publisher pub=nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1000);
  srand(time(0));//the random number generator
  ros::Rate rate(2);//loop 2 times every second

  while(ros::ok){//while the node is running
  //create and set the value of each field
    geometry_msgs::Twist msg;
    msg.linear.x=2*double(rand())/double(RAND_MAX);
    msg.angular.z=4*double(rand())/double(RAND_MAX)-2;
    pub.publish(msg);//publish the message
    //send a message to rosout
    ROS_INFO_STREAM("Sending random velocity command:"<<"linear="<<msg.linear.x
              <<"angular="<<msg.angular.z);
    rate.sleep();
    }
}
