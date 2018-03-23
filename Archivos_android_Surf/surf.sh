#!/bin/bash

#Cambiar PATH al path del NDK
export PATH=/home/user/Documentos/android_compilar/my-android-toolchain_gcc/bin:$PATH
export CXX=arm-linux-androideabi-g++

SCRIPT=$(readlink -f $0)
PWD=`dirname $SCRIPT`

$CXX -fPIC -c -o pruebas_SO.o surfAnchallenge.cpp -lc -I/${PWD}  -L/${PWD}/Librerias-armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d -lopencv_xfeatures2d -lopencv_ml -lopencv_shape -lopencv_flann -lopencv_video -lopencv_videoio 
$CXX -Wall -shared -fPIC -o libSurf_Android_challenge.so pruebas_SO.o surfAnchallenge.h -lc -I/${PWD}  -L/${PWD}/Librerias-armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d -lopencv_xfeatures2d -lopencv_flann -lopencv_ml -lopencv_shape -lopencv_video -lopencv_videoio
$CXX -pie -o "surf" main.cpp -I/${PWD}  -L/${PWD}/Librerias-armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d -lopencv_xfeatures2d -lopencv_ml -lopencv_shape -lopencv_video -lopencv_videoio -lopencv_flann -L. -lSurf_Android_challenge

