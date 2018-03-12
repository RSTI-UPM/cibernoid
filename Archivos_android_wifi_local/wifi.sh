#!/bin/bash

export PATH=/home/dell/Documentos/android_compilar/my-android-toolchain_gcc/bin:$PATH
export CXX=arm-linux-androideabi-g++ 


$CXX -fPIC -c -o pruebas_SO.o wifiAnChallenge.cpp -std=c++11										
$CXX -Wall -shared -fPIC -o libWifi_Android_challenge.so pruebas_SO.o wifiAnChallenge.h -std=c++11
$CXX -pie -o "w" main.cpp  -L. -lWifi_Android_challenge -std=c++11

