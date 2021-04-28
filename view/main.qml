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

        GridLayout {
            id: gridLayout
            width: parent.height
            height: parent.height
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
                }
            }
        }

        function createGrid() {
            var component = Qt.createComponent("gridCell.qml")

            gridLayout.columns = gridSizeWidth.value

            for (var i = 0; i < gridSizeWidth.value * gridSizeHeight.value; i++) {

                var object = component.createObject(gridLayout,
                                                    {"cellId": i,
                                                        "width": gridLayout.width / gridLayout.columns,
                                                        "height": gridLayout.height / gridLayout.columns,
                                                        "color": "red",
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
