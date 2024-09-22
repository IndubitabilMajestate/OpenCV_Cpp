#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <filesystem>


using namespace std;
using namespace cv;
namespace fs = std::filesystem;

int main(int argc, char const *argv[])
{
    (void)argc, argv;
    std::string images_root = fs::absolute("individual_proj/images/CroppedImages/").string();
    vector<cv::String> image_paths;
    glob(images_root+"Image*.png", image_paths, false);
    Size boardSize(25-1, 18-1);
    vector<vector<Point2f>> q(image_paths.size());

    vector<vector<Point3f>> Q;

    int checkerBoard[2] = {25, 18};
    int fieldSize = 15;

    vector<Point3f> objectPoint;
    for (int x = 1; x < checkerBoard[1]; x++){
        for (int y = 1; y < checkerBoard[0]; y++){
            objectPoint.push_back(Point3f(y*fieldSize, x*fieldSize, 0));
        }
    }

    vector<Point2f> imgPoint;
    size_t i = 0;
    for (auto const &im : image_paths){
        //cout << string(im) << endl;

        Mat img = imread(image_paths[i]);
        Mat gray;

        cvtColor(img, gray, COLOR_RGB2GRAY);

        bool foundPattern = findChessboardCorners(gray, boardSize, q[i], CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);

        if (foundPattern){
            cornerSubPix(gray, q[i], Size(11, 11), Size(-1,-1), TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 30, 0.1));
            Q.push_back(objectPoint);
        }

        drawChessboardCorners(img, boardSize, q[i], foundPattern);
        imshow("Chessboard detected", img);
        waitKey(0);

        i++;
    }

    Matx33f K(Matx33f::eye());
    Vec<float, 5> k(0, 0, 0, 0, 0);

    vector<Mat> rvecs, tvecs;
    vector<double> stdIntrinsics, stdExtrinsics, perViewErrors;

    int flags = CALIB_FIX_ASPECT_RATIO + CALIB_FIX_K3 + CALIB_ZERO_TANGENT_DIST + CALIB_FIX_PRINCIPAL_POINT;
    Size frameSize(1440,1080);

    float error = calibrateCamera(Q, q, frameSize, K, k, rvecs, tvecs, flags);

    cout<< "Reprojection error: " << error 
        << "\nK =\n" << K 
        << "\nk =\n" << k << endl;
    
    Mat mapX, mapY;
    initUndistortRectifyMap(K, k, Matx33f::eye(), K, frameSize, CV_32FC1, mapX, mapY);

    for ( auto const &im : image_paths) {
        //cout << string(im) << endl;

        Mat img = imread(im, IMREAD_COLOR);

        Mat imgUndistorted;
        remap(img, imgUndistorted, mapX, mapY, INTER_LINEAR);

        imshow("Undistorted image", imgUndistorted);
        waitKey(0);
    }

    return 0;
}