#include "apiAnChallenge.h"
#include <stdio.h>
using namespace std;

int main(int argc, char** argv)
{
  //printf("Return (executeParam): %s\n", executeParam()[0]);
  //printf("Return (executeParam): %s\n", executeParam()[1]);
  unsigned char* key = execute(executeParam());


  //printf("return (execute): %s\n", execute(executeParam()));
   printf("return (execute): %s\n", key);


  printf("return (getParamNames): %s\n", getParamNames()[0]);
  printf("return (getParamNames): %s\n", getParamNames()[1]);
  printf("return (getParamNames): %s\n", getParamNames()[2]);

  return 0;

}

/*int  main(int argc, char **argv){
  printf("Empezando");
	
	unsigned char** hola =executeParam();
  	printf("return (executeParam): %s\n", hola[0]);
  	printf("c1: %s\n", hola[1]);
  	printf("c2: %s\n", hola[2]);
  	printf("c3: %s\n", hola[3]);
  	printf("c4: %s\n", hola[4]);
   

  	return 0;

}*/