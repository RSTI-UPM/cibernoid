#!/bin/bash

#Cambiar PATH al path del NDK
export PATH=/home/user/Documentos/android_compilar/my-android-toolchain_gcc/bin:$PATH
export CXX=arm-linux-androideabi-g++ 

$CXX -fPIC -c -o pruebas_SO.o apiAnChallenge.cpp -std=c++11 
$CXX -Wall -shared -fPIC -o libApi_Android_challenge.so pruebas_SO.o apiAnChallenge.h -std=c++11
$CXX -pie -o "api" main.cpp  -L. -lApi_Android_challenge -std=c++11



