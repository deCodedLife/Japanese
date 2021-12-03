import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Presets

Item
{
    id: root

    signal showed()
    signal clicked()
    signal destroed()

    property int sized
    property int radius

    property string title
    property string subTitle

    property int animateTO: 1
    property int startX
    property var color: Material.accentColor

    width: Presets.dp(sized)
    height: Presets.dp(sized)

    Rectangle
    {
        id: background

        anchors.fill: parent
        radius: root.radius
        opacity: 0
        color: root.color

        ColumnLayout
        {
            anchors.fill: parent
            anchors.margins: Presets.defaultMargin

            Rectangle { Layout.fillHeight: true }

            Text
            {
                id: cardContext
                Layout.alignment: Qt.AlignHCenter

                text: title
                color: "black"

                font.bold: true
                font.pointSize: Presets.h1
            }

            Text
            {
                id: cardSubtitle
                visible: subTitle.trim().length > 1 ? true : false
                Layout.alignment: Qt.AlignHCenter

                text: subTitle
                color: "black"

                font.pointSize: Presets.h4
            }


            Rectangle { Layout.fillHeight: true }
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked: root.clicked()
        }

        NumberAnimation on opacity
        {
            id: toggleAnimation
            to: 1
            duration: 250
            running: false
            onFinished: root.showed()
        }

        NumberAnimation on opacity
        {
            id: hideAnimation
            to: 0
            duration: 250
            running: false
            onFinished: root.destroed()
        }

    }

    NumberAnimation on x
    {
        id: resetPositionAnimation

        from: root.x
        to: startX
        duration: 200
        running: false

        easing.type: Easing.Linear
    }

    function resetStartPos()
    {
        resetPositionAnimation.running = true
    }

    function show()
    {
        toggleAnimation.running = true
    }

    function hide()
    {
        hideAnimation.running = true
    }

    Component.onCompleted:
    {
        show()
        startX = root.x
    }
}
