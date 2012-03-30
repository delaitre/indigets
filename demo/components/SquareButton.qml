import QtQuick 1.0

Item {
    id: button

    property bool checkable: false
    property bool checked: false
    property alias label: text
    signal clicked(bool isDown)

    Image {
        id: up
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
        source: "../resources/square_button_up.svg"
        visible: !press.visible && !checked
    }

    Image {
        id: down
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
        source: "../resources/square_button_down.svg"
        visible: !press.visible && checked
    }

    Image {
        id: press
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
        source: "../resources/square_button_down.svg"
        visible: mouseArea.pressed
    }

    Text {
        id: text
        anchors.centerIn: parent
        color: "white"
        scale: (mouseArea.pressed || checked) ? 0.95 : 1.0
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Rectangle {
        id: highlight
        anchors.fill: parent
        color:  "#00000000"
        border.color: "#ffabd037"
        border.width: 2
        visible: mouseArea.containsMouse
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: { if (checkable) checked = !checked; button.clicked(checked) }
    }
}
