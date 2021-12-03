import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Presets

Item
{
    id: root
    anchors.fill: parent

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: Presets.defaultMargin * 2
        spacing: Presets.defaultMargin

        TextField
        {
            id: urlAddrTextbox
            Layout.fillWidth: true
            placeholderText: "http://localhost:9180"
        }

        Button
        {
            text: "Update"
            highlighted: true
            Layout.alignment: Qt.AlignRight

            onClicked:
            {
                if ( urlAddrTextbox.text.trim().length > 1 )
                {
                    UPDATER.getWords(urlAddrTextbox.text + "/words")
                }
                else
                {
                    UPDATER.getWords("http://localhost:9180/words")
                }
            }
        }

        Rectangle{ Layout.fillHeight: true }
    }
}
