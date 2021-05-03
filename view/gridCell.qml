import QtQuick 2.12

Rectangle {
    color: "blue"
    property int cellId;

    signal clicked(int cellId);

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked(parent.cellId)
    }
}
