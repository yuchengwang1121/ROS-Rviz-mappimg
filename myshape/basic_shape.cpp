#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char** argv){
        ros::init(argc, argv, "basic_shapes");//初始化節點以及創造Pub在visualization_marker
        ros::NodeHandle n;
        ros::Rate(1);
        ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker",1);

        uint32_t shape = visualization_msgs::Marker::CUBE;//在這邊用一個整數來持續追蹤我們所要發布的形狀，下面會使用四種常見形狀做發布，
							  //因為visualization_msgs/Marker所發布的msgs是一樣的，所以這四種形狀可以隨意切換。

        while(ros::ok){
		//接著線建立一個 visualization_msgs/Marker，並開始填寫他的一些特性，
		//而這裡的header跟"tf"是一樣的。然後設置這個header的id為"myfirstshape"
                visualization_msgs::Marker marker;
                marker.header.frame_id = "myfirstshape";
                marker.header.stamp = ros::Time::now();
		
		//再來namespace(ns)跟id被用來創造一個為一的名字給這個marker，
		//如果marker message收到一樣的ns以及id，新的就會取代舊的。
                marker.ns = "basic_shape";
                marker.id = 0;
		
		//這個type則是用來辨別我們所送的marker種類，這裡我們是設置成為變數，所以會一直改變形狀
		//接著就是對著個marker所做的事，有ADD以及DELETE，"ADD"主要用來創建與修改。
                marker.type = shape;
                marker.action = visualization_msgs::Marker::ADD;

		//然後這一大堆主要就是設置基本位置以 geometry_msgs/Pose傳輸位置與方向
                marker.pose.position.x = 0;
                marker.pose.position.y = 0;
		marker.pose.position.z = 0;
                marker.pose.orientation.x = 0.0;
                marker.pose.orientation.y = 0.0;
                marker.pose.orientation.z = 0.0;
                marker.pose.orientation.w = 1.0;

		//這邊則是指這個形狀的大小，單位是公尺
                marker.scale.x = 1.0;
                marker.scale.y = 1.0;
                marker.scale.z = 1.0;

		//marker的顏色則是以std_msgs/ColorRGBA傳輸，每一項的值均介於0~1，
		//而特別要記得寫a，a代表的是可見度，0是隱形1是完全顯示。
                marker.color.r = 0.0f;
                marker.color.g = 1.0f;
                marker.color.b = 0.0f;
                marker.color.a = 1.0;

		//在被自動消除以前，這個marker要存在多久，而ros::Duration則表示絕不會消除。
		//如果有新的marker近來，lifetime會重置。
                marker.lifetime = ros::Duration();

                while(marker_pub.getNumSubscribers() < 1){
                        if(!ros::ok){
                                return 0;
                        }
                        ROS_WARN_ONCE("Please create a subscriber to the marker");
                        sleep(1);
		}
                marker_pub.publish(marker);

		//設置每個形狀的下一個要是甚麼
                switch(shape){
                        case visualization_msgs::Marker::CUBE:
                                shape = visualization_msgs::Marker::SPHERE;
                                break;

                        case visualization_msgs::Marker::SPHERE:
                                shape = visualization_msgs::Marker::ARROW;
                                break;

                        case visualization_msgs::Marker::ARROW:
                                shape = visualization_msgs::Marker::CYLINDER;
                                break;

                        case visualization_msgs::Marker::CYLINDER:
                                shape = visualization_msgs::Marker::CUBE;
                                break;
                }
                ros::Rate rate(1);
                rate.sleep();

        }

