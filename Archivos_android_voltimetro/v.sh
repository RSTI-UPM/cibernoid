#!/bin/bash

#Cambiar PATH al path del NDK
export PATH=/home/user/Documentos/android_compilar/my-android-toolchain_gcc/bin:$PATH
export CXX=arm-linux-androideabi-g++

SCRIPT=$(readlink -f $0)
PWD=`dirname $SCRIPT`

$CXX -fPIC -c -o pruebas_SO.o volAnchallenge.cpp -lc -I/${PWD} -L/${PWD}/Librerias-armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d 																																								
$CXX -Wall -shared -fPIC -o libVol_Android_challenge.so pruebas_SO.o volAnchallenge.h -lc -I/${PWD} -L/${PWD}/Librerias-armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d
$CXX -pie -o "v" main.cpp -I/${PWD} -L/${PWD}/Librerias-armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d -L. -lVol_Android_challenge

