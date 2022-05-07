#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/videoio.hpp>
#include <iostream>
using namespace cv;

// Initialize constants
const int THRESHOLD = 50;
const int MAX_THRESHOLD = 100;
const int RATIO = 3;
const int KERNEL_SIZE = 3;
const std::string WINDOW_NAME = "Feed";

// Declare global image matrices
Mat frame, src_gray;
Mat dst, detected_edges;

/*
* Function Name: cannyDisplay
* Algorithm: Detects the edges in an image and
*            creates a new image containing the 
*            edge data. This image is then displayed
* Precondition: 'frame' is initilized to an image
* Postcondition: 'The new image 'dst' is displayed and
*                shows the edges from 'frame'
* Exceptions: None
* Notes: None
*/
static void cannyDisplay(){
    // Initialize 'dst' to have the same dimensions/type as 'frame'
    dst.create(frame.size(), frame.type());

    // Convert 'frame' from RGB/BGR to gray scale
    cvtColor(frame, src_gray, COLOR_BGR2GRAY);

    // Blur the image
    blur(src_gray, detected_edges, Size(3, 3));

    // Use Canny Edge Detection method to detected the edges
    Canny(detected_edges, detected_edges, THRESHOLD, THRESHOLD * RATIO, KERNEL_SIZE);

    // Setup destination Mat and display it
    dst = Scalar::all(0);
    frame.copyTo(dst, detected_edges);
    imshow(WINDOW_NAME, dst);
}

int main(int argc, char** argv){
    // Open default camera
    VideoCapture video_src(0);

    // If unsuccessful, end the program
    if (!video_src.isOpened()){
        std::cout << "Could not open video source " << argv[1] << std::endl;
        return -1;
    }

    // Prime the while loop
    bool framesLeft = true;
    bool frameGrabSuccess;
    int frameWidth = video_src.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = video_src.get(CAP_PROP_FRAME_HEIGHT);
    
    // While frames are left in the video feed, continue looping
    while(framesLeft){

        // Grab the next frame from the video
        frameGrabSuccess = video_src.read(frame);

        // If successful detect edges in the frame
        if(frameGrabSuccess){

            // Using Canny Edge Detection, create a new image and display it
            cannyDisplay();

            // Use argument = 1 for live video and 0 for single images
            waitKey(1);
        }
        // Video has ended
        else {
            framesLeft = false;
        }
    }

    // Terminate the program
    return 0;
}