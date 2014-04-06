import QtQuick 2.0
import QtQuick.Window 2.0
import Youly.Components 1.0
import QtGraphicalEffects 1.0
import QtMultimedia 5.0
import "components"

Item {
    id: main
    width: 320 //Screen.width
    height: 568 //Screen.height

    Camera {
        id: camera
    }

    VideoOutput {
        id: cameraOutput
        source: camera
        fillMode: VideoOutput.Stretch
    }

    FastBlur {
        id: fastBlur
        source: cameraOutput
        anchors.fill: cameraOutput
        radius: 0
    }


    NavView {
        blur: fastBlur
        LeftView {
            id: leftView
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: midView.width - midView.height
            x: 0
        }

        NavBar {
            id: midView
            anchors.bottom: parent.bottom
            anchors.left: leftView.right
            width: main.width
            height: 96
        }

        RightView {
            id: rightView
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: midView.right
            width: midView.width - midView.height
        }

    }


}
