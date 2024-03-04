#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

int main(int argc, char const *argv[])
{
    Scalar lower_blue = Scalar(97,203,10);
    Scalar upper_blue = Scalar(105,255,255);
    Scalar lower_red = Scalar(0,43,46);
    Scalar upper_red = Scalar(10,255,255);
    VideoCapture cap;
    cap.open("/home/knot41/桌面/hw/RoboCup_Assessment/task2/video2.mp4");
    Mat frame,hsv,thr,mask1,mask2,kernel,labels1,stats1,centroids1,labels2,stats2,centroids2;
    while(1) {
        cap >> frame;
        if (frame.empty())
            break;
        cvtColor(frame,thr,COLOR_BGR2GRAY);
        cvtColor(frame,hsv,COLOR_BGR2HSV);
        inRange(hsv,lower_blue,upper_blue,mask1);
        inRange(hsv,lower_red,upper_red,mask2);
        kernel = getStructuringElement(MORPH_RECT,Size(5,5));
        morphologyEx(mask1,mask1,MORPH_OPEN,kernel);
        morphologyEx(mask2,mask2,MORPH_OPEN,kernel);
        int num1 = connectedComponentsWithStats(mask1,labels1,stats1,centroids1);
        int num2 = connectedComponentsWithStats(mask2,labels2,stats2,centroids2);
        for(int i = 1;i < num1;++i){
        if(stats1.at<int>(i,CC_STAT_HEIGHT) > stats1.at<int>(i,CC_STAT_WIDTH) && stats1.at<int>(i,CC_STAT_HEIGHT) > 60){
            Rect rect(
                stats1.at<int>(i,CC_STAT_LEFT),
                stats1.at<int>(i,CC_STAT_TOP),
                stats1.at<int>(i,CC_STAT_WIDTH),
                stats1.at<int>(i,CC_STAT_HEIGHT)
            );
            rectangle(frame,rect,Scalar(255,0,0),2);
            char text1[10];
            sprintf(text1,"%s","BLUE");
            putText(frame,text1,Point(stats1.at<int>(i,CC_STAT_LEFT),stats1.at<int>(i,CC_STAT_TOP)),FONT_HERSHEY_SIMPLEX,1,Scalar(255,0,0),4);
            }
        }
        for(int i = 1;i < num2;++i){
        if(stats2.at<int>(i,CC_STAT_AREA) > 1600 && stats2.at<int>(i,CC_STAT_HEIGHT) > 70){
            Rect rect(
                stats2.at<int>(i,CC_STAT_LEFT),
                stats2.at<int>(i,CC_STAT_TOP),
                stats2.at<int>(i,CC_STAT_WIDTH),
                stats2.at<int>(i,CC_STAT_HEIGHT)
            );
            rectangle(frame,rect,Scalar(0,0,255),2);
            char text2[10];
            sprintf(text2,"%s","RED");
            putText(frame,text2,Point(stats2.at<int>(i,CC_STAT_LEFT),stats2.at<int>(i,CC_STAT_TOP)),FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255),4);
            }
        }
        imshow("dst",frame);
        if(waitKey(10) == 'q'){
            break;
        }
    }
    cap.release();

    return 0;
}