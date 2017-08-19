INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
HEADERS += $$PWD/crypt.h \
           $$PWD/ioapi.h \
           $$PWD/quazipfile.h \
           $$PWD/quazipfileinfo.h \
           $$PWD/quazipnewinfo.h \
           $$PWD/quazip_global.h \
           $$PWD/quazip.h \
           $$PWD/unzip.h \
           $$PWD/zip.h

SOURCES += $$PWD/qioapi.cpp \
           $$PWD/quazip.cpp \
           $$PWD/quazipfile.cpp \
           $$PWD/quazipfileinfo.cpp \
           $$PWD/quazipnewinfo.cpp \
           $$PWD/unzip.cpp \
           $$PWD/zip.cpp
