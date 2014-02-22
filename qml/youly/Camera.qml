import QtQuick 2.0
import QtQuick.Controls 1.0
import QtMultimedia 5.0
import Youly 1.0
import "Notifications.js" as Notifications

Item {
    property var notification : null

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
        target: cameraSurface
        onBarcodeReady: {
            Youly.testBarcode(barcode, Account.seed);
        }
    }

    Connections {
        target: Youly
        onBarcodeValid: {
            notification = Notifications.barcode();
            if (notification !== null) notification.color = qsTr("green");
        }
        onBarcodeInvalid: {
            notification = Notifications.barcode();
            if (notification !== null) notification.color = qsTr("red");
        }
    }

}
