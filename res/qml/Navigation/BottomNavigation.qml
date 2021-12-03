import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Presets
import "../Components"

Item
{
    id: root

    property var pages: parent.pages
    property int currentPage: 0

    ColumnLayout
    {
        anchors.fill: parent

        CustomProgressBar
        {
            id: progressBar
            Layout.fillWidth: true

            height: Presets.dp(28)

            from: 0
            to: 1000

            value: STATS.data["score"]
        }

        Loader
        {
            id: loader
            source: pages[currentPage]["qml"]

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: Presets.defaultMargin

            onSourceChanged:
            {
                if ( pages[currentPage]["withProgress"] === false )
                    progressBar.visible = false
                else
                    progressBar.visible = true
            }
        }

        Rectangle
        {
            id: bottomBar
            height: Presets.dp(64)
            Layout.fillWidth: true
            color: Qt.rgba(0,0,0,0)

            Rectangle
            {
                anchors.top: parent.top
                width: parent.width
                height: 1
                color: "lightgrey"
            }

            ListView
            {
                id: bottomNavList
                property int lastIndex

                model: pages
                anchors.fill: parent
                interactive: false
                orientation: ListView.Horizontal

                delegate:
                BottomNavBarItem
                {
                    id: navItem
                    property int itemIndex: index

                    sized: bottomBar.height
                    width: bottomNavList.width / pages.length

                    imgSrc: modelData["icon"]

                    onClicked:
                    {
                        if ( itemIndex == bottomNavList.currentIndex ) return

                        bottomNavList.currentIndex = bottomNavList.lastIndex
                        bottomNavList.currentItem.unselect()

                        bottomNavList.lastIndex = itemIndex

                        navItem.select()
                        bottomNavList.currentIndex = itemIndex
                    }
                }

                onCurrentIndexChanged: currentPage = currentIndex
                Component.onCompleted: currentItem.select()
            }
        }

    }
}
