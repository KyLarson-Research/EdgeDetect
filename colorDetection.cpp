#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;

const int DEFAULT_CAMERA = 0;

int main(int argc, char** argv){
    // Load an image
    Mat src = imread(argv[1]);

    Mat src_HSV, mask;
    src_HSV.create(src.size(), CV_8U);
    mask.create(src.size(), CV_8U);

    int hue_min=0, sat_min=0, val_min=0;
    int hue_max=12, sat_max=13, val_max=255;

    //Convert image to HSV
    cvtColor(src, src_HSV, COLOR_BGR2HSV, CV_8U);

    imshow("HSV", src_HSV);
    imshow("Original", src);
    
    // Create trackbars for determining HSV values
    namedWindow("Trackbars", WINDOW_AUTOSIZE);
    createTrackbar("Hue Min", "Trackbars", &hue_min, 179);
    createTrackbar("Hue Max", "Trackbars", &hue_max, 179);
    createTrackbar("Sat Min", "Trackbars", &sat_min, 255);
    createTrackbar("Sat Max", "Trackbars", &sat_max, 255);
    createTrackbar("Val Min", "Trackbars", &val_min, 255);
    createTrackbar("Val Max", "Trackbars", &val_max, 255);

    // Loop while user finds correct HSV maxs/mins
    while (true) {
        inRange(src, Scalar(hue_min, sat_min, val_min), Scalar(hue_max, sat_max, val_max), mask);
        imshow("Color Detected", mask);
        waitKey(1);
    }
    // Terminate the program and indicate success
    return 0;
}