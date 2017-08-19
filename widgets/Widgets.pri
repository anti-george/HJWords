INCLUDEPATH += $$PWD/zlib
LIBS += -Lzlib -lz
include($$PWD/quazip-reborn/QuaZip.pri)

SOURCES += $$PWD/downloadmanager.cpp \
           $$PWD/deobfuscator.cpp \
           $$PWD/preprocessor.cpp

HEADERS += $$PWD/downloadmanager.h \
           $$PWD/deobfuscator.h \
           $$PWD/preprocessor.h