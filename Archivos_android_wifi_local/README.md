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
cd /cibernoid/Archivos_android_wifi_local

#Crear la librería y ejecutable, ejecutar operador.sh o estas líneas
#(Path de insalación de toolchain)/bin:$PATH
export PATH=/home/user/Documentos/android_compilar/my-android-toolchain/bin:$PATH
#herramienta de compilación, ver las opciones en el directorio anterior, el nombre depende de la arquitectura y la herramienta de compilación (gcc, g++, clang, clang++ ...)
#En este caso arm
export CXX=arm-linux-androideabi-g++

$CXX -fPIC -c -o pruebas_SO.o wifiAnChallenge.cpp -std=c++11										
$CXX -Wall -shared -fPIC -o libWifi_Android_challenge.so pruebas_SO.o wifiAnChallenge.h -std=c++11
$CXX -pie -o "w" main.cpp  -L. -lWifi_Android_challenge -std=c++11


#Para ejecutar en android

#Movil rooteado y conectado por usb al ordenador
#Install adb en el ordenador Ubuntu 16
sudo apt update
sudo apt install android-tools-adb
#Trasferimos el archivo ejecutable al movil a un directorio del móvil, por ejemplo /data/app, para ello hacemos un push al movil conectado y posteriormente copiamos el archivo en la carpeta->
adb push libWifi_Android_challenge.so /sdcard/ 
adb push w /sdcard/ 
adb shell
su
cp /sdcard/w /data/app/
#cambiar permisos Modcifrado_ejecutable -> 
chmod 777 /data/app/w
#Dar permisos de escitura a la carpeta /system/lib o realizar links a la librería
#Trasferimos la biblioteca creada -> adb push libWifi_Android_challenge.so /system/lib/ 
#Otra opción y la que he seguido-> Utilizar la aplicación ES File Explorer, en esta aplicación damos permisos de escritura a la carpeta/system/lib/ y copiar el archivo /sdcard/libWifi_Android_challenge.so a la carperta /system/lib/ 
#Por último ejecutar -> 
./data/app/w

#Fuentes
#https://developer.android.com/ndk/guides/standalone_toolchain.html?hl=es-419#abi //compilar con NDK para c en Android






