function barcode() {
    var qmlCode = "import QtQuick 2.0; Notification {}";
    //var component = Qt.createComponent("Notification.qml");
    //return component.createObject(main);
    return Qt.createQmlObject(qmlCode, main, "BarcodeNotification");
}

function login ( failed ) {
    var qmlCode = "import QtQuick 2.0; Notification {";
    if ( failed ) {
        qmlCode += "color: \"yellow\";Text {text: \"Not logged in\"};";
    } else {
        qmlCode += "color: \"green\";Text {text: \"Logged in successfully\"}";
    }

    qmlCode += "}";

    return Qt.createQmlObject(qmlCode, main, "LoginNotification");
}
