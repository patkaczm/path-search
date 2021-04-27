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

        property var gridCells: [
        ];

        function createItem() {
            for (var i = 0; i < spinBox.value; i++) {
                var object = Qt.createQmlObject("import QtQuick 2.5; Rectangle {}", gridLayout, "dynamicItem");
                gridCells.push(object)

                object.width = gridLayout.width / gridLayout.columns;
                object.height = gridLayout.height / gridLayout.columns;
                object.color = "yellow"
                object.border.color = "black"
                object.border.width = 1
                var mouseArea = Qt.createQmlObject("import QtQuick 2.5; MouseArea {
            }", object, 'mousearea');

                mouseArea.anchors.fill = object

                mouseArea.onClicked.connect(function() {console.log("how to access to mouse area from here")})

                console.log(gridCells.length, object, mouseArea.parent)
            }

        }

        onVisibleChanged: gridView.createItem();


    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;invisible:true}
}
##^##*/
