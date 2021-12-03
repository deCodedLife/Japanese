import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import Presets
import "Navigation"
import "Components"
import "Pages"

ApplicationWindow
{
    id: root
    width: 480
    height: 700
    visible: true

    Material.accent: Material.Yellow
    Material.theme: Material.Dark

    property var pagesList: [
        {
            "title": "Quiz",
            "icon": "qrc:/Images/img/icons/translate_white_24dp.svg",
            "qml": "../Pages/QuizPage.qml",
            "withProgress": true
        },
        {
            "title": "Grammar",
            "icon": "qrc:/Images/img/icons/book_white_24dp.svg",
            "qml": "../Pages/LearningPage.qml",
            "withProgress": true
        },
        {
            "title": "Training",
            "icon": "qrc:/Images/img/icons/note_alt_white_24dp.svg",
            "qml": "../Pages/Training.qml",
            "withProgress": false
        },
        {
            "title": "Settings",
            "icon": "qrc:/Images/img/icons/settings_white_24dp.svg",
            "qml": "../Pages/SettingsPage.qml",
            "withProgress": false
        }
    ]

    Loader
    {
        id: mainLoader
        anchors.fill: parent

        sourceComponent: GreetingPage
        {
            sceneLoader: mainLoader
            animateTo: navigation
        }
    }

    Component
    {
        id: navigation

        BottomNavigation
        {
            anchors.fill: parent
            pages: pagesList
        }
    }
}
