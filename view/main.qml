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
        property var selectColor: "black"

        signal startPathSearching(variant gridCells, int width);

        function onPathFindingDone(pathV) {
            console.log(pathV)
//            console.log(typeof(pathV))
            for (var prop in pathV) {
                gridCells[pathV[prop]].color = "blue";
            }
        }

        property var gridCells: [];

        RowLayout {
        anchors.fill: parent
        anchors.centerIn: parent
            GridLayout {
                id: gridLayout
                height: parent.height
                width: height
                columnSpacing: 0
                rowSpacing: 0
            }
            ColumnLayout {

                Button {
                    text: "Select start"
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10
                    onClicked: {
                        gridView.selectColor = "green"
                    }
                }
                Button {
                    text: "Select end"
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10
                    onClicked: {
                        gridView.selectColor = "red"
                    }
                }
                Button {
                    text: "Draw obstacle"
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10
                    onClicked: {
                        gridView.selectColor = "black"
                    }
                }
                Button {
                    text: "Start"
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10
                    onClicked: {
                        var easyArray = [];
                        for (var i = 0; i < gridView.gridCells.length; i++) {
                            if (Qt.colorEqual(gridView.gridCells[i].color, "green"))
                            {
                                easyArray.push(1);
                            }
                            else if (Qt.colorEqual(gridView.gridCells[i].color, "red"))
                            {
                                easyArray.push(2);
                            }
                            else if (Qt.colorEqual(gridView.gridCells[i].color, "black"))
                            {
                                easyArray.push(3);
                            } else {
                                easyArray.push(0);
                            }
                        }

                        gridView.startPathSearching(easyArray, gridSizeWidth.value)
                    }
                }
            }
        }

        function removeColorFromGridIfNeeded() {
            if (gridView.selectColor === "green" || gridView.selectColor === "red") {
                for (var i = 0; i < gridCells.length; i++) {
                    if (Qt.colorEqual(gridCells[i].color, gridView.selectColor)) {
                        gridCells[i].color = "white";
                    }
                }
            }
        }

        function drawField(cellId)
        {
           removeColorFromGridIfNeeded()
            for (var i = 0; i < gridCells.length; i++) {
                if (gridCells[i].cellId === cellId) {
                    gridCells[i].color = gridView.selectColor;
                }
            }
        }

        function cellClicked(cellId)
        {
            console.log("Clicked: ", cellId)
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
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
