import ".." 1.0
import Qt 4.7

Item {
    property bool on: false
    property color onColor: "red"
    property color offColor: "black"

    signal toggled(bool isOn)
    function toggle() {
        on = !on
    }

    onOnChanged: { toggled(on) }

    width: 40
    height: 40

    Image {
        id: background
        source: "../resources/led_bg.svg"
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
    }

    Ellipse {
        id: light
        color: on ? onColor : offColor
        anchors.fill: parent
        anchors.margins: parent.width * 0.05
        smooth: true

        Behavior on color {
            ColorAnimation {
                duration: 100
            }
        }
    }

    Image {
        id: foreground
        source: "../resources/led_fg.svg"
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
    }
}
