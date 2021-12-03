import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Universal
import QtQuick.Controls.Material

import Presets
import "../Components"

Item
{
    id: root
    anchors.fill: parent

    Card
    {
        anchors.fill: parent
        anchors.margins: Presets.defaultMargin * 5
        radius: 5
        color: Universal.baseLowColor

        ColumnLayout
        {
            anchors.fill: parent
            anchors.margins: Presets.defaultMargin * 2

            spacing: Presets.defaultMargin

            Text
            {
                Layout.fillWidth: true
                text: "Выберите наиболее подходящий вариант"

                color: Presets.textColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                font.bold: true
                font.pointSize: Presets.h2
            }

            Rectangle { height: Presets.defaultMargin }

            Text
            {
                Layout.fillWidth: true
                text: "きのう、友だち___新宿へいきました"

                color: Presets.textColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                font.bold: true
                font.pointSize: Presets.h2
            }

            ListView
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                clip: true
                model: ["に", "が", "と", "は"]

                delegate: RadioButton
                {
                    x: Presets.defaultMargin * 2
                    text: modelData
                }
            }

            Button
            {
                Layout.alignment: Qt.AlignRight
                flat: true
                text: "Submit"
            }
        }
    }
}
