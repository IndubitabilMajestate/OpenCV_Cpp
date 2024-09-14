#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <filesystem>

namespace fs = std::filesystem;

using namespace cv;
int main(int argc, char** argv )
{
    std::string images_dir = fs::path("individual_proj/images/CroppedImages/").string();
    std::string image_path = fs::absolute(fs::path(images_dir) / "Canon5D2_5_160_3200_chair_5_mean.JPG").string();

    Mat image;
    image = imread(image_path);
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}