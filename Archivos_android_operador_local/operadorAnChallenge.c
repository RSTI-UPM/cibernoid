#include "operadorAnChallenge.h"

PUCHAR string;
PUCHAR pa_challenge_params[1];
PUCHAR pa_challenge_subkey[1];
PUCHAR key;
size_t len_string;


PUCHAR* getChallengeProtectParams(){
    FILE *fp;
    char var[40];
    /// Read the file with the string and close it
    fp = popen("dumpsys telephony.registry|grep mServiceState|awk '{print$3}'", "r");
    while (fgets(var, sizeof(var), fp) != NULL) {  
        pa_challenge_params[0] = malloc(strlen(var)+1);
        strcpy(pa_challenge_params[0], var); 
        printf("%s", var);
    }
    pclose(fp);
    return pa_challenge_params;
  
}

PUCHAR* getChallengeUnProtectParams(){

    FILE *fp;
    char var[40];
    /// Read the file with the string and close it
    fp = popen("dumpsys telephony.registry|grep mServiceState|awk '{print$3}'", "r");
    while (fgets(var, sizeof(var), fp) != NULL) {  
        pa_challenge_params[0] = malloc(strlen(var)+1);
        strcpy(pa_challenge_params[0], var); 
        printf("%s", var);
    }
     pclose(fp);
     return pa_challenge_params;

    
}

PUCHAR* executeParam()
{   
    /// Calling the internal function and obtaining the string decoded
    string = getChallengeProtectParams()[0];
      
    len_string = strlen(string);

    pa_challenge_subkey[0] = (PUCHAR)malloc(len_string);
    
    strcpy(pa_challenge_subkey[0], string); 
   
    return pa_challenge_subkey;
}

PUCHAR execute(PUCHAR* parametrosXml){

    /// Calling the internal function and obtaining the string decoded
    string = getChallengeProtectParams()[0];

    
    len_string = strlen(string);
    
    key = (PUCHAR)malloc(len_string);
    strcpy(key, string); 
 
    return key;    

}

PUCHAR* getParamNames(){
    return NULL;
}

int getNParams(){
    return 0;
}
