import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
    Camera {
        anchors.fill: parent
    }


    Button {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 20
        anchors.topMargin: 20
        text: "Profile"
        onClicked: profileDrop.start()
        opacity: 0.5
        onHoveredChanged: {
            if (hovered)
                opacity = 1.0
            else
                opacity = 0.5
        }
    }

}
