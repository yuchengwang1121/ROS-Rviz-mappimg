# include <ros/ros.h>
# include <visualization_msgs/Marker.h>

#include <cmath>

int main ( int argc, char** argv){
  ros::init(argc, argv, "point_and_line");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker",10);

  ros::Rate r(30);

  float f = 0.0;
  while(ros::ok()){
    //建立三個visualization_msgs/Marker 的訊息然後給予初始值
    visualization_msgs::Marker points, line_strip, line_list;
    points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = "point_and_line";
    points.header.stamp = line_strip.header.stamp = line_list.header.stamp = ros::Time::now();
    points.ns = line_strip.ns = line_list.ns = "point_and_line";
    points.action = line_strip.action = line_list.action = visualization_msgs::Marker::ADD;
    points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = 1.0;

    //接著我們給予三個不同的marker三個不同的變數
    //再來是設置各自的type
    points.id = 0;
    line_strip.id = 1;
    line_list.id = 2;
    points.type = visualization_msgs::Marker::POINTS;
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;
    line_list.type = visualization_msgs::Marker::LINE_LIST;

    //設置大小與顏色
    points.scale.x = 0.2;
    points.scale.y = 0.2;

    line_strip.scale.x = 0.1;
    line_list.scale.x = 0.1;

    points.color.g = 1.0f;
    points.color.a = 1.0;

    line_strip.color.b = 1.0;
    line_strip.color.a = 1.0;

    line_list.color.r = 1.0;
    line_list.color.a = 1.0;

    //使用迴圈創造圖形並且發布數據
    for(uint32_t i=0; i<100; ++i){
      float y = 5 * sin(f + i /100.0f * 2 * M_PI);
      float z = 5 * cos(f + i /100.0f * 2 * M_PI);
      geometry_msgs::Point p;
      p.x = (int32_t)i - 50;
      p.y = y;
      p.z = z;

      points.points.push_back(p);
      line_strip.points.push_back(p);

      line_list.points.push_back(p);
      p.z += 1.0;
      line_list.points.push_back(p);
    }

    marker_pub.publish(points);
    marker_pub.publish(line_strip);
    marker_pub.publish(line_list);

    r.sleep();

    f += 0.04;
  }
}


