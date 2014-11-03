import indigets 1.0
import QtQuick 2.2

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
        source: "../resources/circular_button_up.svg"
        visible: !press.visible && !checked
    }

    Image {
        id: down
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
        source: "../resources/circular_button_down.svg"
        visible: !press.visible && checked
    }

    Image {
        id: press
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
        source: "../resources/circular_button_down.svg"
        visible: mouseArea.pressed
    }

    Text {
        id: text
        anchors.centerIn: parent
        color: "white"
        scale: (mouseArea.pressed || checked) ? 0.95 : 1.0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Ellipse {
        id: highlight
        anchors.fill: parent
        color:  "#00000000"
        borderColor: "#ffabd037"
        borderWidth: 2
        visible: mouseArea.containsMouse
        smooth: true
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: { if (checkable) checked = !checked; button.clicked(checked) }
    }
}
