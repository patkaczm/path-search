import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

Item {
    id: pathFindingWindow
    width: parent.width
    height: parent.height

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
           Layout.minimumWidth: parent.width / 5 * 3

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
               property var gridHeight: 6
               property var gridWidth: 6

               readonly property var emptyFiled: ({ color: "white", value: 0});
               readonly property var startField: ({ color: "green", value: 1});
               readonly property var stopField: ({ color: "red", value: 2});
               readonly property var obstacleField: ({ color: "black", value: 3});
               readonly property var visitedField: ({ color: "yellow", value: 4});
               readonly property var pathField: ({ color: "blue", value: 5});

               property var cells: Array.from({length: gridHeight * gridWidth}, (_) => emptyFiled);
               property var startFieldId: undefined;
               property var stopFieldId: undefined;

               property var select: obstacleField

               function paintGrid()
               {
                   let ctx = cvs.getContext("2d");
                   ctx.beginPath();
                   for (var x = 0; x <= gridWidth; x++) {
                       ctx.moveTo(x * width / gridWidth, 0);
                       ctx.lineTo(x * width / gridWidth, height);
                   }
                   for (var y = 0; y <= gridHeight ; y++) {
                       ctx.moveTo(0, y * height / gridHeight);
                       ctx.lineTo(width, y * height / gridHeight);
                   }
                   ctx.stroke();
               }
               function paintCells()
               {
                   let ctx = cvs.getContext("2d");
                   let cellXSize = width / gridWidth;
                   let cellYSize = height / gridHeight;

                   ctx.beginPath();
                   for (var i = 0; i < cells.length; i++) {
                       let x = (i % gridWidth) * cellXSize;
                       let y = Math.floor(i / gridWidth) * cellYSize;
                        console.log(x, y, cellXSize, cellYSize, cells[i].color)
                       ctx.fillStyle = cells[i].color;
                       ctx.fillRect(x , y , cellXSize , cellYSize );
                   }
                   ctx.fill();
               }

               MouseArea {
                   anchors.fill: parent
                   function getCellId(mouseX, mouseY)
                   {
                       let cellXSize = width / cvs.gridWidth;
                       let cellYSize = height / cvs.gridHeight;
                       var X = Math.floor(mouseX/cellXSize);
                       var Y = Math.floor(mouseY/cellYSize);
                       var id = Math.floor(mouseY/cellYSize) * cvs.gridWidth + Math.floor(mouseX/cellXSize);
                       console.log("X: ", X," Y: ", Y, " id: ", id);
                       return id;
                   }
                   function clearPreviouslySelected(type) {
                       if (cvs.select === type) {
                           for(var i = 0; i < cvs.cells.length; i++) {
                               if (cvs.cells[i] === type)
                               {
                                   cvs.cells[i] = cvs.emptyFiled;
                                   break;
                               }
                           }
                       }
                   }

                   onClicked: {
                       clearPreviouslySelected(cvs.startField);
                       clearPreviouslySelected(cvs.stopField);

                       cvs.cells[getCellId(mouseX, mouseY)] = cvs.select;
                       //check start and end
                       cvs.paintCells();
                       cvs.paintGrid();
                       cvs.requestPaint();
                   }
               }
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
            rows: 5
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
            function selectStart(){cvs.select = cvs.startField}
            function selectEnd() {cvs.select = cvs.stopField}
            function selectObstacle() {cvs.select = cvs.obstacleField}

            property var btnData: [
                                   {name: "Start", action: selectStart, colspan: 1},
                                   {name: "End", action: selectEnd, colspan: 1},
                                   {name: "Obstacle", action: selectObstacle, colspan: 1},
                                   {name: "Clear", action: null, colspan: 1},
                                   {name: "Find Path", action: null, colspan: 2},
                                  ]
            Repeater {
                model: parent.btnData
                Button {
                    Layout.columnSpan: parent.btnData[index]["colspan"]
                    Layout.fillWidth: true
                    text: modelData.name
                    onClicked: {
                        parent.btnData[index]["action"]()
                    }
                }
            }
        }



    }

}
