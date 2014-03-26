import QtQuick 2.0

Item {
    id: navView
    state: "mid"

    function moveLeft() {
    }

    function moveRight() {
    }

    function fix() {
    }

    width: left.width + mid.width + right.width
    height: main.height
    x: -left.width

    Rectangle {
        id: left
        x: 0
        y: 0
        width: 240
        height: 568
        color: "#c7c2c2"
    }

    Rectangle {
        id: mid
        x: left.width
        y: 485
        width: 320
        height: 83
        color: "#c7c2c2"
        opacity: 1.0
    }

    Rectangle {
        id: right
        x: mid.x + mid.width
        y: 0
        width: 240
        height: 568
        color: "#c7c2c2"
    }

    MouseArea {
        anchors.fill: parent
        drag.target: parent
        drag.axis: Drag.XAxis
        drag.maximumX: 0
        drag.minimumX: (mid.width - right.width) - right.x

        onReleased: {
            navView.state = ""
            if (navView.x > -mid.width / 3)
            {
                navView.state = "left";
            }
            else if (navView.x < -right.x + mid.width * 2 / 3)
            {
                navView.state = "right";
            }
            else {
                navView.state = "mid";
            }
        }
    }

    states: [
        State {
            PropertyChanges {
                target: navView
                explicit: true
                x: navView.x
            }
        },

        State {
            name: "left"
            PropertyChanges {
                target: navView
                x: -left.x
            }
            PropertyChanges {
                target: mid
                opacity: 0.2
            }
        },
        State {
            name: "mid"
            PropertyChanges {
                target: navView
                x: -mid.x
            }
            PropertyChanges {
                target: mid
                opacity: 1.0
            }
        },
        State {
            name: "right"
            PropertyChanges {
                target: navView
                x: -right.x + (mid.width - right.width)
            }
            PropertyChanges {
                target: mid
                opacity: 0.2
            }
        }
    ]

    transitions: [
        Transition {
            PropertyAnimation {
                target: navView
                properties: "x"
                easing.type: Easing.InOutQuad
            }
            PropertyAnimation {
                target: mid
                properties: "opacity"
                easing.type: Easing.InOutQuad
            }
        }
    ]
}
