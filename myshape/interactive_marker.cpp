#include <ros/ros.h>
#include <interactive_markers/interactive_marker_server.h>

//再來是寫回傳的值，我們用INFO印出來看
void processFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback){
  ROS_INFO_STREAM(feedback->marker_name << " is now at "
      << feedback->pose.position.x << ", " << feedback->pose.position.y
      << ", " << feedback->pose.position.z);

}
int main (int argc, char** argv){
  //初始化節點並架server
  ros::init(argc, argv, "simple_marker");

  interactive_markers::InteractiveMarkerServer server("simple_marker");

  //一些基本設置
  visualization_msgs::InteractiveMarker int_marker;
  int_marker.header.frame_id = "/myfirstinteraction";
  int_marker.header.stamp = ros::Time::now();
  int_marker.name = "my_marker";
  int_marker.description = "Simple 1-DOF control";

  visualization_msgs::Marker box_marker;
  box_marker.type = visualization_msgs::Marker::CUBE;
  box_marker.scale.x = 1.0;
  box_marker.scale.y = 1.0;
  
  box_marker.scale.z = 1.0;
  box_marker.color.r = 0.5;
  box_marker.color.g = 0.5;
  box_marker.color.b = 0.5;
  box_marker.color.a = 1.0;

  //把資料丟給int_marker
  visualization_msgs::InteractiveMarkerControl box_control;
  box_control.always_visible = true;
  box_control.markers.push_back( box_marker );

  int_marker.controls.push_back( box_control );

  visualization_msgs::InteractiveMarkerControl rotate_control;
  rotate_control.name = "move_x";
  rotate_control.interaction_mode =
          visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;

  int_marker.controls.push_back(rotate_control);

  //把int_marker、Feedback塞給server
  server.insert(int_marker, &processFeedback);

  server.applyChanges();

  ros::spin();
box_marker.scale.z = 1.0;
  box_marker.color.r = 0.5;
  box_marker.color.g = 0.5;
  box_marker.color.b = 0.5;
  box_marker.color.a = 1.0;

  visualization_msgs::InteractiveMarkerControl box_control;
  box_control.always_visible = true;
  box_control.markers.push_back( box_marker );

  int_marker.controls.push_back( box_control );

  visualization_msgs::InteractiveMarkerControl rotate_control;
  rotate_control.name = "move_x";
  rotate_control.interaction_mode =
          visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;

  int_marker.controls.push_back(rotate_control);

  server.insert(int_marker, &processFeedback);

  server.applyChanges();

  ros::spin();
box_marker.scale.z = 1.0;
  box_marker.color.r = 0.5;
  box_marker.color.g = 0.5;
  box_marker.color.b = 0.5;
  box_marker.color.a = 1.0;

  visualization_msgs::InteractiveMarkerControl box_control;
  box_control.always_visible = true;
  box_control.markers.push_back( box_marker );

  int_marker.controls.push_back( box_control );

  visualization_msgs::InteractiveMarkerControl rotate_control;
  rotate_control.name = "move_x";
  rotate_control.interaction_mode =
          visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;

  int_marker.controls.push_back(rotate_control);

  server.insert(int_marker, &processFeedback);

  server.applyChanges();

  ros::spin();
}
