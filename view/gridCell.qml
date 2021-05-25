import QtQuick 2.12

Rectangle {
    color: "blue"
    property int cellId;
    property alias border: brd

    signal clicked(int cellId);

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked(parent.cellId)
    }
    CustomBorder {
        id: brd
        commonBorder: true
        commonBorderWidth: 1
        borderColor: "black"
    }

}
