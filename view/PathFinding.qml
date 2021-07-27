import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

Item {
    id: pathFindingWindow
    width: parent.width
    height: parent.height

    signal startPathFinding(variant gridCells, int width);
    function onPathFindingDone(pathV) {
        if (showSteps.checked) {
            timer.path = pathV;
            console.log(timer.path)
            if (!timer.running) {
                timer.start();
            }
        } else {

         for (var prop in pathV) {
                if (cvs.cells[pathV[prop]] === cvs.startField ||
                    cvs.cells[pathV[prop]] === cvs.stopField) {
                    continue;
                }
                cvs.cells[pathV[prop]] = cvs.pathField;
            }
            cvs.paint();
            showSteps.enabled = true;
        }
    }

    function onCellVisited(cell) {
        if (showSteps.checked) {
            timer.history.push(cell);
            if (!timer.running){
                timer.start()
            }
        }
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
                       ctx.fillStyle = cells[i].color;
                       ctx.fillRect(x , y , cellXSize , cellYSize );
                   }
                   ctx.fill();
               }

               function paint() {
                   paintCells();
                   paintGrid();
                   requestPaint();
               }

               function clearFields()
               {
                   startFieldId = undefined;
                   stopFieldId = undefined;
                   cells = Array.from({length: gridHeight * gridWidth}, (_) => emptyFiled);
               }

               function clearPreviousPath()
               {
                   for (var i = 0; i < cells.length; i++) {
                       if (cells[i] === cvs.visitedField || cells[i] === cvs.pathField) {
                           cells[i] = cvs.emptyFiled;
                       }
                   }
                   paint();
               }

               function clear()
               {
                   var ctx = getContext("2d");
                   ctx.reset();
               }

               MouseArea {
                   id: ma
                   anchors.fill: parent
                   function getCellId(mouseX, mouseY)
                   {
                       let cellXSize = width / cvs.gridWidth;
                       let cellYSize = height / cvs.gridHeight;
                       var X = Math.floor(mouseX/cellXSize);
                       var Y = Math.floor(mouseY/cellYSize);
                       var id = Math.floor(mouseY/cellYSize) * cvs.gridWidth + Math.floor(mouseX/cellXSize);
                       return id;
                   }
                   function replaceStartOrStopField(id)
                   {
                       if (cvs.select === cvs.startField) {
                           if (cvs.startFieldId) {
                               cvs.cells[cvs.startFieldId] = cvs.emptyFiled;
                           }
                           cvs.startFieldId = id;
                       } else if (cvs.select === cvs.stopField) {
                           if (cvs.stopFieldId) {
                               cvs.cells[cvs.stopFieldId] = cvs.emptyFiled;
                           }
                           cvs.stopFieldId = id;
                       }
                   }

                   onClicked: {
                       var id = getCellId(mouseX, mouseY);
                       replaceStartOrStopField(id);
                       cvs.cells[id] = cvs.select;
                       cvs.paint();
                   }
               }
               //@todo probably can be done better;
               property var isGridPaintedForTheFirstTime: false;
               onAvailableChanged: {
                   if (width && height && available && !isGridPaintedForTheFirstTime) {
                       isGridPaintedForTheFirstTime = true;
                       cvs.paintGrid();
                       cvs.requestPaint();
                   }
               }
               onWidthChanged: {
                   onAvailableChanged();
               }
               onHeightChanged: {
                   onAvailableChanged();
               }

           }
        }

        Timer {
            id: timer
            readonly property int baseInterval: 100
            interval: baseInterval
            running: false
            repeat: true
            property var path: []
            property var history: []
            function isNeitherStartNorEnd(cell) {
                return !(cvs.startFieldId === cell || cvs.stopFieldId === cell)
            }

            onTriggered: {
                if (history.length > 0) {
                    if (isNeitherStartNorEnd(history[0])) {
                        cvs.cells[history[0]] = cvs.visitedField;
                    }
                    history.shift();
                } else if(path.length > 0) {
                    if (isNeitherStartNorEnd(path[0])) {
                        cvs.cells[path[0]] = cvs.pathField;
                    }
                    path.shift();
                }
                else {
                    showSteps.enabled = true;
                    stop();
                }
                cvs.paint();
            }
            function clearTimer() {
                stop()
                path = []
                history = []
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
                Layout.columnSpan: 2
                Layout.rowSpan: 1
                Layout.fillWidth: true
                displayText: ''
                //@todo exception when start path finding for the second time
                function onAvailablePathFindingAlgorithmsSet(algorithms) {
                    var tmp = []
                    for (var alg in algorithms) {
                        tmp.push(algorithms[alg])
                    }
                    model = tmp
                }
                signal pathFindingAlgorithmSelect(variant selected);
                onActivated: {
                    console.log("Selected: ", model[index]);
                    displayText = model[index];
                    pathFindingAlgorithmSelect(model[index]);
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
                    cvs.gridHeight = value;
                    cvs.clear();
                    cvs.clearFields();
                    cvs.paintGrid();
                    cvs.requestPaint();
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
                    cvs.gridWidth = value;
                    cvs.clear();
                    cvs.clearFields();
                    cvs.paintGrid();
                    cvs.requestPaint();
                }
            }

            CheckBox {
                id: showSteps
                Layout.columnSpan: 1
                Layout.fillWidth: true
                text: "Show steps"

            }
            Slider {
                Layout.columnSpan: 1
                Layout.fillWidth: true
                from: 10
                to: 1000
                onMoved: {
                    timer.interval = value;
                }
            }

            function selectStart(){cvs.select = cvs.startField}
            function selectEnd() {cvs.select = cvs.stopField}
            function selectObstacle() {cvs.select = cvs.obstacleField}
            function startPathFinding() {
                var arr = [];
                cvs.clearPreviousPath();
                for (var i = 0; i < cvs.cells.length; i++) {
                        arr.push(cvs.cells[i].value);
                }
                showSteps.enabled = false;
                pathFindingWindow.startPathFinding(arr, cvs.gridWidth);
            }
            function clear() { cvs.clearFields(); cvs.paint()}

            property var btnData: [
                                   {name: "Start", action: selectStart, colspan: 1},
                                   {name: "End", action: selectEnd, colspan: 1},
                                   {name: "Obstacle", action: selectObstacle, colspan: 1},
                                   {name: "Clear", action: clear, colspan: 1},
                                   {name: "Find Path", action: startPathFinding, colspan: 2},
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
