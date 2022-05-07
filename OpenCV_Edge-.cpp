#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

//Mat src, src_gray, frame;
//Mat dst, detected_edges;
//int lowThreshold = 50;

const char* window_name = "Edge Map";
const int max_lowThreshold = 100;
const int RATIO = 3;
const int kernel_size = 3;


int main(int argc, char** argv)
{
    Mat src, src_gray, frame;
    Mat dst,cdst,cdstP, detected_edges;
    int lowThreshold = 50;

    VideoCapture video_src(0);// Webcam is arguemnt of zero
                              // argv[1] is the thing after name of prgm set in project properties

    if (!video_src.isOpened()) {
        std::cout << "coudl not open video" << argv[1] << std::endl;
        return -1;
    }
    bool framesLeft = true, frameGrabSuccess;
    while (framesLeft) {
        frameGrabSuccess = video_src.read(frame);
        if (frameGrabSuccess) {
            dst.create(frame.size(), frame.type());

            blur(frame, detected_edges, Size(3, 3));
            Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * RATIO, kernel_size);
            dst = Scalar::all(0);
            
            //Do individual frame processing here
            frame.copyTo(dst, detected_edges);
            
            // Probabilistic Line Transform

            // Copy edges to the images that will display the results in BGR
            cvtColor(detected_edges, dst, COLOR_GRAY2BGR);
            cdstP = dst.clone();
            vector<Vec4i> linesP; // will hold the results of the detection
            HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection
            // Draw the lines
            for (size_t i = 0; i < linesP.size(); i++)
            {
                Vec4i l = linesP[i];
                line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
            }

            // Show results
            imshow("Edges", cdstP);
            //imshow("Source", src);
            //imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
            //imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);

            waitKey(1);//this should be zero if doing single images, 1 if video
            //saved video waitkey of 20
        }
        else {
            framesLeft = false;
        }
    }
    return 0;
}