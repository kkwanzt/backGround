// backGround.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void capCha();
void grassBackground();

int main()
{
    capCha();
    grassBackground();
    return 0;
}

void capCha()
{
    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened())
    {
        cout << "failed" << endl;
    }

    int count = 0;
    Mat backPic;
    while (1)
    {
        Mat frame, fGray;
        Mat dstPic;
        cap >> frame;
        imshow("catchedPic", frame);
        cvtColor(frame, fGray, CV_BGR2GRAY);

        if (count == 0)
        {
            fGray.copyTo(backPic);
        }
        absdiff(fGray, backPic, dstPic);
        count++;
        threshold(dstPic, dstPic, 100, 200, THRESH_BINARY);
        imshow("差分结果", dstPic);
    }
 }

void grassBackground()
{
    VideoCapture cap;
    cap = VideoCapture("E:\\爱剪辑\\我的作品\\爱剪辑-也青道宝.mp4");
    if (!cap.isOpened())
        cout << "failed" << endl;

    int cout = 0;
    Mat backPic;
    while (1)
    {
        Mat frame,fGray;
        cap >> frame;
        imshow("srcImage", frame);
        cvtColor(frame, fGray, CV_BGR2GRAY);

        Mat  dstPic, thresholdPic,diffPic;
        int heigh,weight;
        heigh = fGray.rows;
        weight = fGray.cols;
        if (cout == 0)
            fGray.copyTo(backPic);
        absdiff(backPic,fGray,  diffPic);
        for (int i = 0; i < heigh; i++)
        {
            for (int j = 0; j < weight; j++)
            {
                double thredMin =saturate_cast<uchar>( backPic.at<uchar>(i, j)*0.6);
                double thredMax = saturate_cast<uchar>(backPic.at<uchar>(i, j) * 1.6);
                if (diffPic.at<uchar>(i, j) > thredMin&& diffPic.at<uchar>(i, j) < thredMax)
                    dstPic = 0;
                else dstPic = 1;
            }
        }
        cout++;
        imshow("高斯差分结果", dstPic);
    }
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
