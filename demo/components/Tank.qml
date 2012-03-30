import indigets 1.0
import QtQuick 1.0

Item {
    id: tank
    property alias minimum: scale.minimum
    property real middle: minimum + (maximum - minimum) * 0.7
    property alias maximum: scale.maximum
    property alias from: scaler.from
    property alias to: scaler.to
    property alias orientation: scale.orientation
    property alias scale: scale

    LinearValueMapper {
        id: valueMapper
        minimum: tank.minimum
        maximum: tank.maximum
    }

    StepTickEngine {
        id: ticks
        step: 10
    }

    LinearScale {
        id: scale
        anchors.fill: tank
        minimum: 0
        maximum: 100
        orientation: LinearScale.Horizontal
        mapper: valueMapper
        zones: [
            StandardScaleZone {
                id: zone1
                scale: scale
                parent: scale
                minimum: tank.minimum
                maximum: tank.middle
                tickEngine: ticks
                color: "white"
                baselineVisible: true
                ticksVisible: true
                labelsVisible: true
                beginningTickVisible: true
                endingTickVisible: false
                thickness: 2
                tickLength: 3
                flipTicks: false
                smooth: true
            },

            StandardScaleZone {
                id: zone2
                scale: scale
                parent: scale
                minimum: tank.middle
                maximum: tank.maximum
                tickEngine: ticks
                color: "red"
                baselineVisible: true
                ticksVisible: true
                labelsVisible: true
                beginningTickVisible: true
                endingTickVisible: true
                thickness: 2
                tickLength: 3
                flipTicks: false
                smooth: true
            }
        ]
    }

    Scaler {
        id: scaler
        scale: scale
        from: 0
        to: 0
        spacing: 2
        fillWidth: 20

        Behavior on to { NumberAnimation { duration: 400 } }

        Rectangle {
            color: "#abd037"
            anchors.fill: scaler

            Image {
                id: foreground
                anchors.fill: parent
                source: (tank.orientation == LinearScale.Horizontal) ? "../resources/tank_hfg.svg" : "../resources/tank_vfg.svg"
                sourceSize.width: width
                sourceSize.height: height
            }
        }
    }
}
