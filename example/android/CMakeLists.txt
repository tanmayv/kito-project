MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

set(APPNAME "cnfgtest")
set(LABEL ${APPNAME})
set(APKFILE ${APPNAME}.apk)
set(PACKAGENAME com.tanmayvijay.${APPNAME})
set(RAWDRAWANDROID ${CMAKE_CURRENT_SOURCE_DIR})
set(RAWDRAWANDROIDSRCS ${RAWDRAWANDROID}/android_native_app_glue.c)
set(SRC test.c)

set(ANDROIDVERSION 29)
set(ANDROIDTARGET ${ANDROIDVERSION})


set(CMAKE_C_FLAGS "-ffunction-sections -Os -fdata-sections -Wall -fvisibility=hidden -m64 -DBUILD_SHARED_LIBS=OFF")
set(CMAKE_CXX_FLAGS "-ffunction-sections -Os -fdata-sections -Wall -fvisibility=hidden -m64 -DBUILD_SHARED_LIBS=OFF")
set(ANDROID_FULLSCREEN y)
set(ADB adb)
set(UNAME Darwin)

set(ANDROIDSRCS ${SRC} ${RAWDRAWANDROIDSRCS})

if(${UNAME} STREQUAL "Darwin")
  set(OS_NAME darwin-x86_64)
endif()

if(${UNAME} STREQUAL "Linux")
  set(OS_NAME linux-x86_64)
endif()

if(${UNAME} STREQUAL "Windows_NT")
  set(OS_NAME windows-x86_64)
endif()

set(ANDROIDSDK $ENV{ANDROID_HOME})
SUBDIRLIST(SUBDIRS ${ANDROIDSDK}/ndk)
list(LENGTH SUBDIRS list_len)
math(EXPR list_last "${list_len} - 1")
list(GET SUBDIRS ${list_last} NDK)
set(NDK "${ANDROIDSDK}/ndk/${NDK}")
message("Hello " ${SUBDIRS})
# set(NDK ${ANDROIDSDK}/ndk/24.0.8215888)
SUBDIRLIST(SUBDIRS ${ANDROIDSDK}/build-tools)
math(EXPR list_last "${list_len} - 1")
list(GET SUBDIRS ${list_last} BUILD_TOOLS)
set(BUILD_TOOLS "${ANDROIDSDK}/build-tools/${BUILD_TOOLS}")
# set(BUILD_TOOLS ${ANDROIDSDK}/build-tools/33.0.1)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -DANDROID -DAPPNAME=\\\"${APPNAME}\\\"")
set(CMAKE_CC_FLAGS "${CMAKE_CC_FLAGS} -Os -DANDROID -DAPPNAME=\\\"${APPNAME}\\\"")
message("ANDROIDSDK: ${ANDROIDSDK}")
message("NDK: ${NDK}")
message("BUILD_TOOLS: ${BUILD_TOOLS}")
message("CMAKE_CC_FLAGS: ${CMAKE_CC_FLAGS}")

project(rawandroid)
set(CC_ARM64 ${NDK}/toolchains/llvm/prebuilt/${OS_NAME}/bin/aarch64-linux-android${ANDROIDVERSION}-clang)
set(CC_ARM32 ${NDK}/toolchains/llvm/prebuilt/${OS_NAME}/bin/armv7a-linux-androideabi${ANDROIDVERSION}-clang)
set(CC_x86 ${NDK}/toolchains/llvm/prebuilt/${OS_NAME}/bin/i686-linux-android${ANDROIDVERSION}-clang)
set(CC_x86_64 ${NDK}/toolchains/llvm/prebuilt/${OS_NAME}/bin/x86_64-linux-android${ANDROIDVERSION}-clang)
set(AAPT ${BUILD_TOOLS}/aapt)

set(CMAKE_CXX_COMPILER ${CC_ARM64})
set(CMAKE_C_COMPILER ${CC_ARM64})
message("C compile ${CC_ARM64}")

