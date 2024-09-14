 #include <opencv2/highgui.hpp>
 #include <opencv2/imgcodecs.hpp>
 #include <opencv2/imgproc.hpp>
 #include <iostream>
 #include <string>
 #include <filesystem>

 using namespace std;
 using namespace cv;
 namespace fs = std::filesystem;

 int main()
 {
    std::string images_root = fs::absolute(fs::path("individual_proj/images/CroppedImages/")).string();
    std::string image_path1 = images_root + "Canon5D2_5_200_3200_fruit_11_mean.JPG";
    std::string image_path2 = images_root + "Canon5D2_5_200_3200_toy_3_real.JPG";
    std::string image_path3 = images_root + "Canon5D2_5_200_3200_toy_12_mean.JPG";

    Mat img = imread(image_path2, IMREAD_COLOR);
    resize(img, img, Size(600, 400));

    if (img.empty()){
        cout << "Error reading image" << endl;
        return 1;
    }
    
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Mat gray, binaryImg, contoursImg;
    cvtColor(img, gray, COLOR_RGB2GRAY);

    threshold(gray, binaryImg, 50, 255, THRESH_BINARY);

    findContours(binaryImg, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

    imshow("Source Image", img);

    for (int contour = 0; contour < contours.size(); contour++){
        Scalar color(rand() & 0xFF, rand() & 0xFF, rand() & 0xFF);
        drawContours(img, contours, contour, color, FILLED, 8, hierarchy);
    }

    imshow("Contours Image", img);
    waitKey();
    return 0;
 }
 