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
                        value: 10
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        to: 20
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
                        value: 10
                        from: 1
                        to: 10
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
        width: parent.width
        height: parent.height
        visible: false

        readonly property var emptyFiled: ({ color: "white", value: 0});
        readonly property var startField: ({ color: "green", value: 1});
        readonly property var stopField: ({ color: "red", value: 2});
        readonly property var obstacleField: ({ color: "black", value: 3});
        readonly property var visitedField: ({ color: "yellow", value: 4});
        readonly property var pathField: ({ color: "blue", value: 5})

        property var selectColor: obstacleField.color
        property var gridCells: [];

        signal startPathSearching(variant gridCells, int width);

        Timer {
            id: timer
            readonly property int baseInterval: 50
            interval: baseInterval
            running: false
            repeat: true
            property var path: []
            property var history: []
            onTriggered: {
                if (history.length > 0) {
                    if (!Qt.colorEqual(parent.gridCells[history[0]].color, parent.stopField.color) &&
                            !Qt.colorEqual(parent.gridCells[history[0]].color, parent.startField.color)) {
                        parent.gridCells[history[0]].color = parent.visitedField.color;
                    }
                    history.shift();
                } else {
                    if (path.length > 0) {
                        interval = baseInterval / 5;
                        if (!Qt.colorEqual(parent.gridCells[path[0]].color, parent.stopField.color) &&
                                !Qt.colorEqual(parent.gridCells[path[0]].color, parent.startField.color)) {
                        parent.gridCells[path[0]].color = parent.pathField.color;
                        }
                        path.shift();
                    }
                    else {
                        stop();
                    }
                }
            }
            function clearTimer() {
                stop()
                interval = 50
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
            timer.history.push(vertex);
            timer.start()
        }

        function removeAnotherStartOrStopField() {
            for (var i = 0; i < gridCells.length; i++) {
                if (Qt.colorEqual(gridCells[i].color, gridView.selectColor)) {
                    gridCells[i].color = emptyFiled.color;
                }
            }
        }

        function drawField(cellId)
        {
            for (var i = 0; i < gridCells.length; i++) {
                if (gridCells[i].cellId === cellId) {
                    gridCells[i].color = gridView.selectColor;
                    break;
                }
            }
        }

        function cellClicked(cellId)
        {
            if (gridView.selectColor === startField.color || gridView.selectColor === stopField.color)
            {
                removeAnotherStartOrStopField()
            }
            drawField(cellId)
        }

        function createGrid() {
            var component = Qt.createComponent("gridCell.qml")

            gridLayout.columns = gridSizeWidth.value
            gridLayout.rows = gridSizeHeight.value

            for (var i = 0; i < gridSizeWidth.value * gridSizeHeight.value; i++) {

                var object = component.createObject(gridLayout,
                                                    {"cellId": i,
                                                        "width": gridLayout.width / gridLayout.columns,
                                                        "height": gridLayout.height / gridLayout.columns,
                                                        "color": "white",
                                                        "border.color": "black",
                                                        "border.width": 1})
                object.clicked.connect(cellClicked)
                gridCells.push(object)
            }

        }

        //should be deleted on visibility changed to invisible
        onVisibleChanged: {
            gridView.createGrid();
        }

        RowLayout {
        anchors.fill: parent
        anchors.centerIn: parent

            GridLayout {
                id: gridLayout
                height: parent.height
                width: height
                columnSpacing: -2
                rowSpacing: -1
                Layout.leftMargin: 5
                Layout.bottomMargin: 5
                Layout.topMargin: 5
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ColumnLayout {
                id: colLayout
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
                property var btnData: [{name: "Select start", action: selectStart},
                                       {name: "Select end", action: selectEnd},
                                       {name: "Draw obstacle", action: drawObstacle},
                                       {name: "Start", action: start},
                                       {name: "Reset", action: reset},
                                       {name: "Clear visited area", action: clearVisitedArea}]
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
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
