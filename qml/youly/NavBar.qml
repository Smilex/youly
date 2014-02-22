import QtQuick 2.0
import "Screens.js" as Screens

Item {
    id: navBar
    state: "Down"
    Image {
        id: navImage
        width: 60
        height: 40
        source: "qrc:///resources/navbar_bg.png"

        MouseArea {
            anchors.fill: parent
            drag.target: navBar
            drag.axis: Drag.YAxis
            drag.minimumY: main.height - navBar.height
            drag.maximumY: main.height - navImage.height
            onReleased: {
                // TODO: Add a check for direction, with a threshold
                if (navBar.state == "Down") {
                    navBar.state = "Up";
                } else {
                    navBar.state = "Down";
                }
            }
        }
    }

    Rectangle {
        id: navBg
        width: parent.width
        height: navBar.height - navImage.height
        y: navImage.height
        color: "white"

        ListView {
            id: navButtonView
            model: navButtonModel
            delegate: navButtonDelegate
            anchors.fill: parent
            orientation: ListView.Horizontal
        }
    }

    ListModel {
        id: navButtonModel
        ListElement {
            imgSource: "qrc:///history_deselected"
            screen: "History"
        }
        ListElement {
            imgSource: "qrc:///scan_deselected"
            screen: "Scan"
        }
        ListElement {
            imgSource: "qrc:///settings_deselected"
            screen: "Settings"
        }

    }

    Component {
        id: navButtonDelegate
        Image {
            source: imgSource
            height: navButtonView.height
            width: navButtonView.width / 3
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Screens.showScreen(screen);
                }
            }
        }
    }

    Behavior on y { PropertyAnimation{easing.type: Easing.InOutQuad} }

    states: [
        State {
            name: "Down"
            PropertyChanges {
                target: navBar
                y: main.height - navImage.height
            }
        },
        State {
            name: "Up"
            PropertyChanges {
                target: navBar
                y: main.height - navBar.height
            }
        }
    ]
}
