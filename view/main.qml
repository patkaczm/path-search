import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

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
            SpinBox {
                id: spinBox
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                objectName: "gridSize"
                editable: true
                value: 25
                Layout.topMargin: 20
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

        GridLayout {
            id: gridLayout
            width: parent.height
            height: parent.height
            columns: 5
            columnSpacing: 0
            rowSpacing: 0
        }

        property var gridCells: [];

        function cellClicked(cellId)
        {
            console.log("Clicked: ", cellId)
            for (var i = 0; i < gridCells.length; i++) {
                if (gridCells[i].cellId === cellId) {
                    gridCells[i].color = "blue";
                    console.log("height: ", gridCells[i].height, " width: ", gridCells[i].width)
                }
            }
        }

        function createItem() {
            var component = Qt.createComponent("gridCell.qml")
            for (var i = 0; i < spinBox.value; i++) {

                var object = component.createObject(gridLayout,
                                                    {"cellId": i,
                                                     "width": gridLayout.width / gridLayout.columns,
                                                     "height": gridLayout.height / gridLayout.columns,
                                                     "color": "red",
                                                     "border.color": "black",
                                                     "border.width": 1})
                console.log("height: ", gridLayout.height / gridLayout.columns," width: ", gridLayout.width / gridLayout.columns)
                object.clicked.connect(cellClicked)
                gridCells.push(object)
            }

        }

        //should be deleted on visibility changed to invisible
        onVisibleChanged: gridView.createItem();
    }

}
