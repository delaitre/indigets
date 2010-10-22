import ".." 1.0
import Qt 4.7

Item {
    id: gauge
    property alias minimum: scale.minimum
    property real middle: minimum + (maximum - minimum) * 0.7
    property alias maximum: scale.maximum
    property alias value: rotator.value
    property alias scale: scale

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
        anchors.left: gauge.left
        anchors.top: gauge.top
        anchors.right: gauge.right
        anchors.bottom: gauge.bottom
        anchors.leftMargin: gauge.width * 0.1
        anchors.topMargin: gauge.height * 0.1
        anchors.rightMargin: gauge.width * 0.1
        anchors.bottomMargin: gauge.height * 0.1
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
                beginningTickVisible: false
                endingTickVisible: true
                thickness: 2
                tickLength: 3
                flipTicks: true
                smooth: true
            },

            StandardScaleZone {
                id: zone3
                scale: scale
                parent: scale
                minimum: gauge.middle
                maximum: gauge.maximum
                tickEngine: StepTickEngine { step: 5 }
                color: "red"
                baselineVisible: false
                ticksVisible: true
                labelsVisible: false
                beginningTickVisible: false
                endingTickVisible: false
                thickness: 2
                tickLength: 2
                flipTicks: true
                smooth: true
            },

            StandardScaleZone {
                id: zone4
                scale: scale
                parent: scale
                minimum: gauge.middle
                maximum: gauge.maximum
                tickEngine: FixedTickEngine { data: [[zone4.minimum, "beware"]] }
                color: "orange"
                baselineVisible: false
                ticksVisible: true
                labelsVisible: true
                beginningTickVisible: true
                endingTickVisible: true
                thickness: 2
                tickLength: 10
                flipTicks: true
                font.bold: true
                smooth: true
            }
        ]
    }

    Rotator {
        id: rotator
        scale: scale
        value: 0
        x: gauge.width / 2
        y: gauge.height / 2


        Behavior on value { NumberAnimation { duration: 400 } }

        Image {
            id: needle
            source: "../resources/gauge_needle.svg"
            x: -width * 0.279654
            y: -height / 2
            width: ((gauge.width < gauge.height) ? gauge.width : gauge.height) * 0.4
            height: width * 0.2
            sourceSize.width: width
            sourceSize.height: height
            smooth: true
        }
    }

    Image {
        id: foreground
        source: "../resources/gauge_fg.svg"
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
        smooth: true
    }
}
