import QtQuick

Item
{
    property string title
    property string qml

    property bool selected

    function fromJson(json)
    {
        title = json["title"]
        qml = json["qml"]
    }
}