add_library(${APPNAME} MODULE ${ANDROIDSRCS})
# CFLAGS+= ${RAWDRAWANDROID}/rawdraw ${NDK}/sysroot/usr/include ${NDK}/sysroot/usr/include/android ${NDK}/toolchains/llvm/prebuilt/${OS_NAME}/sysroot/usr/include/android -fPIC ${RAWDRAWANDROID} -DANDROIDVERSION=${ANDROIDVERSION}
target_include_directories(${APPNAME} PRIVATE rawdraw ${NDK}/sysroot/usr/include ${NDK}/sysroot/usr/include/android ${NDK}/toolchains/llvm/prebuilt/${OS_NAME}/sysroot/usr/include/android ${CMAKE_CURRENT_SOURCE_DIR})
set(LIB_PATH ${NDK}/toolchains/llvm/prebuilt/${OS_NAME}/sysroot/usr/lib/x86_64-linux-android/${ANDROIDVERSION})
target_link_libraries(${APPNAME} ${LIB_PATH} m GLESv3 EGL android log -shared -uANativeActivity_onCreate)


set(LIB_PATH ${NDK}/toolchains/llvm/prebuilt/${OS_NAME}/sysroot/usr/lib/x86_64-linux-android/${ANDROIDVERSION})
target_link_libraries(${APPNAME} ${LIB_PATH} m GLESv3 EGL android log "-landroid")
set(KEYSTOREFILE my-release-key.keystore)
set(ALIASNAME standkey)
set(DNAME "CN=example.com, OU=ID, O=Example, L=Doe, S=John, C=GB")
set(STOREPASS password)

add_custom_target(keystore ALL 
  COMMAND keytool -genkey -v -keystore ${KEYSTOREFILE} -alias ${ALIASNAME} -keyalg RSA -keysize 2048 -validity 10000 -storepass password -keypass password -dname ${DNAME} || exit 0
  COMMENT "GENERATING keystorefile"
  VERBATIM)

# TODO: Fix the dependency, custom target should only run when testlib is changed
add_custom_target(manifest ALL
  COMMAND PACKAGENAME=${PACKAGENAME} ANDROIDVERSION=${ANDROIDVERSION} ANDROIDTARGET=${ANDROIDTARGET} APPNAME=${APPNAME} LABEL=${LABEL} envsubst '$$ANDROIDTARGET $$ANDROIDVERSION $$APPNAME $$PACKAGENAME $$LABEL' < ${CMAKE_CURRENT_SOURCE_DIR}/AndroidManifest.xml.template > AndroidManifest.xml)

add_custom_target(intermediate_apk ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory apk/assets
  COMMAND ${CMAKE_COMMAND} -E make_directory apk/lib/arm64-v8a
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/src/assets ${CMAKE_BINARY_DIR}/apk/assets
  # COMMAND ${CMAKE_COMMAND} -E copy lib${APPNAME}.dylib apk/lib/arm64-v8a/lib${APPNAME}.dylib
  COMMAND ${CMAKE_COMMAND} -E copy lib${APPNAME}.so apk/lib/arm64-v8a/lib${APPNAME}.so
  COMMAND ${AAPT} package -f -F temp.apk -I ${ANDROIDSDK}/platforms/android-${ANDROIDVERSION}/android.jar -M AndroidManifest.xml -S ${CMAKE_CURRENT_SOURCE_DIR}/src/res -A apk/assets -v --target-sdk-version ${ANDROIDTARGET}
  COMMAND unzip -o temp.apk -d apk
  COMMENT "Generating intermediate apk")

message("CMake binary dir ${CMAKE_CURRENT_BINARY_DIR}")
add_custom_target(zip_apk ALL
  DEPENDS intermediate_apk
  COMMAND ${CMAKE_COMMAND} -E remove makecapk.apk
  COMMAND zip -D9r ../makecapk.apk . && zip -D0r ../makecapk.apk resources.arsc AndroidManifest.xml
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/apk
  COMMENT "Zipping the apk")

add_custom_target(sign_apk ALL
  DEPENDS zip_apk
  COMMAND jarsigner -sigalg SHA1withRSA -digestalg SHA1 -verbose -keystore ${KEYSTOREFILE} -storepass password makecapk.apk ${ALIASNAME}
  COMMAND ${CMAKE_COMMAND} -E remove ${APKFILE}
  COMMAND echo "ZIP ALIGN"
  COMMAND ${BUILD_TOOLS}/zipalign -v 4 makecapk.apk ${APKFILE}
  COMMAND echo "APK SIGNER"
  COMMAND ${BUILD_TOOLS}/apksigner sign --key-pass pass:${STOREPASS} --ks-pass pass:${STOREPASS} --ks ${KEYSTOREFILE} ${APKFILE}
  COMMAND ${CMAKE_COMMAND} -E remove temp.apk
  COMMAND ${CMAKE_COMMAND} -E remove makecapk.apk
  COMMENT "Signing apk")
