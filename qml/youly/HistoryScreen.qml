import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: historyScreen
    state: "Hidden"

    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    Button {
        width: parent.width
        height: 30
        text: "Back"
        onClicked: {
            historyScreen.state = "Hidden"
        }
    }

    Component {
        id: historyComponent
        Rectangle {
            width: historyView.width
            height: 40
            color: statusColor

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
        anchors.topMargin: 30
        flickableDirection: Flickable.VerticalFlick
    }

    Behavior on x { PropertyAnimation {easing.type: Easing.InOutQuad} }

    states: [
        State {
            name: "Shown"
            PropertyChanges {
                target: historyScreen
                x: 0
            }
        },
        State {
            name: "Hidden"
            PropertyChanges {
                target: historyScreen
                x: -main.width
            }
        }

    ]
}
