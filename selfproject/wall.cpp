#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char** argv){
        ros::init(argc, argv, "basic_map");
        ros::NodeHandle n;
        ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>
                ("visualization_marker",1);
        while(ros::ok()){

                visualization_msgs::Marker wall1,wall2,wall3,wall4;
                wall1.header.frame_id = wall2.header.frame_id = wall3.header.frame_id = wall4.header.frame_id = "basic_map";
                wall1.header.stamp = wall2.header.stamp = wall3.header.stamp = wall4.header.stamp = ros::Time::now();
                wall1.ns = wall2.ns = wall3.ns = wall4.ns = "basic_map";
                wall1.action = wall2.action = wall3.action = wall4.action
                        = visualization_msgs::Marker::ADD;

                wall1.pose.position.x = 5.0;
                wall1.pose.position.y = 0.0;
                wall1.pose.position.z = 0.0;

                wall2.pose.orientation.x = 20.0;
                wall2.pose.orientation.y = 20.0;

                wall2.pose.position.x = 0.0;
                wall2.pose.position.y = 5.0;
                wall2.pose.position.z = 0.0;

                wall3.pose.position.x = -5.0;
                wall3.pose.position.y = 0.0;
 		wall3.pose.position.z = 0.0;

                wall4.pose.orientation.x = 20.0;
                wall4.pose.orientation.y = 20.0;

                wall4.pose.position.x = 0.0;
                wall4.pose.position.y = -5.0;
                wall4.pose.position.z = 0.0;

                wall1.id = 0;
                wall2.id = 1;
                wall3.id = 2;
                wall4.id = 3;

                wall1.type = wall2.type = wall3.type = wall4.type
                        = visualization_msgs::Marker::CUBE;

                wall1.scale.x = 0.2;
                wall1.scale.y = 10.0;
                wall1.scale.z = 2.0;
                wall1.color.r = 1.0f;
                wall1.color.a = 1.0;

                wall2.scale.x = 0.2;
                wall2.scale.y = 10.0;
                wall2.scale.z = 2.0;
                wall2.color.b = 1.0f;
		 wall2.color.a = 1.0;

                wall3.scale.x = 0.2;
                wall3.scale.y = 10.0;
                wall3.scale.z = 2.0;
                wall3.color.g = 1.0f;
                wall3.color.a = 1.0;

                wall4.scale.x = 0.2;
                wall4.scale.y = 10.0;
                wall4.scale.z = 2.0;
                wall4.color.b = 0.5f;
                wall4.color.r = 0.5f;
                wall4.color.a = 1.0;

                marker_pub.publish(wall1);
                marker_pub.publish(wall2);
                marker_pub.publish(wall3);
		marker_pub.publish(wall);
	}
}
