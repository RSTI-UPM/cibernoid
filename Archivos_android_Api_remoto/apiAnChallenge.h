#ifndef _APIANCHALLENGE_H_
#define _APIANCHALLENGE_H_

	#include "rapidjson/document.h"
	#include "rapidjson/writer.h"
	#include "rapidjson/stringbuffer.h"

	#include <random>
	#include <unistd.h>
	#include <string>
	#include <sstream>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <iostream>
	#include <algorithm>

	#include <stdlib.h>   
	
    typedef unsigned char UCHAR;
    typedef UCHAR* PUCHAR;
    
    PUCHAR*  getChallengeProtectParams();
    PUCHAR*  getChallengeUnProtectParams();
    PUCHAR*  executeParam();
    PUCHAR execute(PUCHAR*  parametrosXml);
    PUCHAR*  getParamNames();
    int getNParams();
#endif
