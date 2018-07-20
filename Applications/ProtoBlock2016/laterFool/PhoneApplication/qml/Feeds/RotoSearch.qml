import QtQuick 2.0
import QtQuick.XmlListModel 2.0
import QtQuick.Controls 1.4
import QtWebEngine 1.2

import Material 1.0
import Material.ListItems 1.0 as ListItems

Item {
    signal reload()
    ListView{
        width: parent.width
        height: parent.height
        clip: true
        spacing: 3
        model:xmlModel
        delegate: ListItems.Subtitled{
            elevation:  5
            text: model.title
            subText: model.summary + " \nCopyright 2016, CBSSports.com"
            maximumLineCount: 4
            onClicked:{
                webView.url = model.link
                wView.shown = true
            }
        }
    }
    XmlListModel{
        id: xmlModel
        source: "http://www.rotoworld.com/rss/feed.aspx?sport=nfl&ftype=article&count=50&format=rss"
        query: "/rss/channel/item"
        XmlRole{name: "title" ; query: "title/string()" }
        XmlRole{name: "summary" ; query: "description/string()" }
        XmlRole{name: "link" ; query: "link/string()" }
    }




    Rectangle{
        id: wView
        scale: shown === true ? 1 : 0
        property bool shown: false
        width: shown === true ?  parent.width : 0
        height:shown === true ?   parent.height - back.height : 0
        ListItems.Standard{
            id: back
            elevation: 8
            text: "back"
            onClicked: wView.shown = false
            visible: wView.shown === true ?  true : false
        }
        WebEngineView {
            id: webView
            scale: wView.shown === true ? 1 : 0
            width: wView.shown === true ?  parent.width : 0
            height:wView.shown === true ?   parent.height - back.height : 0
            anchors.top: back.bottom
            onLoadProgressChanged:  {
                if( wView.shown === true ){
                    if (webView.loadProgress < 90){
                        opacity = 0
                    }else{
                        opacity = 1
                    }
                }
            }
            Behavior on opacity {NumberAnimation{duration: 600; }}
        }
    }
}