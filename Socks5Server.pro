QT += core
QT -= gui

QT += network

CONFIG += c++11


CONFIG -= console
CONFIG -= app_bundle



TARGET = Socks5Server

TEMPLATE = app

SOURCES += main.cpp \
    param.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#socks5实现
INCLUDEPATH += $$PWD/socks5
#工具
INCLUDEPATH += $$PWD/tool

include($$PWD/socks5/socks5.pri)
include($$PWD/tool/tool.pri)

HEADERS += \
    param.h


#-------------以下参数需根据不同环境自行配置--------------------
#------------------修改后请-重新构建-------------------------
#环境   开发=Qt_DEV  测试=Qt_TEST  生产=Qt_PROD
DEFINES += Qt_DEV

#版本号  V1.0.0.0  手动设置   注：后面的等号不能有空格！！！
DEFINES += LVERSION=\\\"V1.0.0.0\\\"

DISTFILES += \
    README.md
