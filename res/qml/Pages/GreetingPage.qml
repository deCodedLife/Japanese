import QtQuick
import QtQuick.Layouts
import Presets

Item
{
    property var animateTo

    property string greeting
    property Loader sceneLoader

    anchors.fill: parent

    ColumnLayout
    {
        anchors.fill: parent

        Rectangle{ Layout.fillHeight: true }

        Text
        {
            Layout.alignment: Qt.AlignHCenter
            text:　greeting + USERINFO.data["name"] + "さん"

            color: Presets.textColor
            font.bold: true
            font.pointSize: Presets.h1
        }

        Text
        {
            Layout.alignment: Qt.AlignHCenter
            text: "Today score: " + STATS.data["score"]

            color: Presets.textColor
            font.bold: true
            font.pointSize: Presets.h3
        }

        Rectangle{ Layout.fillHeight: true }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: sceneLoader.sourceComponent = animateTo
    }

    function getGreeting()
    {
        var currentTime = Qt.formatTime(new Date(), "hh")
        var currentTimeInt = parseInt( currentTime )

        if ( currentTimeInt < 10 ) greeting = "おはよう"
        if ( currentTimeInt > 10 && currentTimeInt < 16  ) greeting = "こんにちは"
        if ( currentTimeInt > 16 ) greeting = "こんばんは"
    }

    Component.onCompleted: getGreeting()
}
