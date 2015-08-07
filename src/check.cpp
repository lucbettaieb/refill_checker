/**
 A ros node to tell somebody to refill the snacks

 Luc Bettaieb
*/

#include <ros/ros.h>
#include <refill_checker/refill.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "refill_checker");

  ros::spin();
  return 0;
}
