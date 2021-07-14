import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

Item {
    id: mazeGenerationWindow
    width: parent.width
    height: parent.height
    RectangleThickMazePainter {
        id: rectangleThickMazePainter
    }
    RectangleThinMazePainter {
        id: rectangleThinMazePainter
    }

    property alias generateButton: generateButton
    property var currentMaze: null;
    property var painter: rectangleThickMazePainter;
    property var mazeWidth: 3
    property var mazeHeight: 3

    function drawMaze(maze) {
        currentMaze = maze;
        painter.drawMaze(maze, cvs);
        cvs.requestPaint();
    }

    GridLayout {
        columns: 3
        rows: 5
        width: parent.width
        height: parent.height
        Layout.margins: 10

        Rectangle {
           Layout.columnSpan: 1
           Layout.rowSpan: 5

           Layout.fillHeight: true
           Layout.fillWidth: true
           Layout.margins: 10

           border.width: 2
           border.color: "black"
           onWidthChanged: {
               cvs.width = width < height ? width : height;
               cvs.height = width < height ? width : height;
           }
           onHeightChanged: {
               onWidthChanged();
           }

           Canvas {
               id: cvs
               Layout.fillHeight: true
               Layout.fillWidth: true
           }
        }

        ComboBox {
            Layout.topMargin: 10
            Layout.rightMargin: 10
            Layout.columnSpan: 2
            Layout.rowSpan: 1
            Layout.fillWidth: true
            model : ["Thick walls", "Thin walls"]
            onActivated: {
                if (model[index] === "Thin walls") {
                    mazeGenerationWindow.painter = rectangleThinMazePainter;
                } else if (model[index] === "Thick walls") {
                    mazeGenerationWindow.painter = rectangleThickMazePainter;
                }
                mazeGenerationWindow.drawMaze(currentMaze);
            }
        }


        Text {
            id: text3
            text: qsTr("grid height")
            font.pixelSize: 12
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        SpinBox {
            Layout.rightMargin: 10
            id: gridSizeHeight
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            objectName: "gridSizeHeight"
            editable: true
            value: 3
            from: 1
            to: 51
            onValueChanged: {
                mazeGenerationWindow.mazeHeight = value
            }
        }

        Text {
            id: text2
            text: qsTr("grid width")
            font.pixelSize: 12
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        SpinBox {
            Layout.rightMargin: 10
            id: gridSizeWidth
            objectName: "gridSizeWidth"
            editable: true
            value: 3
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            to: 51
            from: 1
            onValueChanged: {
                mazeGenerationWindow.mazeWidth = value
            }
        }

        Button {
            id: generateButton
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop;
            Layout.rightMargin: 10
            text: "Generate Maze"
        }


    }
}
