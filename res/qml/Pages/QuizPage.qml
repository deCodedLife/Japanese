import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import DB
import Presets

import "../Components"

Item
{
    id: root
    anchors.fill: parent

    state: "Preview"
    states: [
        State
        {
            name: "Preview"
            PropertyChanges
            {
                target: pages
                sourceComponent: previewPage
            }
        },
        State
        {
            name: "Quiz"
            PropertyChanges
            {
                target: pages
                sourceComponent: quizPage
            }
        }
    ]

    Loader
    {
        anchors.fill: parent

        id: pages
        sourceComponent: previewPage
    }

    Component
    {
        id: previewPage

        Item
        {
            anchors.fill: parent

            Card
            {
                sized: 250
                radius: 5
                anchors.centerIn: parent

                title: "行きましょう"
                subTitle: ""

                onClicked:
                {
                    root.state = "Quiz"
                }
            }
        }
    }

    Component
    {
        id: quizPage

        Item
        {
            id: quiz
            anchors.fill: parent

            property var words: DATABASE.getWords()
            property var current: words[0]

            states: [
                State
                {
                    name: "original"
                    PropertyChanges
                    {
                        target: card

                        title: quiz.current["ja"]
                        subTitle: ""
                    }
                },
                State
                {
                    name: "translated"

                    PropertyChanges
                    {
                        target: card

                        title: quiz.current["ru"]
                        subTitle: quiz.current["pr"]
                    }
                }

            ]

            state: "original"

            Card
            {
                id: card
                sized: 250
                radius: 5

                function resetPosition()
                {
                    x = parent.width / 2 - width / 2
                    y = parent.height / 2 - height / 2
                }

                title: ""
                subTitle: ""

                onClicked:
                {
                    quiz.state = quiz.state === "original" ? "translated" : "original"
                }

                onDestroed:
                {
                    card.show()

                    if ( quiz.state == "translated" )
                    {
                        STATS.data = {
                            "id": STATS.data["id"],
                            "date": STATS.data["date"],
                            "score": STATS.data["score"] + 10
                        }
                    }

                    quiz.state = "original"
                    quiz.pickRandomWord()
                    card.resetPosition()
                }

                ProgressBar
                {

                }

                MouseArea
                {
                    id: mouse
                    propagateComposedEvents: true
                    anchors.fill: parent

                    drag
                    {
                        target: card
                        axis: Drag.XAxis
                    }

                    onPressedChanged:
                    {
                        if ( card.x + card.width > card.parent.width || card.x < 0 )
                        {
                            card.hide()
                        } else
                        {
                            card.resetStartPos()
                        }
                    }
                }
            }

            function pickRandomWord()
            {
                var randomWord = Math.floor( Math.random() * quiz.words.length )
                quiz.current = quiz.words[ randomWord ];
            }

            Timer
            {
                id: delay
                repeat: false
                onTriggered: showCard()
            }

            Component.onCompleted: card.resetPosition()
        }
    }
}
