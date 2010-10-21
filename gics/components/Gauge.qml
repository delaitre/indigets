import ".." 1.0
import Qt 4.7

Item {
    id: gauge
    property alias minimum: scale.minimum
    property real middle: minimum + (maximum - minimum) * 0.7
    property alias maximum: scale.maximum
    property alias value: rotator.value

    Image {
        id: background
        source: "../resources/gauge_bg.svg"
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
    }

    LinearValueMapper {
        id: valueMapper
        minimum: gauge.minimum
        maximum: gauge.maximum
    }

    StepTickEngine {
        id: ticks
        step: 10
    }

    CircularScale {
        id: scale
        anchors.fill: parent
        minimum: 0
        maximum: 100
        startAngle: 145
        spanAngle: 250
        mapper: valueMapper
        zones: [
            StandardScaleZone {
                id: zone1
                scale: scale
                parent: scale
                minimum: gauge.minimum
                maximum: gauge.middle
                tickEngine: ticks
                color: "white"
                baselineVisible: true
                ticksVisible: true
                labelsVisible: true
                beginningTickVisible: true
                endingTickVisible: false
                thickness: 2
                tickLength: 3
                flipTicks: true
                smooth: true
            },

            StandardScaleZone {
                id: zone2
                scale: scale
                parent: scale
                minimum: gauge.middle
                maximum: gauge.maximum
                tickEngine: ticks
                color: "red"
                baselineVisible: true
                ticksVisible: true
                labelsVisible: true
                beginningTickVisible: true
                endingTickVisible: true
                thickness: 2
                tickLength: 3
                flipTicks: true
                smooth: true
            }
        ]
    }

    Image {
        id: needle
        source: "../resources/gauge_needle.svg"
        sourceSize.width: width
        sourceSize.height: height
        smooth: true
    }

    Rotator {
        id: rotator
        anchors.left: gauge.left
        anchors.top: gauge.top
        anchors.right: gauge.right
        anchors.bottom: gauge.bottom
        anchors.leftMargin: gauge.width * 0.1
        anchors.topMargin: gauge.height * 0.1
        anchors.rightMargin: gauge.width * 0.1
        anchors.bottomMargin: gauge.height * 0.1
        scale: scale
        pointer: needle
        value: 0
        scaleOriginX: scale.width / 2
        scaleOriginY: scale.height / 2
        pointerOriginX: needle.width * 0.279654
        pointerOriginY: needle.height / 2
        pointerWidth: scale.width / 2
        pointerHeight: scale.height * 0.05

        Behavior on value { NumberAnimation { duration: 400 } }
    }

    Image {
        id: foreground
        source: "../resources/gauge_fg.svg"
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
    }
}
