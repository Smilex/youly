# Add more folders to ship with the application, here
folder_01.source = qml/youly
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
#CONFIG += mobility
#MOBILITY += multimedia multimediawidgets

QT += multimedia

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    account.cpp \
    youly.cpp \
    camerareader.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    account.h \
    youly.h \
    camerareader.h

CONFIG += c++11

RESOURCES += \
    Resources.qrc

OTHER_FILES +=

LIBS += -lzxing
INCLUDEPATH += $$PWD/../zxing/cpp/core/src

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/zbar/lib/ -llibzbar
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/zbar/lib/ -llibzbar
#else:unix: LIBS += -L$$PWD/zbar/lib/ -llibzbar

#INCLUDEPATH += $$PWD/zbar/include
#DEPENDPATH += $$PWD/zbar/include
