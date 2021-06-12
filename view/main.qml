import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import QtQml 2.15

Window {
    width: 640
    minimumWidth: width
    maximumWidth: width
    height: 480
    minimumHeight: height
    maximumHeight: height
    visible: true
    title: qsTr("Path Search")
    objectName: "mainWindow"

    Item {
        id: selectGridSizeView
        objectName: "selectGridSizeView"
        width: parent.width
        height: parent.height
        visible: true

        ColumnLayout {
            id: columnLayout
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter


            Text {
                id: text1
                text: qsTr("Select grid size")
                font.pixelSize: 25
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                minimumPixelSize: 12
            }
            RowLayout {
                id: rowLayout
                width: 100
                height: 100

                ColumnLayout {
                    id: columnLayout1
                    width: 100
                    height: 100


                    Text {
                        id: text2
                        text: qsTr("Select grid width")
                        font.pixelSize: 12
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                    SpinBox {
                        id: gridSizeWidth
                        Layout.topMargin: 20
                        objectName: "gridSizeWidth"
                        editable: true
                        value: 3
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        to: 51
                        from: 1
                    }
                }

                ColumnLayout {
                    id: columnLayout2
                    width: 100
                    height: 100

                    Text {
                        id: text3
                        text: qsTr("Select grid height")
                        font.pixelSize: 12
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }

                    SpinBox {
                        id: gridSizeHeight
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        objectName: "gridSize"
                        editable: true
                        value: 3
                        from: 1
                        to: 51
                        Layout.topMargin: 20
                    }
                }

            }

            Button {
                id: button
                text: qsTr("Start")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: {
                    selectGridSizeView.visible = false
                    gridView.visible = true
                }
                Layout.topMargin: 20
            }

        }
    }
    Item {
        id: gridView
        objectName: "gridView"
        anchors.fill: parent
        anchors.centerIn: parent
        visible: false

        readonly property var emptyFiled: ({ color: "white", value: 0});
        readonly property var startField: ({ color: "green", value: 1});
        readonly property var stopField: ({ color: "red", value: 2});
        readonly property var obstacleField: ({ color: "black", value: 3});
        readonly property var visitedField: ({ color: "yellow", value: 4});
        readonly property var pathField: ({ color: "blue", value: 5});

        property var selectColor: obstacleField.color
        property var gridCells: [];

        signal startPathSearching(variant gridCells, int width);
        signal generateMaze(int width, int height);

        Timer {
            id: timer
            readonly property int baseInterval: 100
            interval: baseInterval
            running: false
            repeat: true
            property var path: []
            property var history: []
            function isNeitherStartNorEnd(cell) {
                return !Qt.colorEqual(parent.gridCells[cell].color, parent.stopField.color) &&
                        !Qt.colorEqual(parent.gridCells[cell].color, parent.startField.color)
            }

            onTriggered: {
                if (history.length > 0) {
                    if (isNeitherStartNorEnd(history[0].id)) {
                        parent.gridCells[history[0].id].color = history[0].color;
                    }
                    history.shift();
                } else if(path.length > 0) {
                    if (isNeitherStartNorEnd(path[0])) {
                        parent.gridCells[path[0]].color = parent.pathField.color;
                    }
                    path.shift();
                }
                else {
                    stop();
                }
            }
            function clearTimer() {
                stop()
                path = []
                history = []
            }

        }

        function onPathFindingDone(pathV) {
            for (var prop in pathV) {
                timer.path.push(pathV[prop]);
            }
        }

        function onVertexVisited(vertex) {
            timer.history.push({id: vertex, color: gridView.visitedField.color});
            timer.start()
        }

        function onMazeCellGenerated(cell) {
            timer.history.push({id: cell, color: gridView.emptyFiled.color});
            timer.start()
        }

        function isSet(value, bitPos) {
           var result =   Math.floor(value / Math.pow(2, bitPos)) % 2;
           return result === 1;
        }

        function onMazeGenerationDone(maze) {
            cvs1.drawMaze(maze);
            cvs1.requestPaint();
        }


        RowLayout {
        anchors.fill: parent

        Canvas {
            id : cvs1
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredWidth: parent.width / 5 * 3;
            Layout.preferredHeight: parent.width / 5 * 3;
//            Layout.fillHeight: true

            Layout.margins: 5
            function reset() {
                let ctx = getContext("2d")
                ctx.reset()
            }

            function drawMaze(maze) {
                let cellXSize = width / gridSizeWidth.value;
                let cellYSize = height / gridSizeHeight.value;
                console.log(cellXSize, cellYSize);

                let ctx = getContext("2d")
                ctx.reset()

                for (var i = 0 ; i < maze.length; i++) {
                    let x = (i % gridSizeWidth.value) * cellXSize;
                    let y = Math.floor(i / gridSizeWidth.value) * cellYSize;

                    if (!gridView.isSet(maze[i], 0)) {
                        ctx.beginPath();
                        ctx.moveTo(x + cellXSize, y);
                        ctx.lineTo(x + cellXSize, y + cellYSize);
                        ctx.stroke();
                    }
                    if (!gridView.isSet(maze[i], 1)) {
                        ctx.beginPath();
                        ctx.moveTo(x, y + cellYSize);
                        ctx.lineTo(x + cellXSize, y + cellYSize);
                        ctx.stroke();
                    }
                    if (!gridView.isSet(maze[i], 2)) {
                        ctx.beginPath();
                        ctx.moveTo(x, y);
                        ctx.lineTo(x, y + cellYSize);
                        ctx.stroke();
                    }
                    if (!gridView.isSet(maze[i], 3)) {
                        ctx.beginPath();
                        ctx.moveTo(x, y);
                        ctx.lineTo(x + cellXSize, y);
                        ctx.stroke();
                    }
                }
            }

            function p(mx, my) {
                console.log(height, width)

                let cellXSize = width / gridSizeWidth.value;
                let cellYSize = height / gridSizeHeight.value;
                var X = Math.floor(mx/cellXSize);
                var Y = Math.floor(my/cellYSize);
                console.log("X: ", X,
                            " Y: ", Y,
                            " id: ", Math.floor(my/cellYSize) * gridSizeWidth.value + Math.floor(mx/cellXSize));
                let ctx = getContext("2d")
                ctx.beginPath();
                ctx.fillStyle ="yellow";
                ctx.fillRect(X * cellXSize + 1, Y * cellYSize + 1, cellXSize - 2, cellYSize - 2);
                }


            MouseArea {
                anchors.fill: parent
                onClicked: {

                   cvs1.p(mouseX, mouseY)
                   cvs1.requestPaint()
                }
            }
        }
        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            function selectStart(){gridView.selectColor = gridView.startField.color;}
            function selectEnd(){gridView.selectColor = gridView.stopField.color;}
            function drawObstacle(){gridView.selectColor = gridView.obstacleField.color;}
            function start() {
                var easyArray = [];
                for (var i = 0; i < gridView.gridCells.length; i++) {
                    if (Qt.colorEqual(gridView.gridCells[i].color, gridView.startField.color))
                    {
                        easyArray.push(gridView.startField.value);
                    }
                    else if (Qt.colorEqual(gridView.gridCells[i].color, gridView.stopField.color))
                    {
                        easyArray.push(gridView.stopField.value);
                    }
                    else if (Qt.colorEqual(gridView.gridCells[i].color, gridView.obstacleField.color))
                    {
                        easyArray.push(gridView.obstacleField.value);
                    } else {
                        easyArray.push(gridView.emptyFiled.value);
                    }
                }
                gridView.startPathSearching(easyArray, gridSizeWidth.value)
            }
            function reset() {
                timer.clearTimer()
                for (var i = 0; i < gridView.gridCells.length; i++) {
                    gridView.gridCells[i].color = gridView.emptyFiled.color
                }
            }
            function clearVisitedArea() {
                timer.clearTimer()
                for (var i = 0; i < gridView.gridCells.length; i++) {
                    if (Qt.colorEqual(gridView.gridCells[i].color, gridView.visitedField.color)) {
                        gridView.gridCells[i].color = gridView.emptyFiled.color;
                    }
                }
            }
            function generateMaze() {
                gridView.generateMaze(gridSizeWidth.value, gridSizeHeight.value);
            }

            property var btnData: [
                                   {name: "generate maze", action: generateMaze},
                                   {name: "Select start", action: selectStart},
                                   {name: "Select end", action: selectEnd},
                                   {name: "Draw obstacle", action: drawObstacle},
                                   {name: "Start", action: start},
                                   {name: "Reset", action: reset},
                                   {name: "Clear visited area", action: clearVisitedArea}
                                  ]
            ComboBox {
                objectName: "availableAlgorithms"
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.fillWidth: true
                displayText: ''
                function onAvailableAlgorithmsSet(algorithms) {
                    var tmp = []
                    for (var alg in algorithms) {
                        tmp.push(algorithms[alg])
                    }
                    model = tmp
                }
                signal algorithmSelected(variant selected);
                onActivated: {
                    console.log("Selected: ", model[index]);
                    displayText = model[index];
                    algorithmSelected(model[index]);
                }

            }

            Repeater {
                model: parent.btnData
                Button {
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10
                    Layout.fillWidth: true
                    text: modelData.name
                    onClicked: {
                        parent.btnData[index]["action"]()
                    }
                }
            }
            Slider {
                Layout.fillWidth: true
                from: 100
                to: 1
                value: 100
                onMoved: {
                    timer.interval = value
                }
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
