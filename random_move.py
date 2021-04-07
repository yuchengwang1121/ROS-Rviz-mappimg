#!/usr/bin/env python
import roslib; roslib.load_manifest('robot_teleop')
import rospy
import random
from geometry_msgs.msg import Twist
from std_msgs.msg import String

class Teleop:
    def __init__(self):
        pub = rospy.Publisher('cmd_vel', Twist)
        rospy.init_node('robot_teleop')
        rate = rospy.Rate(rospy.get_param('~hz', 0.1))
        self.cmd = None

        cmd = Twist()
        cmd.linear.x = random.uniform(-0.2, 0.5);
        cmd.angular.z = random.uniform(-0.5, 0.5);

        self.cmd = cmd
        while not rospy.is_shutdown():
            rospy.loginfo(" Sending random velocity command : linear = %d  , angular = %d", cmd.linear.x , cmd.angular.z)
            pub.publish(self.cmd)
            rate.sleep()

if __name__ == '__main__':Teleop()
