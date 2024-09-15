#pragma once
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

vector<Point2f> stairPoints;
vector<Point2f> final_stairPoints;
vector<Point2f> printerPoints;
vector<Point2f> final_printerPoints;

void get_stairPoints(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN && stairPoints.size() < 3)
    {
        cout << "Stair - point (" << x << ", " << y << ")" << endl;
        stairPoints.push_back(Point2f(x, y));
    }
    else if (event == EVENT_LBUTTONDOWN) {
        cout << "Stair - final point (" << x << ", " << y << ")" << endl;
        final_stairPoints.push_back(Point2f(x, y));
    }
}

void get_printerPoints(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN && printerPoints.size() < 4)
    {
        cout << "Printer - point (" << x << ", " << y << ")" << endl;
        printerPoints.push_back(Point2f(x, y));
    } 
    else if (event == EVENT_LBUTTONDOWN) {
        cout << "Printer - final point (" << x << ", " << y << ")" << endl;
        final_printerPoints.push_back(Point2f(x, y));
    }
}