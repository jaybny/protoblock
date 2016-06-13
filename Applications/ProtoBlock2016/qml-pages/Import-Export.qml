import QtQuick 2.4
import QtQuick.Controls 1.4 as Controls
import ProRotoQml.Protoblock 1.0
import Material 1.0
import Material.ListItems 1.0 as ListItems
import ProRotoQml.Theme 1.0

Item{
    Card {
        width: parent.width
        height: parent.height
        Component.onCompleted: {
            pageHelper.title = "Import-Export"
            secretTxt.text = ""
        }
        elevation: 5
        anchors.centerIn: parent

        Column{
            width: parent.width
            height: parent.height
            anchors.fill: parent
            spacing: ProtoScreen.guToPx(1.25)

            Label {
                id: welcomeTxt
                width: parent.width / 1.07
                font.pixelSize: Qt.platform.os === "android" ? 32 : 22
                font.family: "Roboto"
                horizontalAlignment: Text.AlignHCenter
                text: "Protoblock account names are not stored on a central server... blah" +
                      "Import from another device. " +
                      "Export or backup"

                wrapMode: Text.WordWrap
            }

            ListItems.Subtitled{
                elevation: 1
                width: parent.width / 1.07
                anchors.horizontalCenter: parent.horizontalCenter
                text: "FantasyName: " + realRoot.uname
                action:Image{
                    height: parent.height
                    width : height
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/icons/action_account_circle.png"
                }
                valueText: "Balance : " + " 0"
            }


            Card{
                id: bcard
                height: nameText.height + importButton.height + imBan.height + ProtoScreen.guToPx(3)
                width: parent.width / 1.07
                anchors.horizontalCenter: parent.horizontalCenter

                Column{
                    width: parent.width
                    height: parent.height
                    spacing: 3
                    Banner{
                        id: imBan
                        text: "Import From Secret Backup"
                        backgroundColor: root.theme.primaryColor
                    }

                    Controls.TextField {
                        id: nameText
                        width: parent.width / 1.07
                        font.family: "Default"
                        placeholderText: "Please enter in you last years 12 secret words"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Button{
                        id: importButton
                        text: "Import From Secret Backup"
                        width: parent.width / 1.07
                        elevation: 1
//                        backgroundColor: root.theme.accentColor
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: {
                            var mypk = MiddleMan.importMnemonic(nameText.text)
                            if ( mypk === "" ) {
                                importExportStatus = "Error: Import failed, please try again"
                            } else {
                                importExportStatus = "Trying to import with key: " + mypk
                            }
                            myImportDialog.show()
                            nameText.text = ""
                            statusTxt.text = importExportStatus;
                            secretTxt.text = ""
                        }
                    }
                }
            }

            Card{
                height:bcard.height
                width: parent.width / 1.07
                anchors.horizontalCenter: parent.horizontalCenter
                Column{
                    width: parent.width
                    height: parent.height
                    spacing: 3
                    Banner{
                        text: "Import From Secret Backup"
                        backgroundColor: root.theme.primaryColor
                    }
                    Label {
                        width: parent.width / 1.07
                        font.pixelSize: Qt.platform.os === "android" ? 32 : 22
                        font.family: "Roboto"
                        horizontalAlignment: Text.AlignHCenter
                        text: ""

                        wrapMode: Text.WordWrap
                    }



                    Button{
                        property string mypk
                        id: exportButton
                        text: "Export Secret 12 Word for Exprt or Backup"
                        width: parent.width / 1.07
                        elevation: 1
//                        backgroundColor: root.theme.accentColor
                        anchors.horizontalCenter: parent.horizontalCenter
                        onClicked: {
                            secretTxt.text = ""
                            mySecretDialog.show()
                        }
                    }
                }


            }
            Button{
                property string mypk
                id: clearSecret
                visible: secretTxt.visible
                text: "Clear secret"
                width: parent.width / 1.07
                elevation: 5
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    secretTxt.text = ""
                }
            }
            Label {
                id: secretTxt
                visible: text.length >= 1? true : false
                width: parent.width / 1.07
                font.pixelSize: Qt.platform.os === "android" ? 32 : 22
                font.family: "Roboto"
                horizontalAlignment: Text.AlignHCenter
                text: ""
                wrapMode: Text.WordWrap
            }
        }
    }













        Dialog {
            id: mySecretDialog
            title: "12 word account Secret"
            positiveButtonText: "show secret"
            negativeButtonText: "get me out of here!"
            Label{
                width: parent.width / 1.07
                wrapMode: Text.WordWrap
                text:  "Please make sure nobody is behind you. Secret to your account: " +realRoot.uname + ", will be displayed!"
            }
            onAccepted: {
                secretTxt.text = "12 word Secret for " + realRoot.uname + ": \n\n" +
                        MiddleMan.getSecret()
            }
        }

    }
