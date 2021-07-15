import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import QtQml 2.15

Window {
    width: 1000
    minimumWidth: width
    maximumWidth: width
    height: 600
    minimumHeight: height
    maximumHeight: height
    visible: true
    title: qsTr("Path Search")
    objectName: "mainWindow"

MazeGeneration {
    visible: false
    id: mazeGenerationWindow
    objectName: "mazeGenerationWindow"
    width: parent.width
    height: parent.height
}

PathFinding {
    visible: false
    id: pathFindingWindow
    objectName: "pathFindingWindow"
    width: parent.width
    height: parent.height
}

    Item {
        visible: true
        id: menu
        width: parent.width
        height: parent.height
        ColumnLayout {
            width: parent.width * 0.5
            height: parent.height * 0.4
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Maze generation"
                onClicked: {
                    menu.visible = false;
                    mazeGenerationWindow.visible = true;
                }
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "Path finding"
                onClicked: {
                    menu.visible = false;
                    pathFindingWindow.visible = true;
                }
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
