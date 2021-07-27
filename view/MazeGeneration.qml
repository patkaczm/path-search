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

    function onMazeGenerationDone(maze) {
        drawMaze(maze);
    }

    function drawMaze(maze) {
        currentMaze = maze;
        painter.drawMaze(maze, cvs);
        cvs.requestPaint();
    }
    signal generateMaze(int width, int height);

    function isSet(value, bitPos) {
       var result =   Math.floor(value / Math.pow(2, bitPos)) % 2;
       return result === 1;
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
           Layout.minimumWidth: parent.width * 0.6
           Layout.maximumWidth: parent.width * 0.6


//           border.width: 2
//           border.color: "black"
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

        GridLayout {
            Layout.columnSpan: 2
            Layout.rowSpan: 5
            Layout.topMargin: 10
            Layout.rightMargin: 10
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop;
            columns: 2
            rows: 6

        ComboBox {
            objectName: "availableAlgorithms"
            id: availableAlgorithms
            Layout.columnSpan: 2
            Layout.rowSpan: 1
            Layout.fillWidth: true
            displayText: ''
            //@todo exception when start path finding for the second time
            function onAvailableAlgorithmsSet(algorithms) {
                var tmp = []
                for (var alg in algorithms) {
                    tmp.push(algorithms[alg])
                }
                model = tmp
            }
            signal algorithmSelect(variant selected);
            onActivated: {
                console.log("Selected: ", model[index]);
                displayText = model[index];
                algorithmSelect(model[index]);
            }
        }

        ComboBox {
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
            id: gridSizeHeight
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
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
            id: gridSizeWidth
            objectName: "gridSizeWidth"
            editable: true
            value: 3
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
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
            text: "Generate Maze"
            onClicked: {
                console.log(availableAlgorithms.displayText)
                if (availableAlgorithms.displayText === "") {
                    return
                }

                mazeGenerationWindow.generateMaze(mazeGenerationWindow.mazeWidth, mazeGenerationWindow.mazeHeight);
            }
        }

}
    }
}
