#!/bin/bash

#Cambiar PATH al path del NDK
export PATH=/home/dell/Documentos/android_compilar/my-android-toolchain_gcc/bin:$PATH
export CXX=arm-linux-androideabi-gcc

$CXX -fPIC -c -o pruebas_SO.o operadorAnChallenge.c											
$CXX -Wall -shared -fPIC -o libOperador_Android_challenge.so pruebas_SO.o operadorAnChallenge.h 
$CXX -pie -o "o" main.c  -L. -lOperador_Android_challenge

