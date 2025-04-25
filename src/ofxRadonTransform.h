#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class ofxRadonTransform {
public:
    ofxRadonTransform();
    ~ofxRadonTransform();
    
    // Process the input image and generate Radon transform (sinogram)
    void setup(ofImage& inputImage);
    
    // Process with custom parameters
    void setup(ofImage& inputImage, int numAngles);
    
    // Get the resulting sinogram
    ofImage& getSinogram();
    
    // Get processing time in seconds
    double getProcessingTime();
    
private:
    ofImage sinogram;
    double processingTime;
    
    // Core Radon transform implementation
    void computeRadonTransform(cv::Mat& src, cv::Mat& dest, int angle);
};