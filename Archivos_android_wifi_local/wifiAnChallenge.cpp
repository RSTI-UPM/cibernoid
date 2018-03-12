
#include "wifiAnChallenge.h"

using namespace std;


PUCHAR pa_challenge_params[1];
PUCHAR pa_challenge_subkey[2];
PUCHAR key;



PUCHAR* getChallengeProtectParams(){
    FILE *fp;
    char var[40];
    int m = 1;
    PUCHAR list;
    int l=0;
    int i;    
    fp = popen("dumpsys wifi | grep -i '[0-9A-F]\\{2\\}\\(:[0-9A-F]\\{2\\}\\)\\{5\\}'| grep -|awk '{print$5\",\"$2\",\"$3}'", "r");
    std::string myString;
    while (fgets(var, sizeof(var), fp) != NULL) { 
        std::stringstream ss;
        for ( i= 0; i < 40; ++i){
            if(var[i] == 13 ||var[i] == 10|| m==0){
                m=0;
            }
            else{                
                  ss << var[i];                
            }    
        }
        m=1;
        myString += ss.str().c_str();
        myString +=";";             
    }
    pclose(fp); 
    printf("%s\n", myString.c_str());
    pa_challenge_params[0] = (PUCHAR)malloc(myString.length()+1);
    strcpy((char*)pa_challenge_params[0],myString.c_str());    

    return pa_challenge_params;
    
}

PUCHAR* getChallengeUnProtectParams(){
        
    FILE *fp;
    char var[40];
    int m = 1;
    PUCHAR list;
    int l=0;
    int i;    
    fp = popen("dumpsys wifi | grep -i '[0-9A-F]\\{2\\}\\(:[0-9A-F]\\{2\\}\\)\\{5\\}'| grep -|awk '{print$5\",\"$2\",\"$3}'", "r");
    std::string myString;
    while (fgets(var, sizeof(var), fp) != NULL) { 
        std::stringstream ss;
        for ( i= 0; i < 40; ++i){
            if(var[i] == 13 ||var[i] == 10|| m==0){
                m=0;
            }
            else{                
                  ss << var[i];                
            }    
        }
        m=1;
        myString += ss.str().c_str();
        myString +=";";             
    }
    pclose(fp); 
    printf("getChallengeUnProtectParams %s\n", myString.c_str());
    pa_challenge_params[0] = (PUCHAR)malloc(myString.length()+1);
    strcpy((char*)pa_challenge_params[0],myString.c_str());    
    return pa_challenge_params;
    
}

std::vector<std::string> splitFunction(const std::string str, char separator) {
    std::vector<std::string> result;
    size_t pos1 = 0;
    size_t pos2 = 0;
    while (pos2 != str.npos) {
        pos2 = str.find(separator, pos1);
        if (pos2 != str.npos) {
            if (pos2 > pos1)
                result.push_back(str.substr(pos1, pos2 - pos1));
            pos1 = pos2 + 1;
        }
    }
    result.push_back(str.substr(pos1, str.size() - pos1));
    return result;
}
int asciiToInt(int s){
    if(s==48) return 0;
    if(s==49) return 1;
    if(s==50) return 2;
    if(s==51) return 3;
    if(s==52) return 4;
    if(s==53) return 5;
    if(s==54) return 6;
    if(s==55) return 7;
    if(s==56) return 8;
    if(s==57) return 9;

}

