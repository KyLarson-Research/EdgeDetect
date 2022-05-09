#include "edgeDetection.h"

using namespace cv;

// Define constant used for edge detection
const int THRESHOLD = 50;
const int MAX_THRESHOLD = 100;
const int RATIO = 3;
const int KERNEL_SIZE = 3;

/*
* Function Name: generateEdgeImage
* Algorithm: Uses canny edge detection
*            to transform an image to an
*            image containing the edges dependent
*            upon the constants defined above.
* Precondition: 'original' is an initialized Mat
* Postcondition: 'dest' contains the edge information
*                for 'original'
* Exceptions: None
* Notes: None
*/
Mat generateEdgeImage(Mat original) {
    Mat dest, src_gray, detected_edges;

    // Initialize destination to have the same dimensions/type as 'original'
    dest.create(original.size(), original.type());

    // Convert the original from RGB/BGR to gray scale
    cvtColor(original, src_gray, COLOR_BGR2GRAY);

    // Blur the image
    blur(src_gray, detected_edges, Size(3, 3));

    // Use Canny Edge Detection method to detected the edges
    Canny(detected_edges, detected_edges, THRESHOLD, THRESHOLD * RATIO, KERNEL_SIZE);

    // Setup destination Mat and return it
    dest = Scalar::all(0);
    original.copyTo(dest, detected_edges);
    return dest;
}