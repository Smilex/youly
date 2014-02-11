import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {
    color: "lightgrey"
    Login {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }


    Button {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        text: "Back"
        onClicked: profileUp.start()
    }
}
