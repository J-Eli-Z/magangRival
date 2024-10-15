
#ifndef CLASS_HPP
#define CLASS_HPP

#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class game {
    private: 
    Point object;
    Point direction = (2,2);
    int radObj = 20;

    public: 

    void repositionObject() {
        int maxX = frame.cols - radObj; // Max X position
        int maxY = frame.rows - radObj; // Max Y position
        animatedObject = Point(rand() % maxX + radius, rand() % maxY + radius); // Random position
    }


    bool checkCollision(const vector<vector<Point>>& cnt) {
        for (const auto& cnt) {
            if (pointPolygonTest(cnt, animatedObject, false) >= 0) {
                return true;
            }
        }
        return false;
    }
};

class myCamera : public game {
    private:
    // why make these variables private? just for because
    Mat frame, color, bitwise, hsv;
    vector<vector<Point>> contour;

    public:
    // why are these variables public? just because
    Mat lower, upper; // actually we don't really need the lower variable any longer since it's a variable for the experiment i preciously did

    // this is the processing function, where all the frames will be transformed from BGR to HSV to bitwise to vector in a vector for 2D points as in contour 
    void processing () {
        cvtColor(frame, hsv, COLOR_BGR2HSV); // change frame from BGR to HSV
        // inRange(hsv, Scalar(0, 50, 50), Scalar(10, 255, 255), lower); // an experiment that i don't want to delete
        inRange(hsv, Scalar(170, 200, 200), Scalar(180, 255, 255), upper); // red color detection, made on purpose to only detect the lighter boundaries
        // color = lower | upper; // an experiment that i don't want to delete
        // bitwise_and(frame, frame, bitwise, color); // an experiment that i don't want to delete
        bitwise_and(frame, frame, bitwise, upper); // honestly not needed, but meh why not

        // findContours(color, contour, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        findContours(upper, contour, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //putting in the contours
        for (size_t i = 0; i < contour.size(); i++) { // the way a circle contour is different than the rectangle ones
            Point2f center; // here's a point as a float data type so it's more precise and it's for finding the center of the color detected
            float radius; // circle radius
            minEnclosingCircle(contour[i], center, radius); //minimum ... encircling? 
            circle (frame, center, static_cast<int>(radius), Scalar(255, 255, 255), 2); // displays the circle
        }

        circle(frame, animatedObject, radius, Scalar(0, 0, 255), -1);
    }

    void windowShow () {
        imshow("Bitwise", bitwise);  // honestly not needed, but meh why not
        // imshow("Limit Color", color); // an experiment i don't wanna delete
        imshow("Limit Color", upper); // honestly not needed, but meh why not
        imshow("Camera",frame); 
    }

    // why is this made? for no purpose at all, it was a leftover from the previous experiment that i don't wanna delete + comment
    Mat getFrame() const {
        return frame;
    }

    // main constructor
    myCamera() {
        // starts the default (0) camera
        VideoCapture camera(0);
        // jsut for safety measures if it doesn't open, here's an error code
        if(!camera.isOpened()){
            cerr << "Camera can't be opened" << endl;
        }
        
        // looped infinitely to scan frames as long you don't touch the 'space' button
        while(true){
            // putting in the input/pictures one by one every frame into the Mat frame
            camera >> frame;
            // call processing function
            processing();
            // call windowShow function to display all the windows
            windowShow();
            // basically, if you don't press spacebar, this program will loop indfinitely infinitely
            if(waitKey(30)== 32){
                break;
            }
        }
    }
};

#endif