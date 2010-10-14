import Qt 4.7

Text {
    width: 50
    height: 20
    color: "white"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    BorderImage {
        z: -1
        source: "../resources/label.svg"
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
        border.left: width * 0.023809523809523836
        border.top: height * 0.05
        border.right: width * 0.023809523809523836
        border.bottom: height * 0.05
    }
}
