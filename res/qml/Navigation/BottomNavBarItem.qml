import QtQuick
import QtQuick.Controls

Item
{
    id: root

    signal clicked()

    property int sized
    property bool selected
    property string imgSrc

    height: sized

    Button
    {
        anchors.centerIn: parent

        width: root.sized
        height: root.sized

        background: Rectangle { color: Qt.rgba(0,0,0,0) }

        id: iconButton
        highlighted: true
        icon.source: imgSrc

        onClicked:
        {
            root.clicked()
        }
    }

    states: [
        State
        {
            name: "unselected"
            PropertyChanges
            {
                target: iconButton
                icon.color: "white"
            }
        },

        State
        {
            name: "selected"
            PropertyChanges
            {
                target: iconButton
                icon.color: Material.accentColor
            }
        }
    ]

    function select()
    {
        state = "selected"
    }

    function unselect()
    {
        state = "unselected"
    }
}
