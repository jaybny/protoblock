import QtQuick 2.5
import QtQuick.Controls 1.4

import Material 1.0 as Material
import Material.Extras 1.0
import Material.ListItems 1.0 as ListItems
import ProRotoQml.Theme 1.0
//import ProRotoQml.Protoblock 1.0
import QtQuick.Layouts 1.1


Item {
    id: topi

    signal releasedit(string fname)
    property string dragtarget: "dropProxy"

    anchors.fill: parent
//    anchors.margins: ProtoScreen.guToPx(1)
    Item {
//        anchors.top: cb.bottom
        width: parent.width
        height: parent.height //- cb.height

        TableView {
            id: tv
            Component.onCompleted: {
                resizeColumnsToContents()
                model.sortAgain("lastupdate",Qt.DescendingOrder)
            }

            sortIndicatorColumn: 1
            highlightOnFocus:   false
            anchors.fill: parent

            selectionMode: SelectionMode.NoSelection
            model: MiddleMan.pLeaderBoardSortModel
//            sortIndicatorVisible: true
            sortIndicatorOrder: Qt.DescendingOrder
            onSortIndicatorColumnChanged: {
                model.sortAgain(getColumn(sortIndicatorColumn).role, sortIndicatorOrder)
                resizeColumnsToContents();
            }

            onSortIndicatorOrderChanged: {
                model.sortAgain(getColumn(sortIndicatorColumn).role, sortIndicatorOrder)
                resizeColumnsToContents()
            }



            headerDelegate:  Rectangle {
                width: parent.width
                height: ProtoScreen.guToPx(6)
                implicitWidth: textItem2.implicitWidth
                color: "white"
//                anchors.fill: parent
                Material.Card {
                    width: parent.width
                    height: parent.height * .50
                    backgroundColor: themeroot.theme.primaryColor
                    anchors.bottom: parent.bottom
                    radius: 1
                    border.color:
                        styleData.column  === tv.sortIndicatorColumn ? themeroot.theme.accentColor : "black"

                    Material.Label {
                        id: textItem2
                        text: " " + styleData.value + " "
                        anchors.fill: parent
                        font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
                        elide: Text.ElideRight
                        wrapMode: Text.WordWrap
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                    }
                }
            }

            frameVisible: false

            //                width: tv.width / 4.0
            //                    width: tv.width / 4.0
            //                    height: ProtoScreen.guToPx(6)
            //                        height: ProtoScreen.guToPx(3)
            //                        width: win.width * .75
            //Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
//                    x: Math.random() * (win.width / 2 - 100)
//                    y: Math.random() * (win.height - 100)
            //                        radius: 1
            //                        anchors.fill: parent


            TableViewColumn {
                role: "name"
                title: "Fantasy Name"
                horizontalAlignment : Text.AlignHCenter

                delegate:

//                    Item {
//                    id: win
//                    height: tx.height
                    //                        anchors.fill: parent
                    //                        anchors.centerIn: parent;
                    Material.Card {
                        anchors.margins: 0
                        id: mcard
                        anchors.fill: parent
                        flat: true
                        backgroundColor: "#AFE1FF"

//                        height: parent.height
//                        width: parent.width
//                        z: mouseArea.drag.active || mouseArea.pressed ? -20 : -10
                        //Qt.lighter(Colors.blue,1.20)

                        Rectangle {
                        anchors.margins: 0
                        id: rect
                        width: parent.width
                        height: parent.height
                        property point beginDrag
                        property bool caught: false
                        property string fname: styleData.value
                        border { width:ProtoScreen.guToPx(.125); color: "grey" }
                        Drag.active: mouseArea.drag.active
                        color: "transparent"


                        //                            anchors.fill: parent
                        //                            style: Text.Raised
                        Material.Label {
                            id: tx
                            anchors.fill: parent
                            anchors.centerIn: parent
                            text: styleData.value
//                            color: "white"
//                            font.bold: true
                            font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            Layout.fillHeight: true
                            Layout.fillWidth: false
                        }

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            drag.target: rect
                            onClicked: { console.log(" mouse click")}
                            onHoveredChanged: {console.log(" mouse hover")}

                            property int startX
                            property int startY

                            onPositionChanged: {
                                console.log(" mouse onPositionChanged   " + rect.caught)
//                                                                rect.x += mouseX - startX
//                                                                rect.y += mouseY - startY
//                                                                startX = mouseX
//                                                                startY = mouseY
                            }

                            onPressed: {
                                startX = mouseX
                                startY = mouseY
                                console.log(" mouse pressed")
                                rect.beginDrag = Qt.point(rect.x, rect.y);
                            }

                            //                                 MiddleMan.newProjColumn(tx.text)

                            onReleased: {
                                 console.log(" mouse released   " + rect.caught)
                                 if(rect.caught) {
                                    lpv.releasedit(styleData.value)
//                                    backAnimX.duration = 1;
//                                    backAnimY.duration = 1;
//                                    backAnimX.spring = 0;
//                                    backAnimY.spring = 0;
//                                    rect.color = Qt.binding( function() {
//                                        return "transparent"
//                                    })

                                    rect.x = rect.beginDrag.x;
                                    rect.y = rect.beginDrag.y;
                                     mcard.backgroundColor = Qt.binding( function() {
                                        return themeroot.theme.primaryColor
                                     })
                                     tx.color = "white"
                                 }
                                 backAnimX.from = rect.x;
                                 backAnimX.to = rect.beginDrag.x;
                                 backAnimY.from = rect.y;
                                 backAnimY.to = rect.beginDrag.y;
                                 backAnim.start()
                            }
                        }

                        ParallelAnimation {
                            id: backAnim
                            SpringAnimation { id: backAnimX; target: rect; property: "x"; duration: 500; spring: 2; damping: 0.2 }
                            SpringAnimation { id: backAnimY; target: rect; property: "y"; duration: 500; spring: 2; damping: 0.2 }
                        }
                        }
                    }
//                }
            }

            TableViewColumn {
                role: "bits"
                title: "Overall"
                horizontalAlignment : Text.AlignHCenter
                width: ProtoScreen.guToPx(7)


                delegate: Material.Label {
                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
                    text: (styleData.value)//.replace( /(\d)(?=(\d\d\d)+(?!\d))/g, "$1,") + " ƑɃ"
                }
            }

            TableViewColumn{
//                role: "Overall"
                title: "wk1"
                horizontalAlignment : Text.AlignHCenter
                width: ProtoScreen.guToPx(5)
            }

            TableViewColumn{
                role: "numberproj"
                title: "Count"
                horizontalAlignment : Text.AlignHCenter
                width: ProtoScreen.guToPx(5)
            }

            TableViewColumn{
                role: "lastupdate"
                title: "Block"
                horizontalAlignment : Text.AlignHCenter
                width: ProtoScreen.guToPx(10)
                delegate: Material.Label {
                    anchors.centerIn: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
                    text: styleData.value
                }
            }
        }
    }

    function timeSince(date) {

        var seconds = Math.floor((new Date() - date) / 1000);

        var interval = Math.floor(seconds / 31536000);

        if (interval > 1) {
            return interval + " years";
        }
        interval = Math.floor(seconds / 2592000);
        if (interval > 1) {
            return interval + " months";
        }
        interval = Math.floor(seconds / 86400);
        if (interval > 1) {
            return interval + " days";
        }
        interval = Math.floor(seconds / 3600);
        if (interval > 1) {
            return interval + " hours";
        }
        interval = Math.floor(seconds / 60);
        if (interval > 1) {
            return interval + " minutes";
        }
        return Math.floor(seconds) + " seconds";
    }
}


//                    Item {
//                    anchors.fill: parent
//                    id: rootr

//                    MouseArea {
//                        id: mouseArea

//                        anchors.fill: parent
//                        anchors.centerIn: parent
//                        drag.target: dragTarget

//                        onReleased: parent = tile.Drag.target !== null ? tile.Drag.target : rootr

//                        Rectangle {
//                            id: tile

//                            anchors.fill: parent
//                            anchors.verticalCenter: parent.verticalCenter
//                            anchors.horizontalCenter: parent.horizontalCenter

//                            color: "green"

//                            Drag.keys: [ "red" ]
//                            Drag.active: mouseArea.drag.active
//                            states: State {
//                                when: mouseArea.drag.active
//                                ParentChange { target: tile; parent: dragTarget }
//                                AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
//                                PropertyChanges {
//                                    target: tile
//                                    color: "transparent"
//                                }
//                            }

//                        }
//                    }
//                }

//            }
