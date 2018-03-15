#!/bin/bash

export PATH=/home/dell/Documentos/android_compilar/my-android-toolchain_gcc/bin:$PATH
export CXX=arm-linux-androideabi-g++

SCRIPT=$(readlink -f $0)
PWD=`dirname $SCRIPT`

$CXX -fPIC -c -o pruebas_SO.o surfAnchallenge.cpp -lc -I/${PWD}/2.4.13.5/jni/include -L/${PWD}/2.4.13.5/libs/armeabi-v7a -lopencv_gpu -lopencv_video -lopencv_calib3d -lopencv_ml -lopencv_legacy -lopencv_imgproc -lopencv_core -lopencv_features2d -lopencv_highgui -lopencv_nonfree -lopencv_flann -lopencv_objdetect -lopencv_photo -lopencv_ocl																																		
$CXX -Wall -shared -fPIC -o libSurf_Android_challenge.so pruebas_SO.o surfAnchallenge.h -lc -I/${PWD}/2.4.13.5/jni/include  -L/${PWD}/2.4.13.5/libs/armeabi-v7a -lopencv_gpu -lopencv_video -lopencv_calib3d -lopencv_ml -lopencv_legacy -lopencv_imgproc -lopencv_core -lopencv_features2d -lopencv_highgui -lopencv_nonfree -lopencv_flann -lopencv_objdetect -lopencv_photo -lopencv_ocl
$CXX -pie -o "surf" main.cpp -I/${PWD}/2.4.13.5/jni/include -L/${PWD}/2.4.13.5/libs/armeabi-v7a -lopencv_gpu -lopencv_video -lopencv_calib3d -lopencv_ml -lopencv_legacy -lopencv_imgproc -lopencv_core -lopencv_features2d -lopencv_highgui -lopencv_nonfree -lopencv_flann -lopencv_objdetect -lopencv_photo -lopencv_ocl -L. -lSurf_Android_challenge 


