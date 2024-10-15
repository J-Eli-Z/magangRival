#include <opencv4/opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main (){
    VideoCapture kamera (0);
    if(kamera.isOpened()){
        cerr << "tidak bisa membuka" << endl;
    }
    cv::Mat frame;
    while(true){
        kamera >> frame;
        Mat hsv, lim_color;
        Mat frame_clone = frame.clone();

        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsv, Scalar(10, 18, 125), Scalar(11, 21, 156), lim_color);

        vector<vector<Point>> kontur;
        findContours(lim_color, kontur, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // Looping untuk menggambar bounding box di sekitar kontur yang ditemukan
        for (size_t i = 0; i < kontur.size(); i++) {
            Rect box = cv::boundingRect(kontur[i]);
            rectangle(frame_clone, box, Scalar(255, 255, 255), 2);
        }

        imshow("kamera",frame_clone);
        if(waitKey(30)== 32){
            break;
        }
    }
}