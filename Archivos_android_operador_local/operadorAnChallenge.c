
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


unsigned char* string;
unsigned char* pa_challenge_params[1];
unsigned char* pa_challenge_subkey[1];
unsigned char* key;
size_t len_string;


unsigned char ** getChallengeProtectParams(){
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

unsigned char ** getChallengeUnProtectParams(){

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

unsigned char** executeParam()
{   
    /// Calling the internal function and obtaining the string decoded
    string = getChallengeProtectParams()[0];

    /// Generate the key: hash of the string
    
    len_string = strlen(string);



    pa_challenge_subkey[0] = (unsigned char*)malloc(len_string);
    
    strcpy(pa_challenge_subkey[0], string); 
     
    //printf("Scanned string execute: %s\n", pa_challenge_subkey[0]);
    return pa_challenge_subkey;
}

unsigned char* execute(unsigned char** parametrosXml){

    /// Calling the internal function and obtaining the string decoded
    string = getChallengeProtectParams()[0];

    
    len_string = strlen(string);
    
    key = (unsigned char*)malloc(len_string);
    strcpy(key, string); 
    //printf("Scanned string executeparam: %s\n", );
    return key;
    

}

unsigned char** getParamNames(){
    return NULL;
}

int getNParams(){
    return 0;
}
