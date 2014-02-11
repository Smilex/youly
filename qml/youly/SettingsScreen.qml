import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
    VisualItemModel {
        id: settingsModel

        Rectangle {
            width: settingsView.width
            height: 40
            color: "lightgray"

            Label {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: "Set the setting on or off"

                font.pixelSize: 16
            }

            RadioButton {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 10
            }
        }
    }

    ListView {
        id: settingsView
        model: settingsModel
        anchors.fill: parent
    }
}
