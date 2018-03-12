#include "wifiAnChallenge.h"
#include <stdio.h>

int main(int argc, char** argv)
{
  //printf("Return (executeParam): %s\n", executeParam()[0]);
  //printf("Return (executeParam): %s\n", executeParam()[1]);
  printf("return (execute): %s\n", execute(executeParam()));
  printf("return (getNParams): %i\n", getNParams());
  return 0;

}
