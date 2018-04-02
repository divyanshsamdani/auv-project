#include "ros/ros.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "std_msgs/Int16.h"
#include <iostream>

using namespace std;




int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");

  
  ros::NodeHandle n;

  
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int16>("chatter", 100);

  ros::Rate poll_rate(100);
  while(chatter_pub.getNumSubscribers()==0) poll_rate.sleep();

  
  
    
    std_msgs::Int16 msg;
    msg.data = atoi(argv[1]);

    
    ROS_INFO("I published %d \n", msg.data);

   
    chatter_pub.publish(msg);

    ros::spin();
    
  


  return 0;
}