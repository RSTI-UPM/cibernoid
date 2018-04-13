#Pasos a seguir para crear librería .so de Android

#Descargar NDK Android 
#NDK->https://developer.android.com/ndk/downloads/index.html?hl=es-419 
#Descargar lcrypto para android que depende de la arquitectura #https://github.com/emileb/OpenSSL-for-Android-Prebuilt //Openssl armabi y x86
															   #https://github.com/felipejfc/openssl_prebuilt_for_android //arm y armabi-v7a
#Más opciones para tener la librería lcrypto #https://wiki.openssl.org/index.php/Android , https://es.androids.help/q8664
#Instalar compilador de Android (#https://developer.android.com/ndk/guides/standalone_toolchain.html?hl=es-419#abi)
#(Path_de_ndk)/build/tools/make-standalone-toolchain.sh --arch=(arquitectura (x86, x86_64, arm, mips, mips_64)) --platform=(API_android, api23(6.0)) ----install-dir=(Path_del_directorio_donde_se_quiere_guardar_las_herramientas_de_compilación) 
/home/mercurio/Descargas/android-ndk-r15b/build/tools/make-standalone-toolchain.sh --arch=x86 --platform=android-23 --install-dir=/home/mercurio/Documentos/android_compilar/my-android-toolchain 

#(Path de insalación de toolchain)/bin
export PATH=/home/mercurio/Documentos/android_compilar/my-android-toolchain/bin:$PATH
#herramienta de compilación, ver las opciones en el directorio anterior, el nombre depende de la arquitectura y la herramienta de compilación (gcc, g++, clang, clang++ ...)
#En este caso clang++ 
export CLANGXX=arm-linux-androideabi-clang++



#Descargar de drive los archivos de la carpeta archivos_android sha256.h sha256.cpp ModCifradoSO.h ModCifrado.cpp y la librería Openssl para android
cd /(Path de la carpeta con los archivos)

$CLANGXX -fPIC -c -o ModCifradoSO.o ModCifradoSO.cpp -lc -I/(path de la libreria openssl de android)/openssl-1.0.2/include -L/(path de la libreria openssl de android)/x86/lib/ -lcrypto
$CLANGXX -fPIC -c -o sha256.o sha256.cpp
$CXX -shared -fPIC -o libModCifrado_Android.so ModCifradoSO.o sha256.o -lc -I/(path de la libreria openssl de android)/openssl-1.0.2/include -L/(path de la libreria openssl de android)/x86/lib/ -lcrypto
$CLANGXX -pie -o "ModCifrado_ejecutable" ModCifrado.cpp -L. -lModCifrado_Android -I/(path de la libreria openssl de android)/openssl-1.0.2/include -L/(path de la libreria openssl de android)/openssl-1.0.2/x86/lib/ -lcrypto -std=c++11

//Ejemplo:

export PATH=/home/pablo/Documentos/android_compilar/my-android-toolchain-lib-15c/bin:$PATH
export CXX=arm-linux-androideabi-clang++
$CXX -fPIC -c -o sha256.o sha256.cpp 
$CXX -fPIC -c -o ModCifradoSO.o ModCifradoSO.cpp -lc -I/home/pablo/Escritorio/Archivo_android_ModCifrado/OpenSSL-for-Android-Prebuilt-master/openssl-1.0.2/include -L/home/pablo/Escritorio/Archivo_android_ModCifrado/OpenSSL-for-Android-Prebuilt-master/openssl-1.0.2/armeabi-v7a/lib -lcrypto
$CXX -shared -o libModCifrado_Android.so ModCifradoSO.o sha256.o -lc -I/home/pablo/Escritorio/Archivo_android_ModCifrado/OpenSSL-for-Android-Prebuilt-master/openssl-1.0.2/include -L/home/pablo/Escritorio/Archivo_android_ModCifrado/OpenSSL-for-Android-Prebuilt-master/openssl-1.0.2/armeabi-v7a/lib -lcrypto
$CXX -pie -o "ModCifrado_ejecutable" ModCifrado.cpp -L. -lModCifrado_Android -I/home/pablo/Escritorio/Archivo_android_ModCifrado/OpenSSL-for-Android-Prebuilt-master/openssl-1.0.2/include -L/home/pablo/Escritorio/Archivo_android_ModCifrado/OpenSSL-for-Android-Prebuilt-master/openssl-1.0.2/armeabi-v7a/lib -lcrypto 



#Para ejecutar en android

#Descargar por ejemplo Termux en el movil rooteado 
#Trasferimos el archivo ejecutable al movil a un directorio del móvil, por ejemplo /data/app-> adb push Modcifrado_ejecutable /data/app 
#Trasferimos la biblioteca creada -> adb push libModCifrado_Android.so /data/data/com.termux/files/usr/lib
#Decimos que coja las librerías de la carpeta anterior-> export LD_LIBRARY_PATH=/data/data/com.termux/files/usr/lib
#cambiar permisos Modcifrado_ejecutable -> chmod 777 Modcifrado_ejecutable
#ejecutar -> libModCifrado_Android.so
#Dara fallo porque falta la librería -lcrypto -> y cambiamos el nombre de la librería por el nombre que dice, en mi caso, libcrypto.so_1_0_0 y de nuevo la trasferimos igual que la creada adb push libcrypto.so_1_0_0 /data/data/com.termux/files/usr/lib
#ejecutamos -> libModCifrado_Android.so


#Fuentes
#https://github.com/emileb/OpenSSL-for-Android-Prebuilt //Openssl arm y x86
#https://developer.android.com/ndk/guides/standalone_toolchain.html?hl=es-419#abi //compilar con NDK para c en Android
#https://courses.cs.washington.edu/courses/cse326/00wi/unix/g++.html //como usar g++










