import QtQuick 2.0

Rectangle {
    id: pullIn

    readonly property int none: 0
    readonly property int positive: 1
    readonly property int negative: 2

    property int pullX: none
    property int pullY: none

    function pull() {
        state = "pulled"
    }

    function pop() {
        state = "";
    }

    Behavior on x {
        PropertyAnimation {
            easing.type: Easing.InOutQuad
        }
    }
    Behavior on y {
        PropertyAnimation {
            easing.type: Easing.InOutQuad
        }
    }

    states: [
        State {
            name: "pulled"
            PropertyChanges {
                target: pullIn
                explicit: true
                x: {
                    if (pullX == none)
                        return x;
                    else if (pullX == positive)
                        return x + width;
                    else if (pullX == negative)
                        return x - width;
                }
                y: {
                    if (pullY == none)
                        return y;
                    else if (pullY == positive)
                        return y + height;
                    else if (pullY == negative)
                        return y - height;
                }
            }
        }
    ]
}
