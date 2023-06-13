import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: applicatin
    title: "Image Compressor"
    width: 600
    height: 400
    visible: true

    Column {
        anchors.fill: parent

        Rectangle {
            id: header
            width: parent.width
            height: 40
            color: "lightblue"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10

                Text {
                    text: "File Name"
                    font.pixelSize: 15
                    Layout.fillWidth: true
                    horizontalAlignment: Text.AlignHCenter
                }

                Text {
                    text: "Extension"
                    font.pixelSize: 15
                    width: 50
                    horizontalAlignment: Text.AlignHCenter
                }

                Text {
                    text: "Size"
                    font.pixelSize: 15
                    width: 100
                    horizontalAlignment: Text.AlignRight
                }
            }
        }

        ListView {
            id: root
            model: myFolderModel
            width: parent.width
            height: parent.height - header.height
            spacing: 10

            delegate: Rectangle {
                id: fileDelegate
                width: root.width
                height: 60
                color: index % 2 === 0 ? "lightgrey" : "white"
                border.color: "black"
                border.width: 1

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text {
                        id: fileName
                        text: model.fileName
                        font.pixelSize: 15
                        Layout.fillWidth: true
                        elide: Text.ElideRight
                    }

                    Text {
                        id: fileExtension
                        text: model.fileExtension
                        font.pixelSize: 15
                        width: 50
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text {
                        id: fileSize
                        text: model.fileSize
                        font.pixelSize: 15
                        width: 100
                        horizontalAlignment: Text.AlignRight
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: fileDelegate.color = "lightblue"
                }
            }
        }
    }
}