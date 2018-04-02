#include "ros/ros.h"

#include "std_msgs/Int16.h"
#include <iostream>

using namespace std;
//using namespace cv;


void chatterCallback(const std_msgs::Int16::ConstPtr& msg)
{
	if((msg->data <1)||(msg->data >13)){
		ROS_INFO("Invalid number !");
	}

	else{
			ROS_INFO("I heard: [%d]", msg->data);
		}
 			
}

int main(int argc, char **argv)
{
  
   
  ros::init(argc, argv, "listener");

 
  ros::NodeHandle n;

 
  ros::Subscriber sub = n.subscribe("chatter", 10000, chatterCallback);

 
  ros::spin();

  return 0;
}
