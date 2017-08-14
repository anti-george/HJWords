#-------------------------------------------------
#
# Project created by Weijia WANG
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HJWords
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
           QUAZIP_STATIC

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        downloadmanager.cpp \
        deobfuscator.cpp \
    preprocessor.cpp

HEADERS += \
        mainwindow.h \
        downloadmanager.h \
        deobfuscator.h \
    preprocessor.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY = 

INCLUDEPATH += zlib
LIBS += -Lzlib -lz
include(quazip-reborn/quazip.pri)

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/android/lib/armeabi-v7a/libcrypto.so \
        $$PWD/android/lib/armeabi-v7a/libssl.so
}
