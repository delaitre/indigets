import QtQuick 1.0

TextInput {
    width: 50
    height: 20
    color: "white"
    horizontalAlignment: TextInput.AlignHCenter

    BorderImage {
        z: -1
        source: "../resources/field.svg"
        anchors.fill: parent
        border.left: width * 0.023809523809523836
        border.top: height * 0.05
        border.right: width * 0.023809523809523836
        border.bottom: height * 0.05
    }
}
