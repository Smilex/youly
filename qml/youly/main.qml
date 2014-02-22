import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
import Youly 1.0
import "Notifications.js" as Notifications

Rectangle {
    id: main
    width: 320
    height: 568

    VisualItemModel {
        id: pageModel

        /*HistoryScreen {
            id: historyScreen
            width: main.width
            height: main.height
        }*/
        CameraScreen {
            id: cameraScreen
            width: main.width
            height: main.height
        }

        SettingsScreen {
            id: settingsScreen
            width: main.width
            height: main.height
        }
    }

    ListView {
        id: pageView
        anchors.fill: parent
        model: pageModel
        orientation: ListView.Horizontal
        highlightRangeMode: ListView.StrictlyEnforceRange
        snapMode: ListView.SnapOneItem
        boundsBehavior: Flickable.DragOverBounds
        currentIndex: 0
    }

    LoginScreen {
        id: loginScreen
        width: main.width
        height: main.height
        y: -main.height
    }

    Component.onCompleted: {
        if (Account.haveCredentials())
            Account.login(Account.username, Account.password);
    }

    Connections {
        target: Account
        onLoginSuccessful: {
            Notifications.login(false);
        }
        onLoginFailed: {
            Notifications.login(true);
        }
    }

    NumberAnimation {
        id: profileDrop
        target: loginScreen
        properties: "y"
        to: 0
    }

    NumberAnimation {
        id: profileUp
        target: loginScreen
        properties: "y"
        to: -main.height
    }
}
