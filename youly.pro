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
    barcodesurface.cpp \
    barcodecamera.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    account.h \
    youly.h \
    barcodesurface.h \
    barcodecamera.h

CONFIG += c++11

RESOURCES += \
    Resources.qrc

OTHER_FILES +=

INCLUDEPATH += zbar/include
unix:LIBS += -L$$PWD/zbar/lib -lzbar
