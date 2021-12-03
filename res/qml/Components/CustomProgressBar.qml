import QtQuick
import QtQuick.Templates as T

import QtQuick.Controls.Universal
import QtQuick.Controls.Universal.impl

import QtQuick.Controls.Material

T.ProgressBar
{
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)

    contentItem: ProgressBarImpl
    {
        implicitHeight: control.height
        z: -1


        scale: control.mirrored ? -1 : 1
        color: Material.accent
        progress: control.position
        indeterminate: control.visible && control.indeterminate

    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: control.height

        y: (control.height - height) / 2
        height: control.height

        visible: !control.indeterminate
        color: control.Universal.baseLowColor
    }
}
