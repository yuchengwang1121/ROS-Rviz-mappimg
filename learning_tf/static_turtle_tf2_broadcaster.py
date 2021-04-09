#!/usr/bin/env python
import rospy

#為了獲取命令列引數
import sys

import tf

#為了要使用StaticTransformBroadcaster
import tf2_ros
import geometry_msgs.msg

if __name__ == '__main__':
    if len(sys.argv) < 8:
        rospy.logerr('Invalid number of parameters\nusage: '
                     './static_turtle_tf2_broadcaster.py '
                     'child_frame_name x y z roll pitch yaw')
        sys.exit(0)
    else:
        if sys.argv[1] == 'world':
           rospy.logerr('Your static turtle name cannot be "world"')
            sys.exit(0)

        # 再來創建一個 StaticTransformBroadcaster，用來傳輸tf
        # 在這裡建立一個訊息TransformStamped，在附值後傳輸
        # 在給予實際tf值之前，先給予一些基本的設置
        rospy.init_node('my_static_tf2_broadcaster')
        broadcaster = tf2_ros.StaticTransformBroadcaster()
        static_transformStamped = geometry_msgs.msg.TransformStamped()

        # header.frame_id是父框架，child_frame_id是子框架
        static_transformStamped.header.stamp = rospy.Time.now()
        static_transformStamped.header.frame_id = "world"
        static_transformStamped.child_frame_id = sys.argv[1]

        #放置一個6D的東西
        static_transformStamped.transform.translation.x = float(sys.argv[2])
        static_transformStamped.transform.translation.y = float(sys.argv[3])
        static_transformStamped.transform.translation.z = float(sys.argv[4])

        quat = tf.transformations.quaternion_from_euler(
                   float(sys.argv[5]),float(sys.argv[6]),float(sys.argv[7]))
        static_transformStamped.transform.rotation.x = quat[0]
        static_transformStamped.transform.rotation.y = quat[1]
        static_transformStamped.transform.rotation.z = quat[2]
        static_transformStamped.transform.rotation.w = quat[3]

        #送出去
        broadcaster.sendTransform(static_transformStamped)
        rospy.spin()
