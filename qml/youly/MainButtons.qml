import QtQuick 2.0

Item {
    Row {
        Image {
            id: history
            source: "qrc:///images/history_deselected"
            width: 64
            height: 64
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    history.source = "qrc:///images/history_selected"
                    scan.source = "qrc:///images/scan_deselected"
                    settings.source = "qrc:///images/settings_deselected"
                }
            }
        }

        Image {
            id: scan
            source: "qrc:///images/scan_selected"
            width: 64
            height: 64
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    history.source = "qrc:///images/history_deselected"
                    scan.source = "qrc:///images/scan_selected"
                    settings.source = "qrc:///images/settings_deselected"
                }
            }

        }

        Image {
            id: settings
            source: "qrc:///images/settings_deselected"
            width: 64
            height: 64
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    history.source = "qrc:///images/history_deselected"
                    scan.source = "qrc:///images/scan_deselected"
                    settings.source = "qrc:///images/settings_selected"
                }
            }

        }
    }
}
