#!/usr/bin/env sh
NDK_ROOT="${1:-${NDK_ROOT}}"

if [ ! -d "${WD}/android-cmake" ]; then
    echo 'Cloning android-cmake'
   git clone https://github.com/taka-no-me/android-cmake.git
fi

### ABI setup
ANDROID_ABI=${ANDROID_ABI:-"armeabi-v7a"}
#ANDROID_ABI=${ANDROID_ABI:-"arm64-v8a with NEON"}
#ANDROID_ABI=${ANDROID_ABI:-"x86"}
#ANDROID_ABI=${ANDROID_ABI:-"x86_64"}

### path setup
SCRIPT=$(readlink -f $0)
WD=`dirname $SCRIPT`
OPENCV_ROOT=${WD}/opencv

BUILD_DIR=$OPENCV_ROOT/platforms/build_android
INSTALL_DIR=${WD}/android_opencv
N_JOBS=${N_JOBS:-4}

if [ "${ANDROID_ABI}" = "armeabi" ]; then
    API_LEVEL=16
else
    API_LEVEL=21
fi

rm -rf "${BUILD_DIR}"
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"


cmake -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON \
      -DCMAKE_TOOLCHAIN_FILE="${WD}/android-cmake/android.toolchain.cmake" \
      -DANDROID_NDK="${NDK_ROOT}" \
      -DANDROID_NATIVE_API_LEVEL=${API_LEVEL} \
      -DANDROID_ABI="${ANDROID_ABI}" \
      -D WITH_CUDA=OFF \
      -D WITH_MATLAB=OFF \
      -D BUILD_ANDROID_EXAMPLES=OFF \
      -D BUILD_DOCS=OFF \
      -D BUILD_PERF_TESTS=OFF \
      -D BUILD_TESTS=OFF \
      #-D BUILD_SHARED_LIBS=ON \  
      -DOPENCV_EXTRA_MODULES_PATH="${WD}/opencv_contrib/modules/"  \
      -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}/opencv" \
      ../..

make -j${N_JOBS}

# rm and install install folder, and remove build folder
rm -rf "${INSTALL_DIR}/opencv"
make install/strip

cd "${WD}"
rm -rf "${BUILD_DIR}"

#http://tzutalin.blogspot.com.es/2016/01/installing-opencv-310-and-contrib-lib.html
