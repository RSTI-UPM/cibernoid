//https://curl.haxx.se/download.html
//https://github.com/gcesarmza/curl-android-ios
//https://github.com/artoolkit/ofxARToolKit/blob/master/libs/android/EclipseProjects/ARSimple/libs/x86/libcurl.so
//https://ieroot.com/2015/03/29/1728.html

//https://sourceforge.net/p/libjson/wiki/Home/
//https://github.com/jehiah/json-c
//#https://forum.xda-developers.com/showthread.php?t=2362386 Install curl android

#include "apiAnChallenge.h"

using namespace std;
using namespace rapidjson;


PUCHAR  challenge_params[5];
PUCHAR  code_params_names[5];
PUCHAR  key;
PUCHAR  s[4];   
PUCHAR  environment_params[9];



char filename[] = "data/data/remoto.cibernoid.api/files/str.txt";



char url[]="http://192.168.1.186:8084/ServerCiberNoid_1/webresources/claves";
//char url[]="http://servercibernoidpruebas.herokuapp.com/webresources/claves";



//JSON
string paramsToJson(PUCHAR  idFile, PUCHAR  idUser, PUCHAR  grupo_boolean,PUCHAR  operador, PUCHAR  lat, PUCHAR  lon, PUCHAR  hora, PUCHAR  dateMask, PUCHAR  fecha, PUCHAR  timeMask, PUCHAR  wifis){
    // document is the root of a json message
    rapidjson::Document document;
    // define the document as an object rather than an array
    document.SetObject();
    // create a rapidjson String type with similar syntax to std::vector
    rapidjson::Value idFile_(rapidjson::kStringType);
    idFile_.Set((const char*)idFile);
    rapidjson::Value idUser_(rapidjson::kStringType);
    idUser_.Set((const char*)idUser);
    rapidjson::Value grupo_boolean_(rapidjson::kStringType);
    grupo_boolean_.Set((const char*)grupo_boolean);
    rapidjson::Value operador_(rapidjson::kStringType);
    operador_.Set((const char*)operador);
    rapidjson::Value lat_(rapidjson::kStringType);
    lat_.Set((const char*)lat);
    rapidjson::Value lon_(rapidjson::kStringType);
    lon_.Set((const char*)lon);
    rapidjson::Value hora_(rapidjson::kStringType);
    hora_.Set((const char*)hora);
    rapidjson::Value dateMask_(rapidjson::kStringType);
    dateMask_.Set((const char*)dateMask);
    rapidjson::Value fecha_(rapidjson::kStringType);
    fecha_.Set((const char*)fecha);
    rapidjson::Value timeMask_(rapidjson::kStringType);
    timeMask_.Set((const char*)timeMask);
    rapidjson::Value wifis_(rapidjson::kStringType);
    wifis_.Set((const char*)wifis);


    // must pass an allocator when the object may need to allocate memory
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    document.AddMember("idFile",idFile_, allocator);
    document.AddMember("idUser",idUser_, allocator);
    document.AddMember("grupo",grupo_boolean_, allocator);
    document.AddMember("operador",operador_, allocator);
    document.AddMember("lat",lat_, allocator);
    document.AddMember("lon",lon_, allocator);
    document.AddMember("hora",hora_, allocator);
    document.AddMember("dateMask",dateMask_, allocator);
    document.AddMember("fecha",fecha_, allocator);
    document.AddMember("timeMask",timeMask_, allocator);
    document.AddMember("wifis",wifis_, allocator);

    StringBuffer strbuf;
    Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);
    std::cout << strbuf.GetString() << std::endl;
    return strbuf.GetString();    

}



PUCHAR  get_idUser(){
    FILE *fp;
    char var[40];
    int varInt=0;
    PUCHAR  idUser;
    fp = popen("whoami", "r");
    while (fgets(var, sizeof(var), fp) != NULL) {
	     for (int i = 0; i < 40; ++i){    
        		varInt += var[i];
        		if(var[i]==10) break;
        }
    }
    pclose(fp);
    std::ostringstream stream_idUser;
  	stream_idUser << varInt;
  	idUser = (PUCHAR )malloc(stream_idUser.str().length()+1);
  	strcpy((char*)idUser, stream_idUser.str().c_str());
    return idUser;
}


PUCHAR  get_wifi(){
    FILE *fp;
    char var[40];
    int m = 1;
    PUCHAR  list;
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
    list = (PUCHAR )malloc(myString.length()+1);
    strcpy((char*)list,myString.c_str());
    return list;
}


