
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

unsigned char buffer[BUFSIZ];
unsigned char* string;
unsigned char* pa_challenge_params[1];
unsigned char* pa_challenge_subkey[1];
size_t len_string;
int i;
char filename[] = "/data/data/cibernoid.multimedia.qr_code_scanner/files/challenge_key.txt";

int existsFile(char* filename) {
        FILE* f = NULL;
        f = fopen(filename,"r");
        if (f == NULL && errno == ENOENT)
            return 1;
        else {
            fclose(f);
            return 0;
        }
}


unsigned char ** getChallengeProtectParams(){
    int pid;
    pid = fork();
    switch(pid)
    {
        case -1:
            perror("Cannot create the child process\n");
            break;
        case 0:
            execl("/system/bin/sh", "sh", "-c", "am start -W -n cibernoid.multimedia.qr_code_scanner/.MainActivity", (char *)NULL);
            break;
        default:
            while(existsFile(filename)==1){
          
              wait(NULL);
              sleep(3);                      
          
          } 

            FILE *fp;
            char buff[30];
            int ret;

            /// Read the file with the string and close it
            fp = fopen(filename, "r");
            fgets(buff, 30, (FILE*)fp);
            fclose(fp);
            ret = remove(filename);

            if(ret == 0) {
              printf("File deleted successfully\n");
            } else {
              printf("Error: unable to delete the file\n");
            }
            pa_challenge_params[0] = (unsigned char*)malloc(strlen(buff)+1);
            strcpy(pa_challenge_params[0], buff); 

            //printf("Scanned string: %s\n", pa_challenge_params[0]);

            return pa_challenge_params;
    }
}

unsigned char ** getChallengeUnProtectParams(){
    int pid;
    pid = fork();
    switch(pid)
    {
        case -1: // Si pid es -1 quiere decir que ha habido un error
            perror("Cannot create the child process\n");
            break;
        case 0: // Cuando pid es cero quiere decir que es el proceso hijo
            execl("/system/bin/sh", "sh", "-c", "am start -W -n cibernoid.multimedia.qr_code_scanner/.MainActivity", (char *)NULL);
            break;
        default: // Cuando es distinto de cero es el padre
            while(existsFile(filename)==1){
           
              wait(NULL);
              sleep(3);                      
          
          } 

            FILE *fp;
            char buff[30];
            int ret;

            /// Read the file with the string and close it
            fp = fopen(filename, "r");
            fgets(buff, 30, (FILE*)fp);
            fclose(fp);
            ret = remove(filename);

            if(ret == 0) {
              printf("File deleted successfully\n");
            } else {
              printf("Error: unable to delete the file\n");
            }
            pa_challenge_params[0] = (unsigned char*)malloc(strlen(buff)+1);
            strcpy(pa_challenge_params[0], buff); 

            //printf("Scanned string: %s\n", pa_challenge_params[0]);

            return pa_challenge_params;
    }
}

unsigned char** executeParam()
{   
    /// Calling the internal function and obtaining the string decoded
    string = getChallengeProtectParams()[0];

    /// Generate the key: hash of the string
    
    len_string = strlen(string);


    /*printf("Subkey: ");

    for (i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        printf("%02x", string[i]);
    putchar('\n');*/

    pa_challenge_subkey[0] = (unsigned char*)malloc(len_string);
    
    strcpy(pa_challenge_subkey[0], string); 
     
    //printf("Scanned string execute: %s\n", pa_challenge_subkey[0]);
    return pa_challenge_subkey;
}

unsigned char** execute(unsigned char** parametrosXml){

    /// Calling the internal function and obtaining the string decoded
    string = getChallengeProtectParams()[0];

    
    len_string = strlen(string);
    
    pa_challenge_subkey[0] = (unsigned char*)malloc(len_string);
    strcpy(pa_challenge_subkey[0], string); 
    //printf("Scanned string executeparam: %s\n", pa_challenge_subkey[0]);
    return pa_challenge_subkey;
    

}

unsigned char** getParamNames(){
    return NULL;
}

int getNParams(){
    return 0;
}
