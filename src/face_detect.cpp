
//opencv
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <stdio.h>


//main
int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
	int cam_id; //camera id . Associated to device number in /dev/videoX
	int user_key; //user pressed key to quit
  cv::Mat gray_image; //image in gray to find faces

	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    // Create window to visualize results
    cv::namedWindow("faces", 1);


    // Initialize face detector object
    cv::CascadeClassifier face_detect;
    face_detect.load( "/home/river/Escriptori/webcam_capture-master/src/haarcascade_frontalface_default.xml" );

       if(!face_detect.load("/home/river/Escriptori/webcam_capture-master/src/haarcascade_frontalface_default.xml"))
       {
         std::cout<<"Error Loading XML file"<<std::endl;
         return -1;
       }



    //capture loop. Out of user press a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		{
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }


        // If input image is RGB, convert it to gray
        cv::cvtColor(image, gray_image, CV_BGR2GRAY);


        // Detect faces
        std::vector<cv::Rect> faces;
        face_detect.detectMultiScale( gray_image, faces, 1.3, 4, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );

        //draw circles on the image
        for(unsigned int ii = 0; ii < faces.size(); ii++ )
        {
                    cv::rectangle(image, faces[ii],cv::Scalar(255,0,0), 2,8 );
        }


        //show image in a window
        cv::imshow("faces", image);  //"Output Window"

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
    }
}
