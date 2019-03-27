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

using namespace cv;

int main(int argc, char* argv[])
{
    Mat image;
    //VideoCapture cap("/home/nzf/Movie/3.mp4");
    //VideoCapture cap("rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov");
    //VideoCapture cap("rtsp://192.168.1.102:8554/vlc");
    //VideoCapture cap("rtmp://192.168.1.102:1935/vod/3.mp4");
    VideoCapture cap(0);
    int frameH = (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int frameW = (int)cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int fps = (int)cap.get(CV_CAP_PROP_FPS);
    if(!cap.isOpened())
    {
        printf("cap open error!\n");
        return -1;
    }
    while(cap.read(image))
    {
        resize(image,image,Size(frameW,frameH));
        flip(image,image,1);
        imshow("result_cnn", image);
        if((waitKey((int)((1.0/fps)*1000))>=0))
            break;
    }
    return 0;
}
