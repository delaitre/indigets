import Qt 4.7

TextInput {
    width: 50
    height: 20
    color: "white"
    horizontalAlignment: TextInput.AlignHCenter

    BorderImage {
        z: -1
        source: "field.svg"
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
        border.left: width * 0.023809523809523836
        border.top: height * 0.05
        border.right: width * 0.023809523809523836
        border.bottom: height * 0.05
    }
}
