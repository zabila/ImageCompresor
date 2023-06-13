import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: applicatin
    title: "Image Compressor"
    width: 600
    height: 400
    visible: true

    ListView {
        width: parent.width
        height: parent.height
        model: myFolderModel
        delegate: Item {
            width: parent.width
            height: 30

            Text {
                anchors.left: parent.left
                text: fileName
            }

            Text {
                anchors.right: parent.right
                text: fileExtension + " | " +  fileSize
            }
        }
    }
}