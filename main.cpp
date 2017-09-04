#include <sys/time.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "monocular_pose_estimator_lib/pose_estimator.h"

using namespace std;
using namespace cv;


/*
 * my laptop camera parameters
 */
double camera_matrix[] =
{
    745.7, 0.0, 337.5,
    0.0, 749.1, 260.3,
    0.0, 0.0, 1.0
};
double dist_coeff[] = {0.297, -1.2, 0.0077, 0.0029};

Mat m_camera_matrix = Mat(3, 3, CV_64FC1, camera_matrix).clone();
Mat m_dist_coeff = Mat(1, 4, CV_64FC1, dist_coeff).clone();

//The marker positions in the trackable's frame of reference:
// old four points
double marker_positions[4][3]
{
    {0.0714197,0.0800214,0.0622611},
    {0.0400755,-0.0912328,0.0317064},
    {-0.0647293,-0.0879977,0.0830852},
    {-0.0558663,-0.0165446,0.053473}
};

int main(int argc, char* argv[])
{

    PoseEstimator trackable_object_; //!< Declaration of the object whose pose will be estimated

    // Calibrated camera
    trackable_object_.camera_matrix_K_ = Mat(3, 3, CV_64FC1, camera_matrix).clone();
    trackable_object_.camera_distortion_coeffs_ = vector<double>(dist_coeff,dist_coeff+4);
    // Create the marker positions from the test points
    List4DPoints positions_of_markers_on_object;
    positions_of_markers_on_object.resize(4);

    for (int i = 0; i < 4; i++)
    {
      Eigen::Matrix<double, 4, 1> temp_point;
      temp_point(0) = marker_positions[i][0];
      temp_point(1) = marker_positions[i][1];
      temp_point(2) = marker_positions[i][2];
      temp_point(3) = 1;
      positions_of_markers_on_object(i) = temp_point;
    }
    trackable_object_.setMarkerPositions(positions_of_markers_on_object);


    for (int a=4; a<200;a++)  // a <=Count would do one too many...
    {
        string name = format("../frameData/frame%04d.jpg", a);

        Mat image = imread(name);
        Mat rgbmap;
        image.copyTo(rgbmap);
        Mat imageCopy;
        rgbmap.copyTo(imageCopy);
        Mat imgTemp_gray;
        cvtColor(imageCopy, imgTemp_gray, CV_RGBA2GRAY);

        // Get time at which the image was taken. This time is used to stamp the estimated pose and also calculate the position of where to search for the makers in the image
        struct timeval tv;
        gettimeofday(&tv,NULL);
        double time_to_predict = tv.tv_sec*1000 + tv.tv_usec/1000;//毫秒

        const bool found_body_pose = trackable_object_.estimateBodyPose(imgTemp_gray,time_to_predict);

        if (found_body_pose) // Only output the pose, if the pose was updated (i.e. a valid pose was found).
        {
          //Eigen::Matrix4d transform = trackable_object.getPredictedPose();
          //Matrix6d cov = trackable_object_.getPoseCovariance();
          Eigen::Matrix4d transform = trackable_object_.getPredictedPose();

          cout<<"No."<<a<<endl;
          cout<<"The PredictedPos: \n" << transform<<endl;
          //cout<<"The covariance: \n" << cov<<endl<<endl;

          trackable_object_.augmentImage(rgbmap);
          trackable_object_.augmentImage(imageCopy);
        }
        else
        { // If pose was not updated
          cout<<"Unable to resolve a pose."<<endl;
        }

        imshow("inputmap", imageCopy);
        imshow("rgbmap", rgbmap);

        waitKey(0);
        //char key = (char)waitKey(10);
        //if(key == 27) break;
    }
    return 0;
}
