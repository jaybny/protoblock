/*
 * QML Material - An application framework implementing Material Design.
 *
 * Copyright (C) 2014-2015 Jordan Neidlinger <JNeidlinger@gmail.com>
 *               2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

import QtQuick 2.4
import QtQuick.Controls 1.3 as Controls
import Material.Styles 1.0 as MaterialStyle
import ProRotoQml.Utils 1.0
import Material 1.0
import ProRotoQml.Theme 1.0
/*!
   \qmltype RadioButton
   \inqmlmodule Material

   \brief Radio buttons allow the user to select one option from a set.
*/
Controls.RadioButton {
    id: radioButton

    /*!
       The switch color. By default this is the app's accent color
     */
    property color color: darkBackground ? Theme.dark.accentColor
                                         : Theme.light.accentColor

    /*!
       Set to \c true if the switch is on a dark background
     */
    property bool darkBackground

    /*!
       Set to \c true if the radio button can be toggled from checked to unchecked
     */
    property bool canToggle

    style: MaterialStyle.RadioButtonStyle {}

    Ink {
        id: inkArea
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: ProtoScreen.guToPx(2)
        }

        width: ProtoScreen.guToPx(40/8)// * Units.dp
        height: ProtoScreen.guToPx(40/8)//40 * Units.dp
        color: radioButton.checked ? Theme.alpha(radioButton.color, 0.20) : Qt.rgba(0,0,0,0.1)

        onClicked: {
            if(radioButton.canToggle || !radioButton.checked)
                radioButton.checked = !radioButton.checked
            radioButton.clicked()
        }

        circular: true
        centered: true
    }

    MouseArea {
        anchors {
            left: inkArea.right
            top: parent.top
            right: parent.right
            bottom: parent.bottom
        }
        onClicked: {
            if(radioButton.canToggle || !radioButton.checked)
                radioButton.checked = !radioButton.checked
            radioButton.clicked()
        }
    }
}
