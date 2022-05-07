#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

Mat src, src_gray, frame;
Mat dst, detected_edges;
int lowThreshold = 0;

const char* window_name = "Edge Map";
const int max_lowThreshold = 100;
const int RATIO = 3;
const int kernel_size = 3;

static void CannyThreshold(int, void*){
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold* RATIO, kernel_size);
    dst = Scalar::all(0);
    frame.copyTo(dst, detected_edges);
    imshow("Edges", dst);
}

int main(int argc, char** argv)
{
    VideoCapture video_src(argv[1]);
    if (!video_src.isOpened()){
        std::cout << "coudl not open video" << argv[1] << std::endl;
        return -1;
    }
    bool framesLeft = true, frameGrabSuccess;
    while (framesLeft) {
        frameGrabSuccess = video_src.read(frame);
        if (frameGrabSuccess) {
            dst.create(frame.size(), frame.type());
            cvtColor(frame, src_gray, COLOR_BGR2GRAY);
            namedWindow("Edges", WINDOW_NORMAL);
            CannyThreshold(0, 0);
            waitKey(0);
        }
        else {
            framesLeft = false;
        }
    }
    return 0;
}