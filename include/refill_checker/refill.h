/*
  Luc Bettaieb
  refill.h
**/

#ifndef REFILL_H
#define REFILL_H

#include <stdio.h>

#include <image_transport/image_transport.h>

#include <cv_bridge/cv_bridge.h>

#include <sensor_msgs/image_encodings.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include <iostream>
#include <std_msgs/Bool.h>

#include <fstream>

const double EMPTY_THRESHOLD = 0.7;

const int X_MIN = 210;
const int Y_MIN = 129;

const int X_MAX = 420;
const int Y_MAX = 410;

// For full frame testing
// const int X_MIN = 0;
// const int Y_MIN = 0;

// const int X_MAX = 640;
// const int Y_MAX = 480;

const int X_DIFF = X_MAX - X_MIN;
const int Y_DIFF = Y_MAX - Y_MIN;



#endif  // REFILL_H
