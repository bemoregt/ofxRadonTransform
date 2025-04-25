#include "ofxRadonTransform.h"

using namespace cv;
using namespace std;
using namespace ofxCv;

ofxRadonTransform::ofxRadonTransform() {
    processingTime = 0.0;
}

ofxRadonTransform::~ofxRadonTransform() {
    // Nothing to clean up
}

void ofxRadonTransform::setup(ofImage& inputImage) {
    // Default is 360 angles (0-359 degrees)
    setup(inputImage, 360);
}

void ofxRadonTransform::setup(ofImage& inputImage, int numAngles) {
    // Start timing
    double t = getTickCount();
    
    // Convert ofImage to cv::Mat
    Mat src = toCv(inputImage);
    Mat src2;
    
    // Convert to grayscale if needed
    if (src.channels() > 1) {
        cvtColor(src, src2, CV_BGR2GRAY);
    } else {
        src2 = src.clone();
    }
    
    // Create output Mat
    Mat radon_image;
    
    // Compute Radon transform
    computeRadonTransform(src2, radon_image, numAngles);
    
    // Convert back to ofImage
    Mat radon_normalized;
    normalize(radon_image, radon_normalized, 255, 0, NORM_MINMAX, CV_8U);
    toOf(radon_normalized, sinogram);
    sinogram.update();
    
    // Calculate processing time
    processingTime = (getTickCount() - t) / getTickFrequency();
}

void ofxRadonTransform::computeRadonTransform(cv::Mat& src, cv::Mat& dest, int angle) {
    // Convert to float for calculations
    Mat srcFloat;
    src.convertTo(srcFloat, CV_32FC1);
    
    // Create destination
    dest = Mat(srcFloat.rows, angle, CV_32FC1);
    
    // Calculate center of image
    float center = (srcFloat.rows / 2.0);
    
    // Define transformation matrices for rotation
    float shift0[] = {1, 0, -center, 0, 1, -center, 0, 0, 1};
    float shift1[] = {1, 0, center, 0, 1, center, 0, 0, 1};
    Mat m0 = Mat(3, 3, CV_32FC1, shift0);
    Mat m1 = Mat(3, 3, CV_32FC1, shift1);
    
    // Process each angle
    float *theta = new float[angle];
    for (int t = 0; t < angle; t++) {
        theta[t] = t * CV_PI / angle;
        
        // Create rotation matrix
        float R[] = {cos(theta[t]), sin(theta[t]), 0,
                    -sin(theta[t]), cos(theta[t]), 0,
                    0, 0, 1};
        Mat mR = Mat(3, 3, CV_32FC1, R);
        Mat rotation = m1 * mR * m0;
        
        // Apply rotation to image
        Mat rotated;
        warpPerspective(srcFloat, rotated, rotation, cv::Size(srcFloat.rows, srcFloat.cols), WARP_INVERSE_MAP);
        
        // Sum each column
        for (int j = 0; j < rotated.cols; j++) {
            float *p1 = dest.ptr<float>(j);
            for (int i = 0; i < rotated.rows; i++) {
                float *p2 = rotated.ptr<float>(i);
                p1[t] += p2[j];
            }
        }
    }
    
    // Clean up
    delete[] theta;
}

ofImage& ofxRadonTransform::getSinogram() {
    return sinogram;
}

double ofxRadonTransform::getProcessingTime() {
    return processingTime;
}