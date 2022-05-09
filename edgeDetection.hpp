// Pre-compiler directive
#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

cv::Mat generateEdgeImage(cv::Mat original);

#endif