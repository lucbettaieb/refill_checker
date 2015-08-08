/**
 A ros node to tell somebody to refill the snacks

 Luc Bettaieb

 Some inspiration from penghou620
*/

#include <ros/ros.h>
#include <refill_checker/refill.h>


std::vector<uint> currentBlueReadings;
std::vector<uint> thresholdComparison;

double bad;
double big_ol_size;

ros::Publisher pub_;

uint maximum_bad;

namespace enc = sensor_msgs::image_encodings;

// void isWithinBlueRange(cv_bridge::CvImage::Mat image)
// {

// }

void loadCalibration()
{
  ROS_INFO("loading calibration's thresholdComparison vector");
  std::string line;
  std::ifstream fin;

  fin.open("cal.dat");

  if(!fin.good())
  {
    ROS_ERROR("file not found");
    ros::shutdown();
  }
  thresholdComparison.clear();

  uint i = 0;
  while (std::getline(fin, line))
  {
    if(i > 1)
    {
      thresholdComparison.push_back(boost::lexical_cast<uint>(line));
    }
    i++;
  }

  for (size_t x = X_MIN; x < X_MAX; x++)
  {
    for (size_t y = Y_MIN; y < Y_MAX; y++)
    {
      big_ol_size++;
      maximum_bad++;
    }
  }

  ROS_INFO("Diggity done loading calibration");
}

void imageCallback(const sensor_msgs::ImageConstPtr& original_image)
{
  cv_bridge::CvImagePtr cv_ptr;

  try
  {
    cv_ptr = cv_bridge::toCvCopy(original_image, enc::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("tutorialROSOpenCV::main.cpp::cv_bridge exception: %s", e.what());
    return;
  }

  cv::Mat image_ = cv_ptr->image;
  uint i = 0;

  for (size_t x = X_MIN; x < X_MAX; x++)
  {
    for (size_t y = Y_MIN; y < Y_MAX; y++)
    {
      cv::Vec3b intensity = image_.at<cv::Vec3b>(y, x);
      if (static_cast<uint>(intensity.val[0]) > thresholdComparison.at(i))
      {
        if (bad > 0)
          bad--;
      }
      else
        if (bad < maximum_bad)
          bad++;

      i++;
    }
  }

}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "refill_checker");

  ros::NodeHandle nh;
  
  
  pub_ = nh.advertise<std_msgs::Bool>("/needs_refill", 1);

  image_transport::ImageTransport it(nh);

  image_transport::Subscriber sub = it.subscribe("camera/rgb/image_raw", 1, imageCallback);

  std_msgs::Bool bee;
  bee.data = false;
  loadCalibration();

  while(ros::ok())
  {
    double ratio = bad / big_ol_size;

    if (ratio > EMPTY_THRESHOLD)
    {
      bee.data = true;
      pub_.publish(bee);
    }
    else
    {
      bee.data = false;
      pub_.publish(bee);
    }

    ros::spinOnce();  
  }
  
  return 0;
}
