#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QQmlEngine>
#include <QQmlComponent>

#include "youly.h"
#include "account.h"
#include "barcodecamera.h"
#include "barcodesurface.h"
#include <iostream>

int main(int argc, char *argv[])
{    
    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Youly");
    QCoreApplication::setOrganizationDomain("youly.app");
    QCoreApplication::setApplicationName("Youly");

    QtQuick2ApplicationViewer viewer;

    qmlRegisterSingletonType<Youly>("Youly", 1,0, "Youly", YoulySingletonProvider);
    qmlRegisterSingletonType<Account>("Youly", 1,0, "Account", AccountSingletonProvider);
    //qmlRegisterSingletonType<CameraReader>("Youly", 1,0, "CameraReader", CameraReaderSingletonProvider);
    qmlRegisterType<BarcodeCamera>("Youly.Components", 1,0, "BarcodeCamera");

    viewer.setSource(QUrl("qrc:///Main.qml"));
    viewer.showExpanded();

    return app.exec();
}
