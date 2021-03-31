#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char** argv){
        ros::init(argc, argv, "basic_obs");
        ros::NodeHandle n;
        ros::Publisher obs_pub = n.advertise<visualization_msgs::Marker>
                ("visualization_obs",10);
        while(ros::ok()){
                visualization_msgs::Marker obs1,obs2,obs3;
                obs1.header.frame_id = obs2.header.frame_id = obs3.header.frame_id = "basic_map";
                obs1.header.stamp = obs2.header.stamp = obs3.header.stamp = ros::Time::now();
                obs1.ns = obs2.ns = obs3.ns = "basic_obs";
                obs1.action = obs2.action = obs3.action
                        = visualization_msgs::Marker::ADD;

                obs1.pose.position.x = 2.5;
                obs1.pose.position.y = 2.5;

                obs2.pose.position.x = -2.0;
                obs2.pose.position.y = 3.0;

                obs3.pose.position.x = 0.0;
                obs3.pose.position.y = -3.0;

                obs1.id = 0;
                obs2.id = 1;
                obs3.id = 2;
                obs1.type = visualization_msgs::Marker::CUBE;
                obs2.type = visualization_msgs::Marker::CYLINDER;
		obs3.type = visualization_msgs::Marker::ARROW;

                obs1.scale.x = 2.0;
                obs1.scale.y = 2.0;
                obs1.scale.z = 2.0;
                obs1.color.r = 1.0f;
                //obs1.color.g = 192;
                //obs1.color.b = 192;
                obs1.color.a = 1.0;

                obs2.scale.x = 2.0;
                obs2.scale.y = 2.0;
                obs2.scale.z = 2.0;
                //obs2.color.r = 192;
                //obs2.color.g = 192;
                obs2.color.b = 1.0f;
                obs2.color.a = 1.0;

                obs3.scale.x = 2.0;
                obs3.scale.y = 2.0;
                obs3.scale.z = 2.0;
                //obs3.color.r = 192;
                obs3.color.g = 1.0f;
                //obs3.color.b = 192;
                obs3.color.a = 1.0;

                obs_pub.publish(obs1);
                obs_pub.publish(obs2);
                obs_pub.publish(obs3);

        }
}
