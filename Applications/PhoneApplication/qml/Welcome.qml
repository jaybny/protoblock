import QtQuick 2.0
import Material 1.0

Rectangle {
    color: "#F1F1F1"
    width: rootLoader.width
    height: rootLoader.height
    Component.onCompleted:  pageHelper.title = qsTr("2015 Final Results")
    Image {
        id: logo
        source: "qrc:/logoFinal.png"
        width: parent.width / 1.07
        fillMode: Image.PreserveAspectFit
        height: parent.height / 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height / 22
    }
    Label {
        id: welcomeTxt
        anchors.top: logo.bottom
        anchors.topMargin:  paintedHeight
        width: parent.width / 1.07
        font.pixelSize: Qt.platform.os === "android" ? 48 : 22
        font.family: "Roboto"
        horizontalAlignment: Text.AlignHCenter
        text: qsTr("Welcome to Protoblocks tally of 2015 results")
        wrapMode: Text.WordWrap
    }
    Column{
        id:buttons
        width: button1.width
        height: button1.height * 2 + spacing
        spacing: 5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: welcomeTxt.bottom
        anchors.topMargin: 10
        Button{
            id: button1
            width: rootLoader.width / 1.07
            height: rootLoader.height / 6
            text: "Projections"

            onClicked: rootLoader.source = "qrc:/ProjectionsLevelOne.qml"
            elevation: 2
        }

        Button{
            width: rootLoader.width / 1.07
            height: rootLoader.height / 6
            text: "Trading"
            onClicked: rootLoader.source = "qrc:/PnL.qml"
            elevation: 2
        }
    }
}