PUCHAR  get_lat(){
    FILE* fp;
    PUCHAR  gps_lat;
    char var[10];
    //fp = popen("dumpsys location|grep gps\ Location|awk '{print$3}'|cut -f 1 -d\",\"", "r");
    fp = popen("dumpsys location|grep Latitude | head -n 1 | awk '{print$1}'|cut -f 2 -d\"=\"", "r");

    while (fgets(var, sizeof(var), fp) != NULL) {  
        //gps_lat = (PUCHAR )var;
        std::ostringstream stream_gps;
        stream_gps << var;
        gps_lat = (PUCHAR )malloc(stream_gps.str().length()+1);
        strcpy((char*)gps_lat, stream_gps.str().c_str());
        //printf("lat %s", var);
        break;
        
    }
    pclose(fp);
    
    return gps_lat;
}

PUCHAR  get_lon(){
    FILE* fp;
    PUCHAR  gps_lon;
    char var[10];
    fp = popen("dumpsys location|grep Latitude | head -n 1 | awk '{print$2}'|cut -f 2 -d\"=\"", "r");
    while (fgets(var, sizeof(var), fp) != NULL) {  
        std::ostringstream stream_gps;
        stream_gps << var;
        gps_lon = (PUCHAR )malloc(stream_gps.str().length()+1);
        strcpy((char*)gps_lon, stream_gps.str().c_str());

        break;
    }
    pclose(fp);
    
    return gps_lon;
}


PUCHAR  get_operador(){	
  FILE *fp;
  char var[40];
  int i=0;
  PUCHAR  operador;
  fp = popen("dumpsys telephony.registry|grep mServiceState|awk '{print$3}'", "r");
  while (fgets(var, sizeof(var), fp) != NULL) { 
         //printf(" %s", var);
        std::ostringstream stream_operador;
        for ( i= 0; i < 40; ++i){
            if(var[i]==10){
              break;  
            }
            stream_operador << var[i];            
            
        }  
        operador = (PUCHAR )malloc(stream_operador.str().length()+1);
        strcpy((char*)operador, stream_operador.str().c_str());

  }
  pclose(fp);
  return operador;
}


PUCHAR  create_fileID(){
	int min = 0;
	int max = 32727;

	std::random_device rd;    
	std::mt19937 rng(rd());   
	std::uniform_int_distribution<int> uni(min,max); 
	auto random_integer = uni(rng);
	
    PUCHAR  s_rand;
    std::stringstream stream_rand;
  	stream_rand << random_integer;
  	s_rand = (PUCHAR )malloc(stream_rand.str().length()+1);
  	strcpy((char*)s_rand, stream_rand.str().c_str());
    return s_rand;

}

PUCHAR  get_creationDate(){
  
	FILE *fp;
    char var[11];
    int i;
    PUCHAR  date;
    fp = popen("date +\"%Y-%m-%d\"", "r");
    while (fgets(var, sizeof(var), fp) != NULL) {  
        
        std::stringstream stream_date;
        
        for ( i= 0; i < 40; ++i){
            if(var[i]==10){
              break;  
            }
            stream_date << var[i];            
            
        }  

        date = (PUCHAR )malloc(stream_date.str().length()+1);
        strcpy((char*)date, stream_date.str().c_str());        
        break;
     }

    return date;
	
}

PUCHAR  get_curl(PUCHAR  idFile, PUCHAR  idUser, PUCHAR  group,PUCHAR  operador, PUCHAR  lat, PUCHAR  lon, PUCHAR  hora, PUCHAR  dateMask, PUCHAR  fecha, PUCHAR  timeMask, PUCHAR  wifis){
  
    FILE *fp;
    char var[700];
    //char list[800];
    PUCHAR  s_curl;
    int i;
    int l=0;
    printf("F %s\n", (const char*)idFile);
    printf("U %s\n", (const char*)idUser);
    printf("op %s\n", (const char*)operador);
    printf("l %s\n", (const char*)lat);
    printf("l %s\n", (const char*)lon);
    printf("h %s\n", (const char*)hora);
    printf("d %s\n", (const char*)dateMask);
    printf("f %s\n", (const char*)fecha);
    printf("t %s\n", (const char*)timeMask);
    printf("w %s\n", (const char*)wifis);

    
    char command[2000];
    snprintf(command, 2000,"curl -H \"Content-Type: application/json\" -X POST -d '{ \"idFile\": %s, \"idUser\": %s, \"grupo\": %s, \"operador\":\"%s\", \"lat\": \"%s\", \"lon\": \"%s\", \"hora\": \"%s\",\"dateMask\": %s, \"fecha\": \"%s\", \"timeMask\": %s, \"wifis\": \"%s\" }' %s",(const char*)idFile,(const char*) idUser,(const char*) group,(const char*) operador, (const char*) lat, (const char*) lon, (const char*) hora,(const char*) dateMask, (const char*) fecha, (const char*) timeMask, (const char*) wifis,(const char*) url);
    //http://192.168.1.186:8084/ServerCiberNoid_1/webresources/claves
    printf(" %s\n",command );
    
    fp = popen(command, "r");

    if ( fp == NULL ) 
    {
      printf("error");
      return  (PUCHAR )"error";
    }       
        while (fgets(var, sizeof(var), fp) != NULL) { 
          printf(" %s\n",var);          
          std::stringstream stream_var;
          stream_var << var;

          s_curl = (PUCHAR )malloc(stream_var.str().length()+1);
          strcpy((char*)s_curl, stream_var.str().c_str());
    
        }   
    return s_curl;
  
}

