#!/bin/bash

#Cambiar PATH al path del NDK
export PATH=/home/user/Documentos/android_compilar/my-android-toolchain_gcc/bin:$PATH
export CXX=arm-linux-androideabi-g++

SCRIPT=$(readlink -f $0)
PWD=`dirname $SCRIPT`

$CXX -fPIC -c -o pruebas_SO.o imAnchallenge.cpp	-lc -I/${PWD} -L/${PWD}/Librerias-armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d 																																								
$CXX -Wall -shared -fPIC -o libIm_Android_challenge.so pruebas_SO.o imAnchallenge.h -lc -I/${PWD} -L/${PWD}/Librerias-armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d
$CXX -pie -o "im" main.cpp -I/${PWD}   -L/${PWD}/Librerias-armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d -L. -lIm_Android_challenge

