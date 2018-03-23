#!/bin/bash

#Cambiar PATH al path del NDK
export PATH=/home/user/Documentos/android_compilar/my-android-toolchain/bin:$PATH
export CXX=arm-linux-androideabi-gcc

$CXX -fPIC -c -o pruebas_SO.o qrAnChallenge.c																																										
$CXX -Wall -shared -fPIC -o libQr_Android_challenge.so pruebas_SO.o qrAnChallenge.h 
$CXX -pie -o "qr" main.c  -L. -lQr_Android_challenge

