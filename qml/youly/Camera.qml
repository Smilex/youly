import QtQuick 2.0
import QtQuick.Controls 1.0
import QtMultimedia 5.0
import Youly 1.0
import "Notifications.js" as Notifications

Item {
    property var notification : null

    MouseArea {
        anchors.fill: parent
        onPressed: {
            //camera.searchAndLock();
        }
    }

    /*Camera {
        id: camera
        //captureMode: Camera.CaptureVideo
    }*/

    /*VideoOutput {
        source: camera
        anchors.fill: parent
        focus: visible
        fillMode: VideoOutput.Stretch
    }*/

    BarcodeCamera {
        id: cameraSurface
        width: parent.width
        height: parent.height

        MouseArea {
            anchors.fill: parent
            onClicked: {
                cameraSurface.start();
            }
        }
    }

    Connections {
        target: Youly
        onBarcodeValid: {
            if (notification !== null) notification.color = qsTr("green");
        }
        onBarcodeInvalid: {
            if (notification !== null) notification.color = qsTr("red");
        }
    }

    Connections {
        target: pageView
        onFlickStarted: {
            if (pageView.currentIndex === 1) {
                //camera.stop();
            }
        }
        onFlickEnded: {
            if (pageView.currentIndex === 1) {
                //camera.start();
            }
        }
    }
}