PUCHAR  getfield(char* line, int num){
		std::string myString;	
        std::stringstream ss;
        int i;
        int m = 0;
        for ( i= 0; i < 40; ++i){
        	if(m==num-1 && line[i] != 44){            	
            	ss << line[i]; 
            }
            if(line[i] == 44|| m>=num) {
                m++;
            }          
            else{           
                                 
            }    
        }      
        myString += ss.str().c_str();                
        PUCHAR  field = (PUCHAR )malloc(myString.length()+1);
    	strcpy((char*)field,myString.c_str()); 
    	printf("%s\n", field);
    	return  field;          
 }
     

PUCHAR*  get_app(){      
            
            FILE *fp;
            char buff[40];
            int n=4;
            char str[n];
            int ret;
                     
            /// Read the file with the string and close it
             
            fp = fopen(filename, "r");
            if (fp==NULL) {fputs ("File error",stderr);exit (1);}
            fgets(buff, 40, (FILE*)fp);
           

            fclose(fp);
            ret = remove(filename);            

            if(ret == 0) {
              //printf("File deleted successfully\n");            
            }else{
              printf("Error: unable to delete the files\n");
            }           
            
            //group
            s[0] = (PUCHAR )malloc(sizeof(getfield(buff,1))+1);
            s[0]=getfield(buff,1);                       
            //timeMask
            s[1] = (PUCHAR )malloc(sizeof(getfield(buff,2))+1);
            s[1]=getfield(buff,2);
            //dateMask
            s[2] = (PUCHAR )malloc(sizeof(getfield(buff,3))+1);
            s[2]=getfield(buff,3);
            //startWorday
            s[3] = (PUCHAR )malloc(sizeof(getfield(buff,4))+1);
            s[3]=getfield(buff,4);                       
                  
            return s;
    }

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




PUCHAR*   getChallengeProtectParams(){
  FILE *f; 
  PUCHAR  date;
  f = popen("svc wifi enable", "r");
  pclose(f);
  int pid;
  pid = fork();
  switch(pid)
  {
      case -1:
          perror("Cannot create the child process\n");
          break;
      case 0:
          execl("/system/bin/sh", "sh", "-c", "am start -W -n remoto.cibernoid.api/remoto.cibernoid.api.MainActivity", (char *)NULL);
          break;
      default:

         while(existsFile(filename)==1){
         	  printf("%i",existsFile(filename));
              wait(NULL);
              sleep(3);                      
          
          } 
          FILE* fp;
          fp = popen("am force-stop remoto.cibernoid.api", "r");
          pclose(fp);       
          
  }
  PUCHAR*  app=get_app();
  //idUser
  environment_params[0] = get_idUser();  
  //group
  environment_params[1] = app[0];
  //operador
  environment_params[2] = get_operador();
  //lat
  environment_params[3] = get_lat();
  //lon
  environment_params[4] = get_lon();
  //startWorkday
  environment_params[5] = app[3];
  //dateMask
  environment_params[6]= app[2];
  //creationDate
  environment_params[7] = get_creationDate();
  //timeMask
  environment_params[8]= app[1];
  //wifi
  environment_params[9] = get_wifi(); 
 printf("getChallengeProtectParams");
  return environment_params;

}

PUCHAR*  getChallengeUnProtectParams(){
  FILE *f; 
  PUCHAR  date;
  f = popen("svc wifi enable", "r");
  pclose(f);
  
  environment_params[0] = get_idUser();
  //environment_params[1] = get_group();
  environment_params[1] = get_operador();
  environment_params[2] = get_lat();
  environment_params[3] = get_lon();
  //environment_params[4] = get_startWorkday();
  //environment_params[6]= get_dateMask();
  //environment_params[4] = get_creationDate();
  //environment_params[8]= get_timeMask();
  environment_params[4] = get_wifi(); 
  printf("getChallengeUnProtectParams");  
 
  return environment_params;


}



