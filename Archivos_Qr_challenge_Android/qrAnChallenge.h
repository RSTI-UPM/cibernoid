#ifndef QRANCHALLENGE_H
#define QRANCHALLENGE_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
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
