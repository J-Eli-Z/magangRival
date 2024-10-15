#ifndef CLASS_HPP
#define CLASS_HPP

#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
using namespace cv;

class game {
    // as usual, private variables ^^
    private: 
    Point object, direction; // point variables to declare the movement of position and the upcoming move of the object
    int radObj = 15; // the object radius
    int counter = 0; // shall be converted into a text


    public: 
    // this will spawn the circle into display, whether from the initial start or after being captured 
    void spawnObject(const Mat& frame) {
        int maxX = frame.cols - radObj; 
        int maxY = frame.rows - radObj; 
        object = Point(rand() % maxX + radObj, rand() % maxY + radObj); 
    }

    // this will make the object's upcoming move and the way it responds to "walls"
    void directionBehaviour(const Mat& frame) {
        object += direction; // changing the object's point location
        if ((object.y <= radObj) || (object.y >= frame.rows - radObj)){
            direction.y = -direction.y; //reversing it's movement by the y coordinates, when met with the x boundaries
        }
        if ((object.x <= radObj) || (object.x >= frame.cols - radObj)){
            direction.x = -direction.x; //reversing it's movement by the x coordinates, when met with the y boundaries
        }
    }

    // this will check if it's in the range of the contour or not, when it is on the contour, it will return as true + counter++
    bool checkIntertwine(const vector<vector<Point>>& cnt) {
        for (const auto& cnt : cnt) {
            if (pointPolygonTest(cnt, object, false) >= 0) {
                counter++;
                return true;
            }
        }
        return false;
    }

    // usual construct, with a bit of declaration what the value of the variable direction is, by pixels
    game() {
        srand(static_cast<unsigned>(time(0))); 
        direction.x = 15; 
        direction.y = 15;
    }

    // get your object now, buy 1, only get 1!
    Point getObject() {
        return object;
    }

    // get your object's radius now, buy 1, only get 1!
    int getRadObject() {
        return radObj;
    }

    // I told you already! thisIs(a)String!!!
    string thisIsString() {
        string text = ("Candies collected: " + to_string(counter));
        return text;
    }
};

class myCamera : public game {
    private:
    // why make these variables private? just for because
    Mat frame, frameClone, color, colorClone, bitwise, bitwiseClone, hsv;
    vector<vector<Point>> contour;

    public:
    // why are these variables public? just because
    Mat lower, upper; 

    // this is the processing function, where all the frames will be transformed from BGR to HSV to bitwise to vector in a vector for 2D points as in contour 
    void processing () {
        cvtColor(frame, hsv, COLOR_BGR2HSV); // change frame from BGR to HSV
        inRange(hsv, Scalar(0, 145, 140), Scalar(10, 255, 255), lower); // red color detection, made to detect the darker boundaries
        inRange(hsv, Scalar(170, 200, 200), Scalar(180, 255, 255), upper); // red color detection, made on purpose to detect the lighter boundaries
        color = lower | upper; // merging together the range values that came out true
        bitwise_and(frame, frame, bitwise, color); // getting bitwise out of the color
        // bitwise_and(frame, frame, bitwise, upper); // an alternative i tried, worked significantly worse than now

        findContours(color, contour, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // putting in the contours
        // findContours(upper, contour, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); // worked significantly worse than now 
        for (size_t i = 0; i < contour.size(); i++) { // the way a circle contour is different than the rectangle ones
            Point2f center; // here's a point as a float data type so it's more precise and it's for finding the center of the color detected
            float radius; // circle radius
            minEnclosingCircle(contour[i], center, radius); //minimum ... encircling? 
            circle (frame, center, static_cast<int>(radius), Scalar(255, 255, 255), 2); // displays the circle contour
        }

        // makes the circle object appear in the "frame" and it's filled
        circle(frame, getObject(), getRadObject(), Scalar(0, 0, 255), -1);

        // this will flip the frame so players would have an easier time coordinating with the screeen, so they can play better
        flip(frame, frameClone, 1);
        putText(frameClone, thisIsString(), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2); // putting in the text counter in to frameClone

        // basically just flipping every Mat variable that will be put on display, by using the clone version of the original variable
        flip(bitwise, bitwiseClone, 1);
        flip(color, colorClone, 1);
    }

    void windowShow () {
        imshow("Bitwise", bitwiseClone);  // honestly not needed, but meh why not
        imshow("Limit Color", colorClone); // displaying the window 
        // imshow("Limit Color", upper); // from the previous experiment
        imshow("Camera", frameClone); // the main display of the gaming field
    }

    // why is this made? for no purpose at all, it was a leftover from the previous experiment that i don't wanna delete + comment
    Mat getFrame() const {
        return frame;
    }

    // main constructor
    myCamera() : game() {
        // starts the default (0) camera
        VideoCapture camera(0);
        // jsut for safety measures if it doesn't open, here's an error code
        if(!camera.isOpened()){
            cerr << "Camera can't be opened" << endl;
        }

        // getting the first frame from camera so it can be used for the spawnObject() function to initialize initial position
        camera >> frame;
        spawnObject(frame);

        // looped infinitely to scan frames as long you don't touch the 'space' button
        while(true){
            // putting in the input/pictures one by one every frame into the Mat frame
            camera >> frame;
            // call processing function
            processing();
            
            // this will tell the upcoming move's behaviour and will it or will it not mirror the object's movement and if it's met with the contour yet
            directionBehaviour(frame);
            if (checkIntertwine(contour) == true)
            {
                spawnObject(frame);
            }
            
            // call windowShow function to display all the windows
            windowShow();
            
            // basically, if you don't press spacebar, this program will loop indfinitely infinitely
            if(waitKey(5)== 32){
                break;
            }
        }
    }
};

#endif
