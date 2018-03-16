#include "imAnchallenge.h"

using namespace std;
using namespace cv;

PUCHAR challenge_params[2];
PUCHAR key;
PUCHAR code_params_names[1];
char photoname[] = "/sdcard/photo.jpg";
double correlation_base = 0.5;


int h_bins = 50; int s_bins = 60;
int histSize[] = { h_bins, s_bins };

// hue varies from 0 to 179, saturation from 0 to 255
float h_ranges[] = { 0, 180 };
float s_ranges[] = { 0, 256 };
const float* ranges[] = { h_ranges, s_ranges };

// Use the o-th and 1-st channels (H and S)
int channels[] = { 0, 1 };

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

PUCHAR* getChallengeProtectParams(){

  int pid;
  pid = fork();
  switch(pid)
  {
      case -1:
          perror("Cannot create the child process\n");
          break;
      case 0:
          execl("/system/bin/sh", "sh", "-c", "am start -W -n cibernoid.multimedia.camara/cibernoid.multimedia.camara.MainActivity", (char *)NULL);
          break;
      default:
           while(existsFile(photoname)==1){
            
              wait(NULL);
              sleep(3);                      
          
          } 
          FILE* fp;
  		  fp = popen("am force-stop cibernoid.multimedia.camara", "r");
  		  pclose(fp);
          return NULL;
  }
}

PUCHAR* getChallengeUnProtectParams(){
  
  int pid;
  pid = fork();
  switch(pid)
  {
      case -1: 
          perror("Cannot create the child process\n");
          break;
      case 0:
          execl("/system/bin/sh", "sh", "-c", "am start -W -n cibernoid.multimedia.camara/cibernoid.multimedia.camara.MainActivity", (char *)NULL);
          break;
      default:
          while(existsFile(photoname)==1){
            
              wait(NULL);
              sleep(3);                      
          
          } 
          FILE* fp;
  		  fp = popen("am force-stop cibernoid.multimedia.camara", "r");
  		  pclose(fp); 

          return NULL;
  }
}



PUCHAR* executeParam(){

  /// Calling the internal function
  getChallengeProtectParams();

  Mat src_base, hsv_base, hist_base;

  /// Path to the image file (/storage/emulated/0/pic.jpg)
  src_base = imread( photoname, 1 );
  

  int ret = remove(photoname);
  if(ret == 0) {
      printf("File deleted successfully\n");
   }else{
      printf("Error: unable to delete the file\n");
   }
	

  /// Convert the image to HSV format
  cvtColor( src_base, hsv_base, COLOR_BGR2HSV );
  
  /// H-S histogram and normalize
  calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
  normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Calculate Max value of the normalized histogram. We use it to generate the subkey.
  double min, max;
  cv::minMaxLoc(hist_base, &min, &max);

  cv::Size size = hist_base.size();  
  std::stringstream strs;
  strs << max << min << size.width << size.height;
 
  string subkey = strs.str();
  challenge_params[0] = (PUCHAR)malloc(subkey.length()+1);
  strcpy((char*)challenge_params[0], subkey.c_str());

  /// We pass the histogram as code parameters
  FileStorage fs(".xml", FileStorage::WRITE + FileStorage::MEMORY);
  fs << "mymatrix" << hist_base;
  string buf = fs.releaseAndGetString();
  challenge_params[1] = (PUCHAR)malloc(buf.length()+1);
  strcpy((char*)challenge_params[1], buf.c_str()); 
  

  //printf("%s\n",challenge_params[1]);


  return challenge_params;
}

PUCHAR execute(PUCHAR* parametrosXml){

  Mat src, hsv, hist, hist_base;

  /// We convert the parameter (histogram) to a Mat matrix
  //printf("%s\n",parametrosXml[1]);
  std::string str;
  str.append(reinterpret_cast<const char*>(parametrosXml[1]));
  FileStorage fs(str, FileStorage::READ + FileStorage::MEMORY);
  fs["mymatrix"] >> hist_base;

  /// Calling the internal function
  getChallengeUnProtectParams();

  /// Path to the image file
  src = imread( photoname, 1 );


  int ret = remove(photoname);
  if(ret == 0) {
      printf("File deleted successfully\n");
   }else{
      printf("Error: unable to delete the file\n");
   }


  double min, max;
  cv::minMaxLoc(hist_base, &min, &max);

  /// Generate the subkey (the max and min value)

  cv::Size size = hist_base.size();  
  std::stringstream strs;
  strs << max << min << size.width << size.height;
  string subkey = strs.str();
  /// Convert the image to HSV format
  cvtColor( src, hsv, COLOR_BGR2HSV );
  
  /// H-S histogram and normalize
  calcHist( &hsv, 1, channels, Mat(), hist, 2, histSize, ranges, true, false );
  normalize( hist, hist, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Compare histograms
  double correlation = compareHist( hist_base, hist, 0 );

  if (correlation > 0.5){

  	key = (PUCHAR)malloc(subkey.length()+1);
    strcpy((char*)key, subkey.c_str());
  	
  }
  else{
  	string false_subkey = "Incorrect";
    key = (PUCHAR)malloc(false_subkey.length()+1);
    strcpy((char*)key, false_subkey.c_str());	 

  }



  /*
  std::stringstream stream_key;
  stream_key << correlation ;
  string sub_key = stream_key.str();
  key = (PUCHAR)malloc(sub_key.length()+1);
  strcpy((char*)key, sub_key.c_str());
  */
  //execl("/system/bin/sh", "sh", "-c", "am force-stop cibernoid.multimedia.camara", (char *)NULL);
  printf("%s\n",key);

  return key;
  }


PUCHAR* getParamNames(){
  
  string name = "histograma";
  code_params_names[0] = (PUCHAR)malloc(name.length()+1);
  strcpy((char*)code_params_names[0], name.c_str());

  return code_params_names;
}

int getNParams(){

  return 1;
}
