import QtQuick 2.0
import QtQuick.Window 2.0
import "components"

Item {
    id: main
    width: 320 //Screen.width
    height: 568 //Screen.height

    NavBar {
        height: 64
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

    }
}
