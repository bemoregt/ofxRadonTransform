# ofxRadonTransform

Radon Transform (Sinogram) addon for OpenFrameworks.

![Sinogram Example 1](https://github.com/bemoregt/gpRadonTransform/blob/master/sino.png)

![Sinogram Example 2](https://github.com/bemoregt/gpRadonTransform/blob/master/sino2.png)

![Sinogram Example 3](https://github.com/bemoregt/gpRadonTransform/blob/master/test3.png)

![Sinogram Example 4](https://github.com/bemoregt/gpRadonTransform/blob/master/test4.png)

## Overview

ofxRadonTransform is an OpenFrameworks addon that implements the Radon Transform for image processing. The Radon transform is a fundamental tool in tomographic reconstruction and has applications in computer vision, pattern recognition, and image analysis.

### What is Radon Transform?

The Radon Transform represents an image as a collection of projections along different angles. The result is often visualized as a sinogram - a 2D image where:
- Each row corresponds to a projection at a specific angle
- Each column corresponds to a specific position in the original image

This transformation provides a different representation of the image that highlights certain features and can be particularly useful for:
- Feature extraction
- Rotation-invariant pattern recognition
- Tomographic reconstruction
- Line detection

## Features

- Fast implementation of Radon Transform for grayscale images
- Adjustable angle resolution
- Computation time measurement
- Simple integration with existing OF projects
- Interactive example application with GUI controls

## Dependencies

- [OpenFrameworks 0.10.1+](https://openframeworks.cc/)
- [ofxCv](https://github.com/kylemcdonald/ofxCv)
- [ofxOpenCv](https://openframeworks.cc/documentation/ofxOpenCv/)
- [ofxGui](https://openframeworks.cc/documentation/ofxGui/)

## Installation

1. Download or clone this repository into the `addons` folder of your OpenFrameworks installation:
   ```
   cd openFrameworks/addons
   git clone https://github.com/bemoregt/ofxRadonTransform.git
   ```

2. Open the example project in Project Generator, update it, and open in your IDE.

3. Alternatively, add `ofxRadonTransform` to your existing project using the Project Generator.

## Usage

Basic usage example:

```cpp
#include "ofxRadonTransform.h"

ofxRadonTransform radonTransform;
ofImage inputImage, outputImage;

// In setup()
inputImage.load("test.png");

// Compute Radon transform with 360 angle steps
radonTransform.compute(inputImage, outputImage, 360);

// In draw()
inputImage.draw(0, 0);
outputImage.draw(inputImage.getWidth(), 0);

// Get computation time
float time = radonTransform.getElapsedTime();
```

## Algorithm

- Sinogram is the Radon Transform for Grayscale Image.
- Sinogram is a kind of Reciprocal Transform, like a Fourier Transform.
- From Fourier Slice Theorem, Sinogram can be implemented from Polar 1D FFT.
- Like the Fourier space, Phase space, and Hough space, these second spaces are very important to get more detailed features by post processing.
- The implementation is based on rotating the image at various angles and summing pixel values along columns.
- The resulting sinogram is a 2D representation where:
  - Horizontal axis represents angle (0-360 degrees)
  - Vertical axis represents distance from center
  - Pixel intensity represents sum of pixels along each projection line

## Applications

- Image feature extraction
- Dataset transformation and augmentation for deep learning
- Data compression
- Invariance achievement
- Second space image processing
- Tomographic reconstruction

## Future Plans

- Inverse Radon Transform for image reconstruction
- Fast Hough Transform implementation using Radon Transform
- 1D Entropy Plot for analyzing projection patterns
- Peak detection for identifying significant features in the sinogram
- Performance optimizations for real-time usage

## Reference

- Original implementation based on: [OpenCV-Radon](https://github.com/fan2fan/OpenCV-Radon.git)
- Theoretical background: [Radon Transform - Wikipedia](https://en.wikipedia.org/wiki/Radon_transform)

## License

MIT License

## Author

[bemoregt](https://github.com/bemoregt)
