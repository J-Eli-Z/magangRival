#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#define PI 3.141592653589793238462643383279502884197
using namespace std;

void multiplication(float arr[3][3], int arr2[3][3], float arr3[3][3], int limit, float r){
    for (int i = 0; i < limit; i++){
        for (int j = 0; j < 3; j++){
            arr3[i][j] = (((arr[j][0] * arr2[i][0]) + (arr[j][1] * arr2[i][1]) + (arr[j][2] * arr2[i][2]))/r);

            // just a test case
            // cout << "i = " << i << endl;
            // cout << "j = " << j << endl;
            // cout << "This is arr 0 : " << arr[j][0] << endl;
            // cout << "This is arr2 0: " << arr2[i][0] << endl;
            // cout << "This is arr 1 : " << arr[j][1] << endl;
            // cout << "This is arr2 1: " << arr2[i][1] << endl;
            // cout << "This is arr 2 : " << arr[j][2] << endl;
            // cout << "This is arr2 2: " << arr2[i][2] << endl;
            // cout << "This is times 1: " << (arr[j][0] * arr2[i][0]) << endl;
            // cout << "This is times 2: " << (arr[j][1] * arr2[i][1]) << endl;
            // cout << "This is times 3: " << (arr[j][2] * arr2[i][2]) << endl;
            // cout << "This is before division: " << ((arr[j][0] * arr2[i][0]) + (arr[j][1] * arr2[i][1]) + (arr[j][2] * arr2[i][2])) << endl;
            // cout << arr3[i][j] << endl;
        }
    }
}

void printFloat(float arr[3][3], int limit){
    for (int i = 0; i < limit; i++){
        for (int j = 0; j < 3; j++){
            cout << setprecision(4) << arr[i][j] << endl;
        }
    }
}

// just a class you know
class robot{
    public:
        float lildan[3][3] = {
            {sin(((-135)*PI)/180), -cos(((225)*PI)/180), 0.15},
            {sin((0*PI)/180), -cos((0*PI)/180), 0.15},
            {sin((135*PI)/180), -cos((225*PI)/180), 0.15}
        };

        float dharmi[3][3] = {
            {sin(((-120)*PI)/180), -cos(((60)*PI)/180), 0.15},
            {sin(((120)*PI)/180), -cos(((60)*PI)/180), 0.15},
            {sin(((0)*PI)/180), -cos(((180)*PI)/180), 0.15}
        };

        float rl = 127.0/2000;
        float rd = 48.0/2000;

};

int main(){
    string name;
    cin >> name;

    transform(name.begin(), name.end(), name.begin(), ::tolower);
    
    robot myRobot;

    float result[3][3]; 
    int arr[3][3];
    char bot;

    if (name == "lildan"){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cin >> arr[i][j];
            }
        }
        bot = 'l';
    } 
    else if (name == "dharmi"){
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 3; j++){
                cin >> arr[i][j];
            }
        }
        bot = 'd';
    }

    string run;
    cin >> run;
    transform(run.begin(), run.end(), run.begin(), ::tolower);

    if (run == "gas"){
        if (bot == 'l'){
            wcout << "downTriangle" << endl; // my editor doesn't support Unicode Characters, i tried it out by setting up locale, still didn't work with neither UTF-8 and UTF-16
            multiplication(myRobot.lildan, arr, result, 3, myRobot.rl);
            printFloat(result, 3);
        } 
        else if (run == "gas"){
            wcout << "upTriangle" << endl; // my editor doesn't support Unicode Characters, i tried it out by setting up locale, still didn't work with neither UTF-8 and UTF-16
            multiplication(myRobot.dharmi, arr, result, 2, myRobot.rd);
            printFloat(result, 2);
        }
    }

    return 0;
}
