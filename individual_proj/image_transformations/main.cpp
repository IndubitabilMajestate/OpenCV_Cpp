#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <filesystem>
#include "mouse.h"

using namespace std;
using namespace cv;
namespace fs = std::filesystem;

int main(int argc, char const *argv[])
{
    std::string images_root = fs::absolute("individual_proj/images/CroppedImages/").string();
    std::string image_path1 = images_root + "NikonD800_5_125_6400_stair_7_mean.JPG";
    std::string image_path2 = images_root + "Canon80D_8_8_12800_printer_14_mean.JPG";
    
    Mat perspectiveImg, affineImg;

    Mat stairImg = imread(image_path1);
    Mat printerImg = imread(image_path2);

    if ( stairImg.empty() || printerImg.empty()){
        cout << "Error reading image(s)." << endl;
        return 1;
    }

    namedWindow("Original stair", 1);
    namedWindow("Original printer", 1);

    setMouseCallback("Original stair", get_stairPoints, NULL);
    setMouseCallback("Original printer", get_printerPoints, NULL);

    imshow("Original stair", stairImg);
    imshow("Original printer", printerImg);

    waitKey();

    cout << "Stair points:" << endl;

    for (auto& point : stairPoints){
        cout << "(" << point.x << "," << point.y << ")" << endl;
    }

    cout << "Final points:" << endl;
    for (auto& point : final_stairPoints){
        cout << "(" << point.x << "," << point.y << ")" << endl;
    }

    Mat affineMatrix = getAffineTransform(stairPoints, final_stairPoints);

    warpAffine(stairImg, affineImg, affineMatrix, stairImg.size());
    imshow("Stair transformation", affineImg);
    waitKey();

    Mat perspectiveMatrix = getPerspectiveTransform(printerPoints, final_printerPoints);

    warpPerspective(printerImg, perspectiveImg, perspectiveMatrix, printerImg.size());
    imshow("Printer transformation", perspectiveImg);
    waitKey();
    return 0;
}