import QtQuick 2.0

Rectangle {
    property string logoColor
    property string textColor
    property string logoText
    property string bgColor
    property string rectColor

    height: parent.height
    width: 50
    Rectangle {
        height: parent.height - 6
        width: parent.width - 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: parent.logoColor
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: textColor
            text: logoText
        }
    }
    MouseArea {
        anchors.fill: parent
        onPressed: {
            login_facebook.color = bgColor
            login_twitter.color = bgColor
            login_google.color = bgColor
            parent.color = rectColor
        }
    }
}
