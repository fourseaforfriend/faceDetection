/*
By downloading, copying, installing or using the software you agree to this license.
If you do not agree to this license, do not download, install,
copy or use the software.


                  License Agreement For libfacedetection
                     (3-clause BSD License)

Copyright (c) 2018-2019, Shiqi Yu, all rights reserved.
shiqi.yu@gmail.com

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the names of the copyright holders nor the names of the contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

This software is provided by the copyright holders and contributors "as is" and
any express or implied warranties, including, but not limited to, the implied
warranties of merchantability and fitness for a particular purpose are disclaimed.
In no event shall copyright holders or contributors be liable for any direct,
indirect, incidental, special, exemplary, or consequential damages
(including, but not limited to, procurement of substitute goods or services;
loss of use, data, or profits; or business interruption) however caused
and on any theory of liability, whether in contract, strict liability,
or tort (including negligence or otherwise) arising in any way out of
the use of this software, even if advised of the possibility of such damage.
*/

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "facedetectcnn.h"

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000
using namespace cv;

Mat detectFace(Mat &image, unsigned char *pBuffer)
{
    int * pResults = NULL;
    if(!pBuffer)
    {
        fprintf(stderr, "Can not alloc buffer.\n");
        return image;
    }
    pResults = facedetect_cnn(pBuffer, (unsigned char*)(image.ptr(0)), image.cols, image.rows, (int)image.step);

    printf("%d faces detected.\n", (pResults ? *pResults : 0));
    Mat result_cnn = image.clone();
    //print the detection results
    for(int i = 0; i < (pResults ? *pResults : 0); i++)
    {
        short * p = ((short*)(pResults+1))+142*i;
	int x = p[0];
	int y = p[1];
	int w = p[2];
	int h = p[3];
	int neighbors = p[4];
	int angle = p[5];

	printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x,y,w,h,neighbors, angle);
	rectangle(result_cnn, Rect(x, y, w, h), Scalar(0, 255, 0), 2);
     }
     return result_cnn;
}

int main(int argc, char* argv[])
{
    Mat image,result_cnn;
    int count = 0;
    bool stop = true;
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        return -1;
    }
    //pBuffer is used in the detection functions.
    //If you call functions in multiple threads, please create one buffer for each thread!
    unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
    while(stop)
    {
        cap>>image;
        resize(image,image,Size(200,150));
        if(count<=15)
        {
           result_cnn = image;
        }
        else
        {
           count = 0;
           result_cnn = detectFace(image,pBuffer);
        }
        imshow("result_cnn", result_cnn);
        if(waitKey(30)>=0)
           stop = false;
        count++;
    }
    //release the buffer
    free(pBuffer);

    return 0;
}
