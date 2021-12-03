import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Presets
import "../Components"

Item
{
    id: root
    anchors.fill: parent

    Card
    {
        sized: Presets.dp(250)
        anchors.centerIn: parent
        radius: 5
        title: "Select topic"
        subTitle: "1"
    }
}
