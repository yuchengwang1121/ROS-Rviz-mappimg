#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char** argv){
        ros::init(argc, argv, "basic_obs");
        ros::NodeHandle n;
        ros::Publisher obs_pub = n.advertise<visualization_msgs::Marker>
                ("visualization_obs",10);
        while(ros::ok()){
                visualization_msgs::Marker obs1,obs2;
                obs1.header.frame_id = obs2.header.frame_id  = "map";
                obs1.header.stamp = obs2.header.stamp = ros::Time::now();
                obs1.ns = obs2.ns = "basic_obs";
                obs1.action = obs2.action
                        = visualization_msgs::Marker::ADD;

                obs1.pose.position.x = 0.0;
                obs1.pose.position.y = 3.5;
                obs1.pose.position.z = 1.0;

                obs2.pose.position.x = 0.0;
                obs2.pose.position.y = -2.21;
                obs2.pose.position.z = 1.0;

                obs1.id = 0;
                obs2.id = 1;
                obs1.type = visualization_msgs::Marker::CUBE;
                obs2.type = visualization_msgs::Marker::CUBE;

                obs1.scale.x = 0.6;
                obs1.scale.y = 2.5;
                obs1.scale.z = 2.0;
                obs1.color.r = 0.5;
                obs1.color.g = 0.5;
                obs1.color.b = 0.5;
                obs1.color.a = 1.0;
		
		obs2.scale.x = 0.6;
                obs2.scale.y = 2.5;
                obs2.scale.z = 2.0;
                obs2.color.r = 0.5;
                obs2.color.g = 0.5;
                obs2.color.b = 0.5;
                obs2.color.a = 1.0;

                obs_pub.publish(obs1);
                obs_pub.publish(obs2);

        }
}
