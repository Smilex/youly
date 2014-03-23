import QtQuick 2.0
import QtQuick.Window 2.0
import "components"

Rectangle {
    id: rectangle1
    width: 320 //Screen.width
    height: 568 //Screen.height

    NavBar {
        id: navBar
        y: 506
        height: 62
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }
}
