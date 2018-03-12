#!/bin/bash

# PATH=/home/mercurio/Documentos/android_compilar/my-android-toolchain/bin:$PATH
#export CXX=i686-linux-android-gcc
export PATH=/home/dell/Documentos/android_compilar/my-android-toolchain/bin:$PATH
export CXX=arm-linux-androideabi-gcc

$CXX -fPIC -c -o pruebas_SO.o qrAnChallenge.c																																										
$CXX -Wall -shared -fPIC -o libQr_Android_challenge.so pruebas_SO.o qrAnChallenge.h 
$CXX -pie -o "qr" main.c  -L. -lQr_Android_challenge

