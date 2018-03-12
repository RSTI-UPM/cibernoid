#ifndef _APIANCHALLENGE_H_
#define _APIANCHALLENGE_H_
    unsigned char ** getChallengeProtectParams();
    unsigned char ** getChallengeUnProtectParams();
    unsigned char** executeParam();
    unsigned char* execute(unsigned char** parametrosXml);
    unsigned char** getParamNames();
    int getNParams();
#endif