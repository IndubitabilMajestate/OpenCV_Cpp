#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;
int main()
{
    std::string images_root = fs::absolute(fs::path("individual_proj/images/CroppedImages/")).string();
    vector<std::string> relative_image_paths = {
        "Canon5D2_5_160_3200_chair_5_mean.JPG",
        "Canon5D2_5_160_3200_chair_11_mean.JPG",
        "Canon5D2_5_160_3200_chair_14_mean.JPG",
        "Canon5D2_5_160_3200_chair_14_real.JPG",
        "Canon5D2_5_160_3200_chair_11_real.JPG",
    };

    vector<String> abs_image_paths;
    for (const auto& path : relative_image_paths){
        fs::path abs_image_path_aux = fs::absolute(fs::path(images_root) / path);
        abs_image_paths.push_back(abs_image_path_aux.string());
    }

    vector<Mat> images;
    vector<String> titles;
    for (int i = 0; i < abs_image_paths.size(); i++){
        if (i < 2){
            images.push_back(imread(abs_image_paths[i], IMREAD_COLOR));
        }
        else{
            images.push_back(imread(abs_image_paths[i],IMREAD_GRAYSCALE));
        }
        resize(images[i],images[i], {500,500}, 0 ,0, INTER_NEAREST);
        string title = relative_image_paths[i]; 
        replace(title.begin(),title.end(),'_',' ');

        size_t pos = title.find(".JPG");
        if ( pos != std::string::npos)
        {
            title.erase(pos);
        }
        titles.push_back(title);
        //imshow(titles[i],images[i]);
    }
    waitKey();
    MatND histogram;
    int histSize = 256;
    const int* channel_numbers = { 0 };
    float channel_range[] = { 0.0, 256.0};
    const float* channel_ranges = channel_range;
    int number_bins = histSize;

    calcHist(&images[2], 1, 0, Mat(), histogram, 1, &number_bins, &channel_ranges);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
    normalize(histogram, histogram, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for(int i = 1; i < histSize; i++){
        line(histImage, Point(bin_w* (i-1), hist_h - cvRound(histogram.at<float>(i-1))),
        Point(bin_w * (i), hist_h - cvRound(histogram.at<float>(i))),
        Scalar(255, 0, 0), 2, 8, 0);
    }
    MatND histogram2;

    calcHist(&images[4], 1, 0, Mat(), histogram2, 1, &number_bins, &channel_ranges);

    Mat histImage2(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
    normalize(histogram2, histogram2, 0, histImage2.rows, NORM_MINMAX, -1, Mat());
    for(int i = 1; i < histSize; i++){
        line(histImage2, Point(bin_w* (i-1), hist_h - cvRound(histogram2.at<float>(i-1))),
        Point(bin_w * (i), hist_h - cvRound(histogram2.at<float>(i))),
        Scalar(255, 0, 0), 2, 8, 0);
    }


    double histMatchingCorreltion = compareHist(histogram, histogram2, HISTCMP_CORREL);
    double histMatchingChiSquare = compareHist(histogram, histogram2, HISTCMP_CHISQR);
    double histMatchingIntersect = compareHist(histogram, histogram2, HISTCMP_INTERSECT);
    double histMatchingBhattacharyya = compareHist(histogram, histogram2, HISTCMP_BHATTACHARYYA);


    cout << "Correlation: " << histMatchingCorreltion << endl;
    cout << "ChiSquare: " << histMatchingChiSquare << endl;
    cout << "Intersect: " << histMatchingIntersect << endl;
    cout << "Bhattacharyya: " << histMatchingBhattacharyya << endl;
    // cout << "Absolute Image Path: " << abs_image_path.string() << endl;

    imshow(titles[2], images[2]);
    imshow("Histogram 1", histImage);
    imshow(titles[4], images[4]);
    imshow("Histogram 2", histImage2);

    waitKey(0);
    return 0;
}
