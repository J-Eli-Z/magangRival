cmake_minimum_required(VERSION 3.0)

project( play )

find_package( OpenCV REQUIRED )

add_executable( play src/catchMeThat!.cpp )

##add_executable( oke1 src/progrobot.cpp )

target_link_libraries( play ${OpenCV_LIBS} )
