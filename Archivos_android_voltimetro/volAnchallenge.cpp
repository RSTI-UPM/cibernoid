#include "volAnchallenge.h"

using namespace std;
using namespace cv;

PUCHAR challenge_params[2];
PUCHAR key;
PUCHAR code_params_names[1];
char photoname[] = "/sdcard/photo.jpg";
double minimo = 10;

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

  Mat src_base, crop, gris, result, result2, canny, oscuro, cropGris;

  vector<Vec4i> hierarchy;
  vector<vector <Point> > contours;

  /// Path to the image file (/storage/emulated/0/pic.jpg)
  src_base = imread( photoname, 1 );
  FILE* fp;
  char command[80];
  snprintf(command, 80,"rm %s", photoname);
  printf("%s\n", command);
  fp = popen(command, "r");
  pclose(fp);

  //OPERACIONES CON LOS src_base
  cvtColor( src_base, gris, COLOR_RGB2GRAY);
  threshold(gris,oscuro,50,255,1); //se ponen en blanco las cosas oscuras (menor que 50 en la escala gris)
  Canny(gris, canny, 50, 150, 3);//deteccion de bordes en la figura con gris
  
  result = src_base.clone();
  result2 = src_base.clone();
  //HOUGH CIRCLES DETECTION
  vector<Vec3f> circles;
  HoughCircles( gris, circles, CV_HOUGH_GRADIENT, 1, gris.rows/4, 170, 70, 15,  238 );
  //hace la dteccion desde la img gris
  //gris.rows/12 es la minima distancia entre circulos (para que no detecte circulos juntos)
  //200, 100 es el threshold superior e inferior del algoritmo. siempre uno el doble
  //mayor therhold:mas dificil detectar
  //los dos ultimos: minimo radio, maximo radio (0: indefinido)
  //tener en cuenta que el ancho de la img es de 630 px, para los radios
  //los puntos se miden en px (x), px(y)

  //Variables del voltaje
  double voltaje=0;
  int j = 0;

  for( size_t i = 0; i < circles.size(); i++ )
    //obtiene para cada circulo la x del centro, la y y el radio
    {
      
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

         
    if(((center.x - radius) > 0) && ((center.x + radius) < src_base.cols) && ((center.y - radius) > 0) && ((center.y + radius) < src_base.rows)){
    //ajustamos el crop que cortamos del voltimetro, para mayor precision
    //posteriormente cuando se requiera detectar la aguja

    int alturaRect = cvRound(radius + (0.1*radius));
    int yRect = cvRound(center.y -radius + (0.3*radius));
    //EN EL ELSE DE ESTE IF HAY QUE DECIR AL BRAZO QUE SE MUEVA A UN LADO U OTRO.
    //SERIA IDEAL ENVIAR UN VALOR QUE SEA EL MODO DE FUNCIONAMINETO DEL BRAZO
            
    crop = result2(Rect((center.x - radius - 5), yRect , ((2*radius)+10) , alturaRect ));
    //1º: el punto a la izq y arriba, 2º width, 3º height
    //operaciones con el crop

    Canny(crop, cropGris, 50, 150,3); //HAY QUE HACER UN CANNY PARA PODER USAR HOUGHLINES
    //aplicamos el algoritmo de Hough para detectar lineas
    vector<Vec4i> lines;
    int minHoughLine = cvRound(cropGris.cols/6); //max x entre 4

    HoughLinesP(cropGris, lines, 1, CV_PI/180, 32, minHoughLine, 6);
    //solo cambiamos los tres ultimos parametros.
    //1º: threshold (mayor, mas dificil), 2º: minLineLength
    //2º: maxLineGap: max espacio entre dos ptos ded una linea
    
    //printf("%zu\n", lines.size());
    for( size_t i = 0; i < lines.size(); i++ )
        {
          //Elegimos las lineas que nos gusten
      int modulo = sqrt(pow((lines[i][0]-lines[i][2]), 2) + pow((lines[i][1]-lines[i][3]), 2));
      
      if(lines[i][1] > lines[i][3] ){ //lines[i][0], [1] es el punto de abajo
        //double tangente = (lines[i][1] - lines[i][3]) / (lines[i][0] - lines[i][2]); //y entre x
        double ytan = lines[i][1] - lines[i][3];
        double xtan = lines[i][0] - lines[i][2];
        double angulo = atan2(ytan, xtan);
        //printf("%f\n",angulo );
        //0 voltios es unos 0.523 (30º), 20 voltios unos 150º (2.62) - se hace la conversión
        if((angulo > 0.5)&&(angulo < 2.45)){ //eliminamos las lineas que no sean la aguja
          if((modulo > (int)(cropGris.cols/6)) &&  (modulo < (int)(cropGris.cols/1.5)) ){
            line( crop, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, CV_AA );
            //cout << angulo << endl;
            double voltaje2 = ((angulo-0.75)*20)/1.64;
            voltaje += voltaje2;            
            j++;
          
                  
          }
        }
      }
      else{ //lines[i][2], [3] es el punto de abajo
        double ytan = lines[i][3] - lines[i][1];
        double xtan = lines[i][2] - lines[i][0];
        double angulo = atan2(ytan, xtan);
        printf("%f\n",angulo );
        if((angulo > 0.5)&&(angulo < 2.45)){
          if((modulo > (int)(cropGris.cols/6)) &&  (modulo < (int)(cropGris.cols/1.5)) ){
            line( crop, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, CV_AA );
            double voltaje2 = ((angulo-0.75)*20)/1.64;
            voltaje += voltaje2;            
            j++;
      
                
           
          }
        }
      }
        }
    }        
        
  }
  std::ostringstream stream_param;
  if(j==0){
      printf("Error en la lectura del voltimetro");
      stream_param << "Error";
    }else{

      voltaje = voltaje/j;
      printf("El valor del voltaje es %f\n",voltaje ); 
      if (voltaje >= minimo){
          stream_param << 10;
        }
      else {
          stream_param << 0;
        }

  } 
   
  
  std::string subkey = stream_param.str();
  challenge_params[0] = (PUCHAR)malloc(subkey.length()+1);
  strcpy((char*)challenge_params[0], subkey.c_str());


  return challenge_params;
}

