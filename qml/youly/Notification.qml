import QtQuick 2.0

Rectangle {
    id: notification
    width: main.width
    height: 30
    state: "UP"
    color: "yellow"

    property int pauseDuration : 2000

    Component.onCompleted: notification.state = "DOWN"

    states: [
        State {
            name: "UP"
            PropertyChanges {
                target: notification
                y: -notification.height
            }
        },
        State {
            name: "DOWN"
            PropertyChanges {
                target: notification
                y: 0
            }
        }

    ]

    transitions:[
        Transition {
            from: "UP"; to: "DOWN";
            SequentialAnimation {
                NumberAnimation {properties: "y"; easing.type: Easing.InOutQuad}
                PauseAnimation { duration: pauseDuration }
                PropertyAction {target: notification; property: "state"; value: "UP"; }
            }
        },

        Transition {
            from: "DOWN"; to: "UP";
            NumberAnimation {properties: "y"; easing.type: Easing.InOutQuad}
        }
    ]
}
