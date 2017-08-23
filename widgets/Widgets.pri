INCLUDEPATH += $$PWD/zlib
LIBS += -Lzlib -lz
include($$PWD/quazip-reborn/QuaZip.pri)

SOURCES += $$PWD/downloadmanager.cpp \
           $$PWD/deobfuscator.cpp \
           $$PWD/preprocessor.cpp \
           $$PWD/processor.cpp

HEADERS += $$PWD/downloadmanager.h \
           $$PWD/deobfuscator.h \
           $$PWD/preprocessor.h \
           $$PWD/processor.h
