
# NoReference-Image-Quality-Assesment
This is an implementation of the proposed NoReference-Image-Quality-Assesment of jpeg compressed images as presented in [[1]](https://live.ece.utexas.edu/publications/2002/zw_icip_2002_norefjpeg.pdf).  

The output is the estimated quality of the image. The higher the estimated quality value, the better. An image is evaluated on the basis of differences between the border of compression blocks (8x8 pixels - jpeg compression), inner block activity measuring the differences between neighbouring pixels to evaluating the amount of blur and lastly the total amount of differences between pixels. These measurements are determined both horizontaly and verticaly and weighted to determin the final quality estimate.

To install, download OpenCV - v.4.10 (https://github.com/opencv/opencv/releases).
Unpack source files, navigate to directory and run:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```
To build application, nevigate to root directory and run:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
To run application, run:
```
$ ./Quality <image filepath>
```




[[1] Z. Wang, H. R. Sheikh, and A.C. Bovik. No-reference perceptual quality
assessment of JPEG compressed images. IEEE Inter. Conf. Image Proc., Sept.
2002.](https://live.ece.utexas.edu/publications/2002/zw_icip_2002_norefjpeg.pdf)
