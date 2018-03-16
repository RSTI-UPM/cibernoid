#include "surfAnchallenge.h"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

unsigned char* challenge_params[2];
unsigned char* key;
unsigned char* code_params_names[1];
char photoname[] = "/sdcard/photo.jpg";

int minHessian = 400;
double minimo = 0.195;
int size = 30;

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


unsigned char** getChallengeProtectParams(){

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

unsigned char** getChallengeUnProtectParams(){
  
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



unsigned char ** executeParam(){

  /// Calling the internal function
  getChallengeProtectParams();

  Mat src_base, descriptors_1;

  /// Path to the image file (/storage/emulated/0/pic.jpg)
  src_base = imread( photoname, 1 ); 

  int ret = remove(photoname);
  if(ret == 0) {
      printf("File deleted successfully\n");
   }else{
      printf("Error: unable to delete the file\n");
   }



  
   //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptor
   //int minHessian = 400;
   Ptr<SURF> detector = SURF::create();
   detector->setHessianThreshold(minHessian);
   std::vector<KeyPoint> keypoints_1;   
   detector->detectAndCompute( src_base, Mat(), keypoints_1, descriptors_1);

  

  /// We pass the descriptor as code parameters
  FileStorage fs(".xml", FileStorage::WRITE + FileStorage::MEMORY);
  fs << "mymatrix" << descriptors_1;
  string buf = fs.releaseAndGetString();
  challenge_params[1] = (unsigned char*)malloc(buf.length()+1);  
  strcpy((char*)challenge_params[1], buf.c_str());
  std::stringstream strs;
  cv::Size size = descriptors_1.size();

  strs << strs << size.width << size.height;;
  string subkey = strs.str();  
 
  challenge_params[0] = (unsigned char*)malloc(subkey.length()+1);
  strcpy((char*)challenge_params[0], subkey.c_str()); 
  
  printf("%i , %i\n", size.width, size.height); 

  return challenge_params;
}

unsigned char* execute(unsigned char** parametrosXml){

  Mat src, descriptors_1;

  /// We convert the parameter (descriptor) to a Mat matrix
  //printf("%s\n",parametrosXml[1]);
  std::string str;
  str.append(reinterpret_cast<const char*>(parametrosXml[1]));
  FileStorage fs(str, FileStorage::READ + FileStorage::MEMORY);
  fs["mymatrix"] >> descriptors_1;
  /// Calling the internal function
  getChallengeUnProtectParams();

   src = imread( photoname, 1 );
   /// Path to the image file 



  int ret = remove(photoname);
  if(ret == 0) {
      printf("File deleted successfully\n");
   }else{
      printf("Error: unable to delete the file\n");
   }  


    //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
  
   Ptr<SURF> detector = SURF::create();
   detector->setHessianThreshold(minHessian);
   std::vector<KeyPoint> keypoints_2;
   Mat descriptors_2;
   detector->detectAndCompute( src, Mat(), keypoints_2, descriptors_2);

    //-- Step 2: Matching descriptor vectors using FLANN matcher
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match( descriptors_1, descriptors_2, matches);

    //--Step 3: Calculate the lowest (30 points=size) Euclidean distance

    std::vector<double> vector;

    for(int t=0; t<size; t++){
      vector.push_back(100.00);
    }

  
    for( int k = 0; k < descriptors_1.rows; k++ ){ 
      double dist = matches[k].distance;
      for(int l=0 ; l<size ;l++){
        try{
          if (dist<vector[l]){
            vector.erase(vector.begin() + l);
            vector.insert(vector.begin() + l, dist);
            break;
          }
        }catch(std::out_of_range o){
          printf("%s\n",o.what());
        }
      } 
    }

  double Total= 0.00;
  for (unsigned m=0; m<vector.size(); ++m){
    Total += vector[m];
  }



  if (Total/size < minimo ){
    std::stringstream strs;
    cv::Size size = descriptors_1.size();
   
    strs << size.width << size.height;
    string subkey = strs.str();
 

  	key = (unsigned char*)malloc(subkey.length()+1);
    strcpy((char*)key, subkey.c_str());
  	
  }
  else{
  	string false_subkey = "Incorrect";
    key = (unsigned char*)malloc(false_subkey.length()+1);
    strcpy((char*)key, false_subkey.c_str());	 

  }



  /*
  std::stringstream stream_key;
  stream_key << correlation ;
  string sub_key = stream_key.str();
  key = (unsigned char*)malloc(sub_key.length()+1);
  strcpy((char*)key, sub_key.c_str());
  */
  //execl("/system/bin/sh", "sh", "-c", "am force-stop cibernoid.multimedia.camara", (char *)NULL);
  printf("%s\n",key);

  return key;
  }


unsigned char ** getParamNames(){
  
  string name = "surf";
  code_params_names[0] = (unsigned char*)malloc(name.length()+1);
  strcpy((char*)code_params_names[0], name.c_str());

  return code_params_names;
}

int getNParams(){

  return 1;
}