PUCHAR execute(PUCHAR* parametrosXml){

 

  /// We convert the parameter (histogram) to a Mat matrix
  /*std::string str;
  str.append(reinterpret_cast<const char*>(parametrosXml[1]));
  FileStorage fs(str, FileStorage::READ + FileStorage::MEMORY);
  fs["mymatrix"] >> hist_base;
*/
  /// Calling the internal function
  getChallengeUnProtectParams();

  Mat src_base, crop, gris, result, result2, canny, oscuro, cropGris;

  vector<Vec4i> hierarchy;
  vector<vector <Point> > contours;

  /// Path to the image file (/storage/emulated/0/pic.jpg)
  src_base = imread( photoname, 1 );
  FILE* fp;
  char command[80];
  snprintf(command, 80,"rm %s", photoname);
  printf("%s\n", command);
  fp = popen(command, "r");
  pclose(fp);

  //OPERACIONES CON LOS src_base
  cvtColor( src_base, gris, COLOR_RGB2GRAY);
  threshold(gris,oscuro,50,255,1); //se ponen en blanco las cosas oscuras (menor que 50 en la escala gris)
  Canny(gris, canny, 50, 150, 3);//deteccion de bordes en la figura con gris
  
  result = src_base.clone();
  result2 = src_base.clone();
  //HOUGH CIRCLES DETECTION
  vector<Vec3f> circles;
  HoughCircles( gris, circles, CV_HOUGH_GRADIENT, 1, gris.rows/4, 170, 70, 15,  238 );
  //hace la dteccion desde la img gris
  //gris.rows/12 es la minima distancia entre circulos (para que no detecte circulos juntos)
  //200, 100 es el threshold superior e inferior del algoritmo. siempre uno el doble
  //mayor therhold:mas dificil detectar
  //los dos ultimos: minimo radio, maximo radio (0: indefinido)
  //tener en cuenta que el ancho de la img es de 630 px, para los radios
  //los puntos se miden en px (x), px(y)

  //Variables del voltaje
  double voltaje=0;
  int j = 0;

  for( size_t i = 0; i < circles.size(); i++ )
    //obtiene para cada circulo la x del centro, la y y el radio
    {
      
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

         
    if(((center.x - radius) > 0) && ((center.x + radius) < src_base.cols) && ((center.y - radius) > 0) && ((center.y + radius) < src_base.rows)){
    //ajustamos el crop que cortamos del voltimetro, para mayor precision
    //posteriormente cuando se requiera detectar la aguja

    int alturaRect = cvRound(radius + (0.1*radius));
    int yRect = cvRound(center.y -radius + (0.3*radius));
    //EN EL ELSE DE ESTE IF HAY QUE DECIR AL BRAZO QUE SE MUEVA A UN LADO U OTRO.
    //SERIA IDEAL ENVIAR UN VALOR QUE SEA EL MODO DE FUNCIONAMINETO DEL BRAZO
            
    crop = result2(Rect((center.x - radius - 5), yRect , ((2*radius)+10) , alturaRect ));
    //1º: el punto a la izq y arriba, 2º width, 3º height
    //operaciones con el crop

    Canny(crop, cropGris, 50, 150,3); //HAY QUE HACER UN CANNY PARA PODER USAR HOUGHLINES
    //aplicamos el algoritmo de Hough para detectar lineas
    vector<Vec4i> lines;
    int minHoughLine = cvRound(cropGris.cols/6); //max x entre 4

    HoughLinesP(cropGris, lines, 1, CV_PI/180, 32, minHoughLine, 6);
    //solo cambiamos los tres ultimos parametros.
    //1º: threshold (mayor, mas dificil), 2º: minLineLength
    //2º: maxLineGap: max espacio entre dos ptos ded una linea
    
    //printf("%zu\n", lines.size());
    for( size_t i = 0; i < lines.size(); i++ )
        {
          //Elegimos las lineas que nos gusten
      int modulo = sqrt(pow((lines[i][0]-lines[i][2]), 2) + pow((lines[i][1]-lines[i][3]), 2));
      
      if(lines[i][1] > lines[i][3] ){ //lines[i][0], [1] es el punto de abajo
        //double tangente = (lines[i][1] - lines[i][3]) / (lines[i][0] - lines[i][2]); //y entre x
        double ytan = lines[i][1] - lines[i][3];
        double xtan = lines[i][0] - lines[i][2];
        double angulo = atan2(ytan, xtan);
        printf("%f\n",angulo );
        //0 voltios es unos 0.523 (30º), 20 voltios unos 150º (2.62) - se hace la conversión
        if((angulo > 0.5)&&(angulo < 2.45)){ //eliminamos las lineas que no sean la aguja
          if((modulo > (int)(cropGris.cols/6)) &&  (modulo < (int)(cropGris.cols/1.5)) ){
            line( crop, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, CV_AA );
            //cout << angulo << endl;
            double voltaje2 = ((angulo-0.75)*20)/1.64;
            voltaje += voltaje2;            
            j++;
          
                  
          }
        }
      }
      else{ //lines[i][2], [3] es el punto de abajo
        double ytan = lines[i][3] - lines[i][1];
        double xtan = lines[i][2] - lines[i][0];
        double angulo = atan2(ytan, xtan);
        
        if((angulo > 0.5)&&(angulo < 2.45)){
          if((modulo > (int)(cropGris.cols/6)) &&  (modulo < (int)(cropGris.cols/1.5)) ){
            line( crop, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, CV_AA );
            double voltaje2 = ((angulo-0.75)*20)/1.64;
            voltaje += voltaje2;
            printf("%f\n",voltaje2 );            
            j++;
      
                
           
          }
        }
      }
        }
    }        
        
  }
  std::ostringstream stream_key;
  if(j==0){
      printf("Error en la lectura del voltimetro");
      stream_key << "Error";
    }else{

      voltaje = voltaje/j;
      printf("El valor del voltaje es %f\n",voltaje ); 
      if (voltaje >= minimo){
          stream_key << 10;
        }
      else{
          stream_key << 0;
        }

  } 

  std::string sub_key = stream_key.str();
  key = (PUCHAR)malloc(sub_key.length()+1);
  strcpy((char*)key, sub_key.c_str());
  return key;
  }


PUCHAR* getParamNames(){
  
  return NULL;
}

int getNParams(){

  return 0;
}
