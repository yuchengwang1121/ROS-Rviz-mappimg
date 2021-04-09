#include<ros/ros.h>
#include<turtlesim/Pose.h>
#include＜iomanip>

void poseMessageReceived(const turtlesim::Pose& msg){
  //send a message to rosout get from pub
  ROS_INFO_STREAM(std::setprecision(2) <<std::fixed
  <<“position=(”<< msg.x <<","<<msg.y<<")"
  <<“direction=”<< msg.theta);
}

int main(int argc, char** argv){
  // intitialize the node
  ros::init(argc, argv, “turtlesim_subscriber_node”);
  ros::NodeHandle nh;
  //subscribe the message
  ros::Subscriber sub=nh.subscribe(“turtle1/pose”,1000,&poseMessageReceived);

  ros::spin();//keep listening
}
