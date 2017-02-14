#include <QCoreApplication>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

#define WINDOW_NAME1 "window1"
#define WINDOW_NAME2 "window2"

Mat g_srcImage,g_srcImage1,g_grayImage;
int thresh =30;
int max_thresh = 175;

void on_CornerHarris(int,void*);


int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
    g_srcImage = imread("/home/spadesk/workspace/lena.jpg",1);
    imshow("yuanshitu",g_srcImage);
    g_srcImage1 = g_srcImage.clone();

    cvtColor(g_srcImage1,g_grayImage,COLOR_BGR2GRAY);
    namedWindow(WINDOW_NAME1,WINDOW_AUTOSIZE);
    createTrackbar("thresh",WINDOW_NAME1,&thresh,max_thresh,on_CornerHarris);

    on_CornerHarris(0,0);
    waitKey(0);
    return 0;


//    return a.exec();
}


void on_CornerHarris(int, void *)
{
    Mat dstImage;
    Mat normImage;
    Mat scaledImage;

    dstImage = Mat::zeros(g_srcImage.size(),CV_32FC1);
    g_srcImage1=g_srcImage.clone();

    cornerHarris(g_grayImage,dstImage,2,3,0.04,BORDER_DEFAULT);
    normalize(dstImage,normImage,0,255,NORM_MINMAX,CV_32FC1,Mat());
    convertScaleAbs(normImage,scaledImage);


    for (int j=0;j < normImage.rows;j++)
    {
        for(int i=0;i<normImage.cols;i++)
        {
           if((int)normImage.at<float>(j,i)>thresh+80)

            {
               circle(g_srcImage1,Point(i,j),5,Scalar(10,10,255),2,8,0);
               circle(scaledImage,Point(i,j),5,Scalar(0,10,255),2,8,0);
            }
        }
    }
    imshow(WINDOW_NAME1,g_srcImage1);
    imshow(WINDOW_NAME2,scaledImage);
}
