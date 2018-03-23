#Pasos a seguir para crear librería .so de Android

#Descargar NDK Android 
#NDK-> https://developer.android.com/ndk/downloads/older_releases.html?hl=es-419#ndk-12b-downloads 
#Más opciones para tener la librería lcrypto #https://wiki.openssl.org/index.php/Android , https://es.androids.help/q8664
#Instalar compilador de Android (#https://developer.android.com/ndk/guides/standalone_toolchain.html?hl=es-419#abi)
#(Path_de_ndk)/build/tools/make-standalone-toolchain.sh --arch=(arquitectura (x86, x86_64, arm, mips, mips_64)) --platform=(Ej.API_android, api23(6.0)) --install-dir=(Path_del_directorio_donde_se_quiere_guardar_las_herramientas_de_compilación) 
/home/user/Descargas/android-ndk-r12b/build/tools/make-standalone-toolchain.sh --arch=arm --platform=android-16 --install-dir=/home/user/Documentos/android_compilar/my-android-toolchain 

#instrucción de compilación
#Some options
#    -g - turn on debugging (so GDB gives more friendly output)
#    -Wall - turns on most warnings
#    -O or -O2 - turn on optimizations
#    -o <name> - name of the output file
#    -c - output an object file (.o)
#    -I<include path> - specify an include directory
#    -L<library path> - specify a lib directory
#    -l<library> - link with library lib<library>.a 


#Obtener los archivos .so de android 

#Descargar de drive los archivos de la carpeta
cd /cibernoid/Archivos_android_Api_remoto

#Crear la librería y ejecutable, ejecutar api.sh o estas líneas
#(Path de insalación de toolchain)/bin:$PATH
export PATH=/home/user/Documentos/android_compilar/my-android-toolchain/bin:$PATH
#herramienta de compilación, ver las opciones en el directorio anterior, el nombre depende de la arquitectura y la herramienta de compilación (gcc, g++, clang, clang++ ...)
#En este caso arm
export CXX=arm-linux-androideabi-g++

$CXX -fPIC -c -o pruebas_SO.o apiAnChallenge.cpp -std=c++11 
$CXX -Wall -shared -fPIC -o libApi_Android_challenge.so pruebas_SO.o apiAnChallenge.h -std=c++11
$CXX -pie -o "api" main.cpp  -L. -lApi_Android_challenge -std=c++11

#Para ejecutar en android

#Movil rooteado y conectado por usb al ordenador
#Install adb en el ordenador Ubuntu 16
sudo apt update
sudo apt install android-tools-adb
#Descargar curl android https://curl.haxx.se/download.html y descomprimir 
wget https://curl.haxx.se/gknw.net/7.40.0/dist-android/curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android.tar.gz
tar -xzvf curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android.tar.gz

#Para instalar, copia data/local/ssl y los ejecutables curl y openssl de data/local/bin 
adb push curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android/data/local/ssl/openssl.cnf /sdcard/
adb push curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android/data/local/ssl/certs/ca-bundle.crt /sdcard/
adb push curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android/data/local/bin/curl /sdcard/
adb push curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android/data/local/bin/openssl /sdcard/


#Trasferimos el archivo ejecutable al movil a un directorio del móvil, por ejemplo /data/app, para ello hacemos un push al movil conectado y posteriormente copiamos el archivo en la carpeta->
adb push libApi_Android_challenge.so /sdcard/ 
adb push api /sdcard/ 
adb shell
#Entramos como root
su
cp /sdcard/api /data/app/
#cambiar permisos ejecutable -> 
chmod 777 /data/app/api

#Crear carpetas para ejecutar el comando curl, necesario para el challenge
cd /data/local/
mkdir ssl
cd ssl
mkdir certs

#Dar permisos de escitura a la carpeta /system/lib o realizar links a las librerías
#Trasferimos la biblioteca creada -> adb push libApi_Android_challenge.so /system/lib
#Trasferimos los ejecutables de curl y ssl -> adb push curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android/data/local/ssl/openssl.cnf /data/local/ssl/
#                                             adb push curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android/data/local/ssl/certs/ca-bundle.crt /data/local/ssl/certs/
#                                             adb push curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android/data/local/bin/curl /system/bin/
#                                             adb push curl-7.40.0-rtmp-ssh2-ssl-zlib-static-bin-android/data/local/bin/openssl /system/bin/
#Otra opción y la que he seguido-> 
#Utilizar la aplicación ES File Explorer, en esta aplicación 
#damos permisos de escritura a la carpeta /system/lib/ y /system/bin/
#copiamos el archivo /sdcard/libApi_Android_challenge.so, a la carperta /system/lib/ 
#copiamos los archivos /sdcard/curl y /sdcard/openssl a la carperta /system/bin/
#copiamos los archivos /sdcard/openssl.cnf a la carpeta /data/local/ssl/
#copiamos los archivos /sdcard/ca-bundle.crt a la carpeta /data/local/ssl/certs/

#cambiar permisos ejecutable -> 
chmod 755 /system/bin/curl
chmod 755 /system/bin/openssl

#Abrir el proyecto remoto de la carpeta Aplicaciones_Android en android studio y darle a ejecutar para instalar la aplicación , que se utilizará para hacer las fotos.
#Cerrar la aplicación
#Por último ejecutar -> 
./data/app/api

#Fuentes

#https://developer.android.com/ndk/guides/standalone_toolchain.html?hl=es-419#abi //compilar con NDK para c en Android
#https://courses.cs.washington.edu/courses/cse326/00wi/unix/g++.html //como usar g++
#https://github.com/chili-epfl/chilitags/blob/master/README-ANDROID.md //librería opencv 





