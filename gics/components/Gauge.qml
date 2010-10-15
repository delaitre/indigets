import ".." 1.0
import Qt 4.7

Item {
    id: gauge
    property real minimum: 0
    property real middle: 60
    property real maximum: 100
    property real value: 0
    property real startAngle: 145
    property real spanAngle: 250
    property real baselineRadius: 150
    property real tickStep: 5
    property real thickness: 4
    property bool animated: true

    width: rotator.width + 40
    height: rotator.height + 40

    Image {
        id: background
        source: "../resources/gauge_bg.svg"
        anchors.fill: parent
        sourceSize.width: width
        sourceSize.height: height
    }

    StepScaleEngine {
        id: majorEngine
        minimum: gauge.minimum
        maximum: gauge.maximum
        step: gauge.tickStep
    }

    StepScaleEngine {
        id: minorEngine2
        minimum: gauge.minimum
        maximum: gauge.maximum
        step: gauge.tickStep * 0.5
    }

    FixedScaleEngine {
        id: minorEngine
        minimum: gauge.minimum
        maximum: gauge.maximum
        data: [[87.5, "warning"], [92.5, "danger"], [97.5, "beware"]]
    }

    CircularScale {
        id: scale1
        anchors.centerIn: gauge
        baselineRect: Qt.rect(0, 0, baselineRadius, baselineRadius)
        minimum: gauge.minimum
        maximum: gauge.middle
        startAngle: gauge.startAngle
        spanAngle: gauge.spanAngle * (gauge.middle - gauge.minimum) / (gauge.maximum - gauge.minimum)
        engine: majorEngine
        color: "white"
        beginningTickVisible: true
        endingTickVisible: false
        thickness: gauge.thickness
        flipTicks: false
        smooth: true
    }

    CircularScale {
        id: scale2
        anchors.centerIn: gauge
        baselineRect: Qt.rect(0, 0, baselineRadius, baselineRadius)
        minimum: gauge.middle
        maximum: gauge.maximum
        startAngle: scale1.startAngle + scale1.spanAngle
        spanAngle: gauge.spanAngle - scale1.spanAngle
        engine: majorEngine
        color: "red"
        beginningTickVisible: true
        endingTickVisible: true
        thickness: gauge.thickness
        flipTicks: false
        smooth: true
    }

    CircularScale {
        id: scale3
        anchors.centerIn: gauge
        baselineRect: Qt.rect(0, 0, baselineRadius, baselineRadius)
        minimum: scale2.minimum
        maximum: scale2.maximum
        startAngle: scale2.startAngle
        spanAngle: scale2.spanAngle
        engine: minorEngine
        color: "orange"
        beginningTickVisible: false
        endingTickVisible: false
        thickness: gauge.thickness * 0.5
        baselineVisible: true
        labelsVisible: true
        flipTicks: true
        smooth: true
    }

    Image {
        id: needle
        source: "../resources/gauge_needle.svg"
        width: baselineRadius * 0.5
        height: baselineRadius * 0.07
        sourceSize.width: width
        sourceSize.height: height
        smooth: true
    }

    Rotator {
        id: rotator
        scale: scale1
        pointer: needle
        value: gauge.value
        pointerOriginX: needle.width * 0.279654
        pointerOriginY: needle.height * 0.5
        scaleOriginX: gauge.width * 0.5
        scaleOriginY: gauge.height * 0.5
        pointerWidth: needle.width
        pointerHeight: needle.height

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
