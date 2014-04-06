import QtQuick 2.0

Item {
    id: navView
    state: "mid"

    property var blur
    property real maxOpacity: 0.7
    property real minOpacity: 0.2

    width: leftView.width + midView.width + rightView.width
    height: main.height
    x: -leftView.width

    onXChanged: {
        if (navView.x > -leftView.width)
        {
            blur.radius = (1.0 + navView.x / leftView.width) * 100;
            midView.opacity = (-navView.x / leftView.width) * maxOpacity;
            if (midView.opacity <= minOpacity)
                midView.opacity = minOpacity;
        }
        else if (navView.x < leftView.width)
        {
            blur.radius = (1.0 + navView.x / leftView.width) * -100;
            midView.opacity = (maxOpacity + (navView.x + leftView.width) / leftView.width);
            if (midView.opacity <= minOpacity)
                midView.opacity = minOpacity;
        }
        else {
            blur.radius = 0
            midView.opacity = maxOpacity;
        }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: parent
        drag.axis: Drag.XAxis
        drag.maximumX: 0
        drag.minimumX: (midView.width - rightView.width) - rightView.x

        onReleased: {
            navView.state = ""
            if (navView.x > -midView.width / 3)
            {
                navView.state = "left";
            }
            else if (navView.x < -rightView.x + midView.width * 2 / 3)
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
                x: -leftView.x
            }
        },
        State {
            name: "mid"
            PropertyChanges {
                target: navView
                x: -midView.x
            }
        },
        State {
            name: "right"
            PropertyChanges {
                target: navView
                x: -rightView.x + (midView.width - rightView.width)
            }
        }
    ]

    transitions: [
        Transition {
            PropertyAnimation {
                target: navView
                properties: "x"
                duration: 100
                easing.type: Easing.Linear
            }
            PropertyAnimation {
                target: midView
                properties: "opacity"
                easing.type: Easing.InOutQuad
            }
        }
    ]
}
