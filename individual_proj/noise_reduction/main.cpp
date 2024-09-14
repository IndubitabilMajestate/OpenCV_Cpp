#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;

const int max_value_H = 360 / 2;
const int max_value = 255;

int main()
{
    string images_dir = fs::path("individual_proj/images/CroppedImages/").string();
    string image_path1 = fs::absolute(fs::path(images_dir) / "Canon5D2_5_160_3200_chair_5_mean.JPG").string();
    string image_path2 = fs::absolute(fs::path(images_dir) / "Canon5D2_5_160_3200_chair_5_real.JPG").string();
    string image_path3 = fs::absolute(fs::path(images_dir) / "Canon5D2_5_160_3200_chair_11_mean.JPG").string();

    Mat image1 = imread(image_path1, IMREAD_COLOR);
    
    if (image1.empty())
    {
        cout << "Error reading " << image1 << endl;
        return 1;
    }
    resize(image1, image1, {500, 500});

    

    vector<int> lower_bound = { 170, 80, 50};
    int low_H = lower_bound[0], low_S = lower_bound[1], low_V = lower_bound[2];
    int high_H = max_value_H, high_S = max_value, high_V = max_value;

    Mat hsvImg, imgThreshold;

    cvtColor(image1, hsvImg, COLOR_BGR2HSV);

    inRange(hsvImg, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), imgThreshold);

    Mat medianBlurImg, gaussianBlurImg;
    medianBlur(image1, medianBlurImg, 9);
    GaussianBlur(image1, gaussianBlurImg, Size(1,1), 9, 9);

    imshow("Original Image", image1);
    imshow("Median Blurred Image", medianBlurImg);
    imshow("Gaussian Blurred Image", gaussianBlurImg);

    int key = waitKey(0);

    if (key == 'q')
    {
        destroyAllWindows();
    }

    return 0;
}