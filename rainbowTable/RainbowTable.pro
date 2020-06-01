QT -= gui

TEMPLATE = app
CONFIG += sdk_no_version_check
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
#VPATH = SRC INCLUDE
CONFIG += c++17
QMAKE:    QT += core

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        #check-passwd.cpp \
        #gen-passwd.cpp \
        sha256-main.cpp \
        sha256.cpp \
        #tableGeneration.cpp \
        #uncypher.cpp


HEADERS += \
        passwd-utils.hpp \
        random.hpp \
        sha256.h \
        #tableGeneration.h \
        #uncypher.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