PUCHAR* executeParam()
{   
    FILE *f; 
    PUCHAR  date;
    f = popen("svc wifi enable", "r");
    pclose(f);
    
    string wifis((const char*)getChallengeProtectParams()[0]);
    int canales = 1;
    int maximo = 0;
    int minimo = 6000;
    int noHay = 1;
    int varInt2;
    int varInt1;

    std::vector<std::string> ssids;    
    std::vector<std::string> wifisParse = splitFunction(wifis, L';');
    string pa_challenge_params_s;
    for (int i = 0; i < wifisParse.size()-1; i++) {
        std::vector<std::string> redString = splitFunction(wifisParse[i], L',');
        for(int k=0;k<ssids.size();k++){
                noHay=1;
                if(redString[0] == ssids[k]){                     
                        noHay=0;                                               
                        break;
                }
                        
            }

        if(noHay > 0){
            varInt2 = 0;
            varInt1 = 0;
            std::stringstream stream;
            for (int i = 0; i < 40; ++i){ 
                if(redString[2][i]==10||redString[2][i]==44||redString[2][i]==0) break;
                    if(redString[2][i]>=48&&redString[2][i]<=57){
                        varInt2 += redString[2][i];               
                        stream << redString[2][i];                       
                        break;
                    }                         
                    else{
                       
                    }              
     
            }
            int exp = 0;
            int p = 0;
            for (int i = 0; i < 40; ++i){
                if(redString[1][i]==10||redString[1][i]==44||redString[2][i]==0) break;
                if(redString[1][i]>=48&&redString[1][i]<=57){
                            if(p==0) exp = 1000;
                            if(p==1) exp = 100;
                            if(p==2) exp = 10;
                            if(p==3) exp = 1;
                            varInt1 += asciiToInt(redString[1][i])*exp;
                            p++;
                }else {  
                    
                }
                
               
            }
            //55 (Código ASCII 7, es decir menos de -70dBm de potencia)
            if (varInt2 <= 55) {
                pa_challenge_params_s += redString[0] + ",";                
                canales += varInt1;
                ssids.push_back(redString[0]);
                if (varInt1 > maximo) {
                    maximo = varInt1;
                }
                if (varInt1 < minimo) {
                    minimo = varInt1 ;
                }
            }
        }
    }
    printf("canales %i\n",canales);
    printf("maximo %i\n",maximo);
    printf("minimo %i\n",minimo);
    pa_challenge_params_s = pa_challenge_params_s.substr(0, pa_challenge_params_s.length() - 1);
    //canales = canales + minimo + maximo;
    printf("%s \n",pa_challenge_params_s.c_str());
    std::stringstream stream;
    stream << canales << minimo << maximo;
    pa_challenge_subkey[0] = (PUCHAR)malloc(stream.str().length()+1);
    strcpy((char*)pa_challenge_subkey[0], stream.str().c_str());
    printf("Termine %s\n",stream.str().c_str());

   // pa_challenge_subkey[0] = (PUCHAR)malloc(clave.length()+1);
    //strcpy((char*)pa_challenge_subkey[0],clave.c_str());
    pa_challenge_subkey[1] = (PUCHAR)malloc(pa_challenge_params_s.length()+1);
    strcpy((char*)pa_challenge_subkey[1],pa_challenge_params_s.c_str());
     
    //printf("Scanned string execute: %s\n", pa_challenge_subkey[0]);
    return pa_challenge_subkey;
}

PUCHAR execute(PUCHAR* parametrosXml){

    FILE *f; 
    PUCHAR  date;
    f = popen("svc wifi enable", "r");
    pclose(f);

    string wifis((const char*)getChallengeProtectParams()[0]);
    std::string parametrosXMLString((const char*)parametrosXml[1]);
    std::vector<std::string> wifisFijas = splitFunction(parametrosXMLString, L',');

    int canales = 1;
    int maximo = 0;
    int minimo = 6000;
    int noHay = 1;
    int varInt2;
    int varInt1;

    std::vector<std::string> ssids;

    std::vector<std::string> wifisParse = splitFunction(wifis, L';');
    string pa_challenge_params_s;
    for (int i = 0; i < wifisParse.size()-1; i++) {
        std::vector<std::string> redString = splitFunction(wifisParse[i], L',');
        for(int k=0;k<ssids.size();k++){
                noHay=1;
                if(redString[0] == ssids[k]){                     
                        noHay=0;                                               
                        break;
                }
                        
            }

        if(noHay > 0){
            for (int j = 0; j < wifisFijas.size(); j++) {
                if (redString[0] == (wifisFijas[j])) {                    
                    varInt2 = 0;
                    varInt1 = 0;
                    std::stringstream stream;
                    for (int i = 0; i < 40; ++i){ 
                        if(redString[2][i]==10||redString[2][i]==44||redString[2][i]==0) break;
                            if(redString[2][i]>=48&&redString[2][i]<=57){
                                varInt2 += redString[2][i];
                                stream << redString[2][i];
                                break;
                            }                         
                            else{
                               
                            }              
             
                    }
                    int exp = 0;
                    int p = 0;
                    for (int i = 0; i < 40; ++i){
                        if(redString[1][i]==10||redString[1][i]==44||redString[2][i]==0) break;
                        if(redString[1][i]>=48&&redString[1][i]<=57){
                                    if(p==0) exp = 1000;
                                    if(p==1) exp = 100;
                                    if(p==2) exp = 10;
                                    if(p==3) exp = 1;
                                    varInt1 += asciiToInt(redString[1][i])*exp;
                                    p++;                                    
                        }else {  
                            
                        }                
                       
                    }
                    

                    //57 (Código ASCII 9, es decir menos de -90dBm de potencia)
                    if (varInt2 <= 57) {
                        pa_challenge_params_s += redString[0] + ",";                
                        canales += varInt1;                       
                        ssids.push_back(redString[0]);
                        if (varInt1 > maximo) {
                            maximo = varInt1;
                        }
                        if (varInt1 < minimo) {
                            minimo = varInt1 ;
                        }
                    }
                    
                }
                }
        }
    }
   
    std::stringstream stream_k;
    stream_k << canales << minimo << maximo;
    key = (PUCHAR)malloc(stream_k.str().length()+1);
    strcpy((char*)key, stream_k.str().c_str());
    printf("Termine %s\n",stream_k.str().c_str());

    return key;
    

}



PUCHAR* getParamNames(){
    return NULL;
}

int getNParams(){
    return 0;
}

