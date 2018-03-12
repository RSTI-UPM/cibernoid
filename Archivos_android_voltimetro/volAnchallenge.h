#ifndef IMANCHALLENGE3_H
#define IMANCHALLENGE3_H

        #include <opencv2/imgcodecs.hpp>
        #include <opencv2/imgproc.hpp>
        #include <opencv2/opencv.hpp>
        #include <unistd.h>
        #include <sstream>
        #include <stdlib.h> 
        #include <sys/wait.h>

        typedef unsigned char UCHAR;
        typedef UCHAR* PUCHAR;

        PUCHAR*  getChallengeProtectParams();
        PUCHAR*  getChallengeUnProtectParams();
        PUCHAR*  executeParam();
        PUCHAR execute(PUCHAR*  parametrosXml);
        PUCHAR*  getParamNames();
        int getNParams();

#endif
