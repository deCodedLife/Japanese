pragma Singleton

import QtQml
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Material

Item
{
    Material.accent: Material.Orange
    Material.theme: Material.Dark

    property int dpi: Screen.PixelDensity * 25.4

    function dp(x)
    {
        if ( dpi < 120 ) return x;
        return x * (dpi / 160)
    }

    function fontDp(x)
    {
        var platform = Qt.platform.os

        if (  platform === "android" || platform === "ios" ) return dp(x) * 1.2
        else return dp(x)
    }

    readonly property string textColor: "white"
    readonly property string highlitedTextColor: "white"
    readonly property string accentColor: Qt.rgba(0.7, 0, 0, 1)

    readonly property int defaultHeight: dp(48)
    readonly property int defaultMargin: dp(5)

    readonly property int h1: fontDp(24)
    readonly property int h2: fontDp(18)
    readonly property int h3: fontDp(14)
    readonly property int h4: fontDp(12)
    readonly property int h5: fontDp(8)
}
