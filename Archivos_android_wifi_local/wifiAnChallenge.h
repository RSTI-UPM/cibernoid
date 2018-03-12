#ifndef WIFIANCHALLENGE_H
#define WIFIADORANCHALLENGE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sstream>
    #include <vector>
    
    typedef unsigned char UCHAR;
    typedef UCHAR* PUCHAR;

    PUCHAR* getChallengeProtectParams();
    PUCHAR* getChallengeUnProtectParams();
    PUCHAR* executeParam();
    PUCHAR execute(PUCHAR* parametrosXml);
    PUCHAR* getParamNames();
    int getNParams();

#endif
