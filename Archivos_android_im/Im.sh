#!/bin/bash

export PATH=/home/dell/Documentos/android_compilar/my-android-toolchain_gcc/bin:$PATH
export CXX=arm-linux-androideabi-g++

$CXX -fPIC -c -o pruebas_SO.o imAnchallenge.cpp	-lc -I/home/dell/Documentos/Retos/opencv-3.3.1/platforms/build_android_arm/install/sdk/native/jni/include  -L/home/dell/Documentos/Retos/opencv-3.3.1/platforms/build_android_arm/install/sdk/native/libs/armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d 																																								
$CXX -Wall -shared -fPIC -o libIm_Android_challenge.so pruebas_SO.o imAnchallenge.h -lc -I/home/dell/Documentos/Retos/opencv-3.3.1/platforms/build_android_arm/install/sdk/native/jni/include  -L/home/dell/Documentos/Retos/opencv-3.3.1/platforms/build_android_arm/install/sdk/native/libs/armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d
$CXX -pie -o "im" main.cpp -I/home/dell/Documentos/Retos/opencv-3.3.1/platforms/build_android_arm/install/sdk/native/jni/include  -L/home/dell/Documentos/Retos/opencv-3.3.1/platforms/build_android_arm/install/sdk/native/libs/armeabi-v7a -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d -L. -lIm_Android_challenge