PUCHAR*  executeParam(){
    challenge_params[1] = create_fileID();   
    getChallengeProtectParams();
    //get_curl(idFile,idUser,group,operador,lat,lon,startWorkday,dateMask,creationDate,timeMask,wifi)
    const char* json = (const char*) get_curl(
    	challenge_params[1],
    	environment_params[0],
    	environment_params[1],
    	environment_params[2],
    	environment_params[3],
    	environment_params[4],
    	environment_params[5],
    	environment_params[6],
    	environment_params[7],
    	environment_params[8],
    	environment_params[9]);
    rapidjson::Document document;
    document.Parse(json);   
    std::string c;
    c += document["claveOperador"].GetString();
    c += document["claveGPS"].GetString();
    c += document["claveHora"].GetString();
    c += document["claveFecha"].GetString();
    c += document["claveWifi"].GetString(); 

    challenge_params[0] = (PUCHAR )malloc(c.length()+1);
    strcpy((char*)challenge_params[0],c.c_str());
    challenge_params[2] = environment_params[1]; //group
    challenge_params[3] = environment_params[6]; //dateMask
    challenge_params[4] = environment_params[7]; //creationDate
    challenge_params[5] = environment_params[8]; //timeMask
    challenge_params[6] = environment_params[5]; //startWorkday

    printf("Clave %s\n", challenge_params[0]);
    printf("Clave %s\n", challenge_params[1]);
    printf("Clave %s\n", challenge_params[2]);
    printf("Clave %s\n", challenge_params[3]);
    printf("Clave %s\n", challenge_params[4]);
    printf("Clave %s\n", challenge_params[5]);
    printf("Clave %s\n", challenge_params[6]);

    
    
    return challenge_params;
    
}

PUCHAR  execute(PUCHAR*  parametrosXml){  	

  	/// Calling the internal function
  	getChallengeUnProtectParams();
  	//get_curl(idFile,idUser,group,operador,lat,lon,startWorkday,dateMask,creationDate,timeMask,wifi)
    const char* json = (const char*) get_curl(
    	parametrosXml[1],
    	environment_params[0],
    	parametrosXml[2],
    	environment_params[1],
    	environment_params[2],
    	environment_params[3],
    	parametrosXml[6],
    	parametrosXml[3],
    	parametrosXml[4],
    	parametrosXml[5],
    	environment_params[4]);
    rapidjson::Document document;
    document.Parse(json);
    std::string c;
    c += document["claveOperador"].GetString();
    c += document["claveGPS"].GetString();
    c += document["claveHora"].GetString();
    c += document["claveFecha"].GetString();
    c += document["claveWifi"].GetString();
    key = (PUCHAR )malloc(c.length()+1);
    strcpy((char*)key,c.c_str());
    printf("%s\n", key);
    return key;

}

PUCHAR*  getParamNames(){
  string fileID= "fileID";
  string timeMask="timeMask";
  string dateMask="dateMask";
  string group="group";
  string date="date";
  string startWorkday="startWorkday";

  string name;
  
    for (int i = 0; i < 6; ++i)
    {
    	switch(i){
    		case 0:
    			name=fileID;
    			break;
    		case 1:
    			name=group;    			
    			break;
            case 2:
            	name=date;            	               
            break;
            case 3:
                name=dateMask; 
            break;
            case 4:
                name=timeMask;
            break;
            case 5:
                name=startWorkday;
            break;
    		default:
    			name = "error";
    			break;

    	}
  		code_params_names[i] = (PUCHAR )malloc(name.length()+1);
  		strcpy((char*)code_params_names[i], name.c_str());
    }
 
  return code_params_names;

}

int getNParams(){
  return 6;
}


//curl -H "Content-Type: application/json" -X POST -d '{ "idFile": 0, "idUser": 54546, "grupo": false, "operador": "operador", "lat": 0.000000, "lon": 0.000000, "hora": "08:00", "fecha": "2017-03-04", "timeMask": 2, "wifis": "wifi1,canal,potencia;wifi2,..." }' http://192.168.1.184:8084/ServerCiberNoid_1/webresources/claves 
//http://developer.famoco.com/Android_development/ADB_commands/
//https://android.stackexchange.com/questions/120611/how-to-check-my-phone-hardware-specs-on-android-terminal-emulator
