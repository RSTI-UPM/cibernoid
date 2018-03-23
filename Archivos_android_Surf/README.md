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
#Descargar la librería opencv de android https://sourceforge.net/projects/opencvlibrary/files/opencv-android/3.3.1/
#Descargar opencv_contrib https://github.com/opencv/opencv_contrib/releases/tag/3.3.1
#export ANDROID_NDK=(Path_de_ndk) 
export ANDROID_NDK=/home/user/Descargas/android-ndk-r12b
sudo apt install cmake-curses-gui
cd ~/(path descarga opencv)/
mv -r opencv-3.3.1 opencv
mv -r opencv_contrib-3.3.1 opencv_contrib
cp ~/(path descarga git)/cibernoid/Archivos_android_surf/build-android-opencv.sh ~/(path opencv)/
.~/(path opencv)/build-android-opencv.sh # //puede editarse el script por ejemplo indicando el ńumero de la api de android, ej. cmake -DANDROID_ABI=arm -DANDROID_ARCH=arm -DANDROID_API_LEVEL=16 -DCMAKE_TOOLCHAIN_FILE=../android/android.toolchain.cmake $@ ../..
cd (carpeta creada por el anterior script) #android_opencv/opencv/sdk/native/libs/armeabi-v7a (librerías .so) y /android_opencv/opencv/sdk/native/jni/include (include)

#Descargar de drive los archivos de la carpeta
cd /cibernoid/Archivos_android_Surf


#Crear la librería y ejecutable, ejecutar Im.sh o estas líneas
#(Path de insalación de toolchain)/bin:$PATH
export PATH=/home/user/Documentos/android_compilar/my-android-toolchain/bin:$PATH
#herramienta de compilación, ver las opciones en el directorio anterior, el nombre depende de la arquitectura y la herramienta de compilación (gcc, g++, clang, clang++ ...)
#En este caso arm
export CXX=arm-linux-androideabi-g++

$CXX -fPIC -c -o pruebas_SO.o surfAnchallenge.cpp -lc -I/(Path de la carpeta include de los archivos de opencv) -L/Path de la carpeta que contiene las librerías .so)  -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d -lopencv_xfeatures2d -lopencv_ml -lopencv_shape -lopencv_flann -lopencv_video -lopencv_videoio 																																											
$CXX -Wall -shared -fPIC -o libSurf_Android_challenge.so pruebas_SO.o surfAnchallenge.h -lc -I/(Path de la carpeta include de los archivos de opencv) -L/Path de la carpeta que contiene las librerías .so)  -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d -lopencv_xfeatures2d -lopencv_ml -lopencv_shape -lopencv_flann -lopencv_video -lopencv_videoio 
$CXX -pie -o "surf" main.cpp -lc -I/(Path de la carpeta include de los archivos de opencv) -L/Path de la carpeta que contiene las librerías .so)  -lopencv_calib3d -lopencv_imgproc -lopencv_imgcodecs -lopencv_core -lopencv_features2d -lopencv_xfeatures2d -lopencv_ml -lopencv_shape -lopencv_flann -lopencv_video -lopencv_videoio  -L. -lIrchallenge_Android 

#Para ejecutar en android

#Movil rooteado y conectado por usb al ordenador
#Install adb en el ordenador Ubuntu 16
sudo apt update
sudo apt install android-tools-adb
#Trasferimos el archivo ejecutable al movil a un directorio del móvil, por ejemplo /data/app, para ello hacemos un push al movil conectado y posteriormente copiamos el archivo en la carpeta->
adb push libSurf_Android_challenge.so /sdcard/ 
adb push surf /sdcard/ 
adb shell
#Entramos como root
su
cp /sdcard/surf /data/app/
#cambiar permisos Modcifrado_ejecutable -> 
chmod 777 /data/app/surf
#Dar permisos de escitura a la carpeta /system/lib o realizar links a las librerías
#Trasferimos la biblioteca creada -> adb push libSurf_Android_challenge.so /system/lib
#Tranferimos las librerías necesarias de opencv libopencv_calib3d.so, libopencv_core.so, libopencv_features2d.so, libopencv_flann.so, libopencv_highgui.so, libopencv_imgcodecs.so, libopencv_imgproc.so, libopencv_videoio.so...
#Otra opción y la que he seguido-> Utilizar la aplicación ES File Explorer, en esta aplicación damos permisos de escritura a la carpeta/system/lib/ y copiar el archivo /sdcard/libSurf_Android_challenge.so,libopencv_calib3d.so, libopencv_core.so, libopencv_features2d.so, libopencv_flann.so, libopencv_highgui.so, libopencv_imgcodecs.so, libopencv_imgproc.so, libopencv_videoio.so ... a la carperta /system/lib/ 
#Abrir el proyecto camara en android studio que se encuentra en la carpeta cibernoid/Aplicaciones_android y darle a ejecutar para instalar la aplicación camera, que se utilizará para hacer las fotos.
#Cerrar la aplicación
#Por último ejecutar -> 
./data/app/surf


#Fuentes

#https://developer.android.com/ndk/guides/standalone_toolchain.html?hl=es-419#abi //compilar con NDK para c en Android
#https://courses.cs.washington.edu/courses/cse326/00wi/unix/g++.html //como usar g++
#https://github.com/chili-epfl/chilitags/blob/master/README-ANDROID.md //librería opencv 





