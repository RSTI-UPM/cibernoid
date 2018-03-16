#ifndef IMANCHALLENGE_H
#define IMANCHALLENGE_H
	#include <stdio.h>
	#include <sstream>
	#include <unistd.h>
	#include <sys/wait.h> 
	#include <stdexcept>
	#include <vector>
	#include "opencv2/core.hpp"
	#include "opencv2/features2d.hpp"
	#include "opencv2/imgcodecs.hpp"
	#include "opencv2/highgui.hpp"
	#include "opencv2/xfeatures2d.hpp"

	typedef unsigned char UCHAR;
    typedef UCHAR* PUCHAR;
    
    PUCHAR*  getChallengeProtectParams();
    PUCHAR*  getChallengeUnProtectParams();
    PUCHAR*  executeParam();
    PUCHAR execute(PUCHAR*  parametrosXml);
    PUCHAR*  getParamNames();
    int getNParams();

#endif
