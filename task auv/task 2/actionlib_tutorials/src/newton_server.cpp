#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib_tutorials/newtonAction.h>
#include <cmath>
#include <iostream>

using namespace std;

class newtonAction
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<actionlib_tutorials::newtonAction> as_; 
  std::string action_name_;
  // create messages that are used to published feedback/result
  actionlib_tutorials::newtonFeedback feedback_;
  actionlib_tutorials::newtonResult result_;

public:

  newtonAction(std::string name) :
    as_(nh_, name, boost::bind(&newtonAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~newtonAction(void)
  {
  }

  void executeCB(const actionlib_tutorials::newtonGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(1);
    bool success = true;

    // push_back the seeds for the fibonacci sequence
    feedback_.root.clear();

    //initialize feedback[0] as the value you input
    feedback_.root.push_back(goal->init);
    

    // publish info to the console for the user
    ROS_INFO("%s: Executing, finding root of function x^3+5x-3 using newton raphson method,starting with %f", action_name_.c_str(), goal->init);
    float a;
    int i=1;
    // start executing the action
    while(1)
    {
      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        break;
      }

      a = feedback_.root[i-1];
      feedback_.root.push_back(a-((pow(a,3)+5*a-3)/(3*pow(a,2)+5)));
      // publish the feedback
      as_.publishFeedback(feedback_);
      // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
      r.sleep();  

      // breaking condition (10 decimal places)
      float b,c;
      b = feedback_.root[i];
      c = feedback_.root[i-1];

      
      for(int j=0;j<10;j++){
        b=b*10;
        c=c*10;
      }
      if(abs(b-c)<1.0){
        break;
      }
      i++;
    }

    if(success)
    {
      result_.root = feedback_.root;
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      as_.setSucceeded(result_);
    }
  }


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "newton");

  newtonAction newton("newton");
  ros::spin();

  return 0;
}