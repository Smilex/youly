import QtQuick 2.0

Item {
    Component {
        id: historyComponent
        Rectangle {
            width: historyView.width
            height: 40
            color: "green"

            Text {
                text: "Barcode: " + barcode
                font.pixelSize: 16
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
            }
        }
    }

    ListModel {
        id: historyModel
    }

    ListView {
        id: historyView
        model: historyModel
        delegate: historyComponent
        anchors.fill: parent
    }
}
