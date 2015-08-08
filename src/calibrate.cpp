/**
 A ros node to tell somebody to refill the snacks

 Luc Bettaieb

 Some inspiration from penghou620
*/

#include <ros/ros.h>
#include <refill_checker/refill.h>
#include <sound_play/sound_play.h>


std::vector<uint> emptyBinReadings(X_DIFF * Y_DIFF, 0);

namespace enc = sensor_msgs::image_encodings;

// void isWithinBlueRange(cv_bridge::CvImage::Mat image)
// {

// }

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

  size_t i = 0;
  for (size_t x = X_MIN; x < X_MAX; x++)
  {
    for (size_t y = Y_MIN; y < Y_MAX; y++)
    {
      // Iterates through all frames and finds the brightest points for everything
      
      cv::Vec3b intensity = image_.at<cv::Vec3b>(y, x);
      // std::cout << "i:" << i << ", intensity: " << static_cast<uint>(intensity.val[0]) << std::endl;
      if (static_cast<uint>(intensity.val[0]) > emptyBinReadings.at(i));
        emptyBinReadings.at(i) = static_cast<uint>(intensity.val[0]);

      i++;
    }
  }
}


void endCalibration()
{
   ROS_INFO("Ending calibration");
  std::ofstream file;
  file.open("cal.dat");

  file << "X_MIN: " << X_MIN << ", Y_MIN: " << Y_MIN << ", X_MAX: " << X_MAX << ", Y_MAX: " << Y_MAX << "\n" << std::endl;

  for (size_t i = 0; i < emptyBinReadings.size(); i++)
  {
    file << emptyBinReadings.at(i) << std::endl;
  }

  file.flush();
  file.close();
  ROS_INFO("done. bye!");
  ros::shutdown();
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "refill_checker");

  ros::NodeHandle nh;
  ros::Time begin = ros::Time::now();

  // sound_play::SoundClient sc;
  // sc.say("Time to calibrate!  Drive me around for a while then press return to end calibration.");
  ROS_INFO("Time to calibrate!  Drive me around for a 15 seconds GO GO GO!");
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("camera/rgb/image_raw", 1, imageCallback);

  while(ros::ok())
  {
    if(ros::Time::now() > begin + ros::Duration(15))
      endCalibration();

    ros::spinOnce();
  }
  return 0;
}
