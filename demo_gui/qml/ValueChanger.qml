import demo 1.0
import QtQuick 2.2

Item {
    property QtObject subject
    height:  20
    width: childrenRect.width

    Label {
        id: label
        text: "Value"
        width: 50
        height: parent.height
    }

    Field {
        id: field
        width: 60
        height: label.height
        anchors.left: label.right
        validator: DoubleValidator { bottom: subject.minimum; top: subject.maximum }
        text: subject.value
        readOnly: button.checked

        Keys.onReturnPressed: { if (acceptableInput) subject.value = text }
    }

    SquareButton {
        id: button
        width: 100
        height: label.height
        anchors.left: field.right
        anchors.leftMargin: 4
        label.text: "Start / Stop"
        checkable: true
        onClicked: {
            timer.running = isDown
            if (isDown)
                subject.value = subject.minimum
        }
    }

    Timer {
        id: timer
        interval: 1000
        running: false
        repeat: true
        onTriggered: {
            if (subject.value == subject.minimum)
                subject.value = subject.maximum
            else if (subject.value == subject.maximum)
                subject.value = subject.minimum
        }
    }
}
