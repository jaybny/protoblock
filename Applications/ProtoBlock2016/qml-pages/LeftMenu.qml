import QtQuick 2.5
import Material 1.0
import Material.ListItems 1.0 as ListItem

Item {
    property string strCheck: section[0]
    Sidebar {
        id: sidebar
        expanded: !navDrawer.enabled
        Column {
            width: parent.width
            Repeater {
                model: section
                delegate: ListItem.Subtitled {
                    text: modelData
                    selected: modelData === strCheck
                    onSelectedChanged: console.log(index)
                    onClicked: {
                        strCheck= section[index]
                        pageHelper.title = modelData
                        var theFile = modelData
                        rootLoader.source  = Qt.resolvedUrl(theFile.replace(/\s/g, "") + ".qml" )
                    }
                }
            }
        }
    }
}
