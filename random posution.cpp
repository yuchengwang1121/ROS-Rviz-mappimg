#include <ros/ros.h>
#include <interactive_markers/interactive_marker_server.h>
#include <stdlib.h>
#include <ros/console.h>

void processFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback){
  ROS_INFO_STREAM(feedback->marker_name << " is now at "
      << feedback->pose.position.x << ", " << feedback->pose.position.y
      << ", " << feedback->pose.position.z);

}

int main(int argc, char**argv){
        ros::init(argc, argv, "robot");

        interactive_markers::InteractiveMarkerServer server("robot_ser");
        srand(time(0));
        ros::Rate rate(5);

        while(ros::ok()){

                visualization_msgs::InteractiveMarker int_robot;

                int_robot.name = "robot";
                int_robot.header.frame_id = "basic_map";
                int_robot.header.stamp = ros::Time::now();
                int_robot.description = "i'm robot";

                visualization_msgs::Marker robot;
                robot.type = visualization_msgs::Marker::CYLINDER;
                robot.scale.x = 1.0;
                robot.scale.y = 1.0;
		robot.scale.z = 0.7;

                robot.color.r = 1.0f;
                robot.color.g = 192;
                robot.color.b = 203;
                robot.color.a = 1.0;


                robot.pose.position.x = 2*double(rand())/double(RAND_MAX);
                robot.pose.position.y = 4*double(rand())/double(RAND_MAX)-2;


                ROS_INFO_STREAM("Sending random velocity command:" << "x` = " << robot.pose.position.x << "y` = " << robot.pose.position.y);

                visualization_msgs::InteractiveMarkerControl robot_control;
                robot_control.always_visible = true;

                robot_control.markers.push_back(robot);
                int_robot.controls.push_back(robot_control);

                server.insert(int_robot);
                server.applyChanges();

                rate.sleep();
        }
}
