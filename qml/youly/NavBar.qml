import QtQuick 2.0
import "components"

Rectangle {
    color: "white"
    opacity: 0.7

    ListView {
        id: navView
        model: navModel
        delegate: navItem
        orientation: ListView.Horizontal

        anchors.fill: parent
    }

    ListModel {
        id: navModel

        ListElement {
            image:"icons/settings"
        }

        ListElement {
            image:"icons/settings"
        }

        ListElement {
            image:"icons/settings"
        }
    }

    Component {
        id: navItem
        Image {
            source: image
            width: 64
            height: 64
        }
    }
}
