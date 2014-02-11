import QtQuick 2.0
import QtQuick.Controls 1.0
import Youly 1.0

Item {
    id: login
    width: 150
    height: 62
    Column {
        Row {
            height: 50
            LoginService {
                id: login_facebook
                logoColor: qsTr("blue")
                textColor: qsTr("white")
                logoText: qsTr("F")
                rectColor: qsTr("#BBBBBB")
                bgColor: qsTr("white")
                color: rectColor
            }
            LoginService {
                id: login_twitter
                logoColor: qsTr("#A0A0FF")
                textColor: qsTr("white")
                logoText: qsTr("T")
                rectColor: qsTr("#BBBBBB")
                bgColor: qsTr("white")
            }
            LoginService {
                id: login_google
                logoColor: qsTr("orange")
                textColor: qsTr("black")
                logoText: qsTr("G+")
                rectColor: qsTr("#BBBBBB")
                bgColor: qsTr("white")
            }
        }
        Rectangle {
            width: 150
            height: 60
            color: "#BBBBBB"
            Column {
                width: parent.width - 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                TextField {
                    id: login_username
                    width: parent.width
                    text: Account.username
                }
                TextField {
                    id: login_password
                    width: parent.width
                    text: Account.password
                    echoMode: TextInput.Password
                }
            }
        }

        Button {
            width: 150
            text: qsTr("Login")
            onClicked: {
                Account.login(login_username.text, login_password.text);
            }
        }
    }

}
