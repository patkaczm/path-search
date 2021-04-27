import QtQuick 2.12

Rectangle {
    width: 100
    height: 100
    color: "blue"
    property int cellId;

    signal clicked(int cellId);

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked(parent.cellId)
    }
}
