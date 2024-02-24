#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

int main(int argc, char const *argv[])
{
    Scalar lower_gray = Scalar(10,10,10);
    Scalar upper_gray = Scalar(180,255,46);
    VideoCapture cap;
    cap.open("/home/jiang/桌面/hw/RoboCup_Assessment/task1/video1.mp4");
    Mat frame,hsv,thr,mask,kernel,labels,stats,centroids;
    while(1) {
        cap >> frame;
        if (frame.empty())
            break;
        cvtColor(frame,thr,COLOR_BGR2GRAY);
        cvtColor(frame,hsv,COLOR_BGR2HSV);
        inRange(hsv,lower_gray,upper_gray,mask);
        kernel = getStructuringElement(MORPH_RECT,Size(5,5));
        morphologyEx(mask,mask,MORPH_OPEN,kernel);
        morphologyEx(mask,mask,MORPH_CLOSE,kernel);
        int num = connectedComponentsWithStats(mask,labels,stats,centroids);
        for(int i = 1;i < num;++i){
        if(stats.at<int>(i,CC_STAT_HEIGHT) > 170 && stats.at<int>(i,CC_STAT_LEFT) < frame.cols/2){
            Rect rect(
                stats.at<int>(i,CC_STAT_LEFT),
                stats.at<int>(i,CC_STAT_TOP),
                stats.at<int>(i,CC_STAT_WIDTH),
                stats.at<int>(i,CC_STAT_HEIGHT)
            );
            rectangle(frame,rect,Scalar(0,0,0),2);}}
        imshow("dst",frame);
        if(waitKey(20) == 'q'){
            break;
        }
    }
    cap.release();

    return 0;
}