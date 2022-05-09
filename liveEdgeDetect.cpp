#include <iostream>
#include "edgeDetection.hpp"
using namespace cv;

const int DEFAULT_CAMERA = 0;

int main(int argc, char** argv){
    // Open default camera
    VideoCapture video_src(DEFAULT_CAMERA);

    // If unsuccessful, end the program
    if (!video_src.isOpened()){
        std::cout << "Could not open video source " << argv[1] << std::endl;
        // Terminate the program and indicate an issue
        return -1;
    }

    // Prime the while loop
    bool framesLeft = true;
    bool frameGrabSuccess;
    double frameWidth = video_src.get(CAP_PROP_FRAME_WIDTH);
    double frameHeight = video_src.get(CAP_PROP_FRAME_HEIGHT);

    // To hold each frame of the video
    Mat frame;

    // While frames are left in the video feed, continue looping
    while(framesLeft){

        // Grab the next frame from the video
        frameGrabSuccess = video_src.read(frame);

        // If successful detect edges in the frame
        if(frameGrabSuccess){

            // Using Canny Edge Detection, create a new image and display it
            imshow("Feed", generateEdgeImage(frame));

            // Use argument = 1 for live video and 0 for single images
            waitKey(1);
        }
        // Video has ended
        else {
            framesLeft = false;
        }
    }

    // Terminate the program and indicate success
    return 0;
}
