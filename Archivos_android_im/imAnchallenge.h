#ifndef IMANCHALLENGE_H
#define IMANCHALLENGE_H

    #include <opencv2/imgcodecs.hpp>
    #include <opencv2/imgproc.hpp>
    #include <unistd.h>
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
