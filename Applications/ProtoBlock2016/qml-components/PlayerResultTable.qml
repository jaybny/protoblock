import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Material 1.0 as Material
import Material.Extras 1.0
import Material.ListItems 1.0 as ListItems
import ProRotoQml.Theme 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Private 1.0

Item {
    id: topw
    anchors.fill: parent
    signal indrop(string fname)
    signal donedrop
    signal addcolumn(string fname)

    property alias ccount: tv.columnCount
    property int focuscount: 0
    property string who: "default"
    property int rw: 8
    Item {
        id: i2
        anchors.top: parent.top
        width: parent.width
        height: parent.height - ProtoScreen.guToPx(8)

        TableView {
            id: tv
            Component.onCompleted: {
                ppt.addcolumn.connect(addcolumnMethod)
                MiddleMan.pResultsViewFilterProxyModel.sortAgain("result", sortIndicatorOrder)
            }

//            onClicked: {
//                expand(index)
//            }

            function addcolumnMethod(fname) {
//                customRoleNames[0] = fname
                console.log(" addColumn " )
                var role = MiddleMan.addFnameColumn(fname,tv.columnCount)
                tv.addColumn(columnComponent.createObject(tv, {
                                                              "role": role,
                                                              "title": fname,
                                                              "horizontalAlignment": Text.AlignHCenter,
                                                              "delegate": copydel
                                                          })
                             )


//                tv.resizeColumnsToContents()
            }
            highlightOnFocus: false
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height
            implicitWidth: parent.width
            model: MiddleMan.pResultsViewFilterProxyModel

            sortIndicatorVisible: true
            sortIndicatorOrder: Qt.DescendingOrder
            onSortIndicatorColumnChanged: {
                MiddleMan.pResultsViewFilterProxyModel.sortAgain(getColumn(sortIndicatorColumn).role, sortIndicatorOrder)
            }

            onSortIndicatorOrderChanged: {
                MiddleMan.pResultsViewFilterProxyModel.sortAgain(getColumn(sortIndicatorColumn).role, sortIndicatorOrder)
            }

            headerDelegate: headerdel
            frameVisible: false
            selectionMode: SelectionMode.NoSelection

            rowDelegate: Rectangle {
               height: ProtoScreen.guToPx(3)
//               SystemPalette {
//                  id: myPalette;
//                  colorGroup: SystemPalette.Inactive
//               }
               color: styleData.alternate?"#f5f5f5":"transparent"
//               {
//                  var baseColor = styleData.alternate?"#f5f5f5":"transparent"
//                  return styleData.selected?myPalette.highlight:baseColor
//               }
            }


            TableViewColumn {
                role: "lastname"
                title: "Player Name"
                horizontalAlignment : Text.AlignLeft
                movable: false
                delegate: Material.Card {
                    flat: true
                    radius: 0
                    border.width: 0
                    anchors.fill: parent
                    backgroundColor: "transparent"
                    Material.Label {
                        id: lll
                        anchors.leftMargin: ProtoScreen.guToPx(.25)
                        anchors.topMargin: ProtoScreen.guToPx(.25)
                        anchors.bottomMargin: ProtoScreen.guToPx(.25)
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        text: styleData.value
                        font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: false
                    }

                    Component.onCompleted: {
                    lll.text = Qt.binding(function() {
                        if ( !model )
                            return styleData.value
                        else
                            return model.fullname

                    })

                    backgroundColor = Qt.binding(function() {
                        if ( !model )
                            return "transparent"
                        else {
                            switch(model.pos) {
                            case "WR":
                                return "#FEFBB6";
                            case "RB":
                                return "#BCFAAD";
                            case "QB":
                                return "#F8ADAA";
                            case "TE":
                                return "#CCB4F0";
                            case "K":
                                return "#FBD580";
                            case "DEF":
                                return "#AFE1FF";
                            default:
                                return "transparent";
                            }
                        }
                    })
                    }
                }
            }

            TableViewColumn {
                id: tvm
                role: "pos"
                title: "Position"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(7)
                delegate: Material.Card {
                    flat: true
                    radius: 0
                    border.width: 0
                    anchors.fill: parent
                    anchors.centerIn: parent
                    backgroundColor: "transparent" //TeamInfo.getPosColor(styleData.value)
                    Material.Label {
                        anchors.centerIn: parent
                        id: lbl
                        text: " " + styleData.value + " "
                        font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: false
                    }
                    Component.onCompleted: {
                        backgroundColor = Qt.binding(function() {
                            switch(styleData.value) {
                                case "WR":
                                    return "#FEFBB6";
                                case "RB":
                                    return "#BCFAAD";
                                case "QB":
                                    return "#F8ADAA";
                                case "TE":
                                    return "#CCB4F0";
                                case "K":
                                    return "#FBD580";
                                case "DEF":
                                    return "#AFE1FF";
                                default:
                                    return "transparent";
                            }
                        })
                    }
                }
            }

            TableViewColumn{
                id: teamcol
                role: "teamid"
                title: "Team"
                horizontalAlignment : Text.AlignHCenter
                width: ProtoScreen.guToPx(6)

                delegate: Material.Label {
                    text: styleData.value
                    font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: false
                    Component.onCompleted: {
                        color = Qt.binding(function() {
                            return TeamInfo.getPrimaryAt(text)
                        })
                    }
                }
            }

            TableViewColumn{
                role: "result"
                title: "Result"
                horizontalAlignment : Text.AlignHCenter
                delegate: resdel
                movable: false
                width: ProtoScreen.guToPx(10)
            }

            TableViewColumn {
                role: "fb"
                title: "ƑɃ"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(10)
                delegate: fbdel
            }

            TableViewColumn {
                role: "PassTD"
                title: "PassTD"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }

            TableViewColumn {
                role: "PassYd"
                title: "PassYd"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "RushTD"
                title: "RushTD"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "RushYd"
                title: "RushYd"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "RecTD"
                title: "RecTD"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "RecYd"
                title: "RecYd"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "Rec"
                title: "Rec"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "Int"
                title: "Int"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "Fum"
                title: "Fum"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "_2Pt"
                title: "2Pt"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "PAT"
                title: "PAT"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "FG"
                title: "FG"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "D_TD"
                title: "D_TD"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "Sack"
                title: "Sack"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "TO"
                title: "TO"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "SFTY"
                title: "SFTY"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "D2pt"
                title: "Def2pt"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
            TableViewColumn {
                role: "PtsA"
                title: "PtsAlw"
                horizontalAlignment : Text.AlignHCenter
                movable: false
                width: ProtoScreen.guToPx(rw)
                delegate: fbdel
            }
        }
    }

    Component {
        id: headerdel
        Rectangle {
            id: idd
            implicitWidth: textItem2.implicitWidth
            height: ProtoScreen.guToPx(8)
            color: "white"
            Rectangle {
                id: rec
                height: parent.height * .50
                width: parent.width
                color: "transparent"
                anchors.top: parent.top
                ComboBox {
                    id: cbc
                    model: ["All","QB" , "RB" , "WR" , "TE" , "K" , "DEF"]
                    enabled: styleData.column === 1
                    currentIndex: 0
                    visible: styleData.column === 1
                    anchors.fill: parent
                    onCurrentTextChanged: {
                       MiddleMan.pResultsViewFilterProxyModel.setPos(currentText)
                    }
                }

                Material.IconButton {
                    id: exportit
                    anchors.left: parent.left
                    anchors.top: parent.top
                    Layout.fillHeight: true
                    Layout.fillWidth: false
                    width: ProtoScreen.guToPx(6)
                    height: parent.height
                    onClicked: {
                        importexportDialog.show();
                    }

                    size: ProtoScreen.guToPx(2.5)


                    visible: false//styleData.column === 0
                    enabled: false//styleData.column === 0
                    action: Material.Action {
                        iconName: "awesome/code"
                        hoverAnimation: true
                    }
                }

            }

            Material.Card {
                id: mcbot
                width: parent.width
                height: parent.height * .50
                backgroundColor: styleData.column === 4 ? themeroot.theme.accentColor :
                                 themeroot.theme.primaryColor
                anchors.bottom: parent.bottom
                radius: 1
                border.color:
                    styleData.column  === tv.sortIndicatorColumn ? themeroot.theme.accentColor
                                                                 : "black"
                Material.Label {
                    anchors.margins: ProtoScreen.guToPx(.25)
                    id: textItem2
                    text: styleData.value
                    anchors.fill: parent
                    font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
                    elide: Text.ElideRight
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: styleData.column === 4 ? themeroot.theme.secondaryColor : "white"
                    //                    font.bold: styleData.column === 4
                }
            }

        }
    }

    Component {
        id: copydel

        Material.Label {
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
            text: (styleData.value)
        }
    }

    Component {
        id: statdel

        Material.Label {
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
            text: (styleData.value)
        }
    }

    Component {
        id: resdel

        Material.Label {
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
            text: !model ? "" : model.result.toFixed(2)
            font.bold: true;
        }
    }

    Component {
        id: bfbdel

        Material.Label {
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
            text: styleData.value
            font.bold: true;
        }
    }

    Component {
        id: fbdel

        Material.Label {
            anchors.centerIn: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            font.pixelSize: ProtoScreen.font(ProtoScreen.SMALL)
            text: (styleData.value < 1) ? "" : styleData.value;
            font.bold: false;
        }
    }

    Component {
        id: columnComponent
        TableViewColumn {
            width: 100
        }

    }
}

