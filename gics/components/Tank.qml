import ".." 1.0
import Qt 4.7

Item {
    id: tank
    property real minimum: 0
    property real maximum: 100
    property real value: 0
    property real tickStep: 5
    property real thickness: 2
    property alias orientation: scale1.orientation

    width: 80
    height: 200

    Rectangle {
        anchors.fill: parent
        color: "blue"
    }

    StepScaleEngine {
        id: majorEngine
        minimum: tank.minimum
        maximum: tank.maximum
        step: tank.tickStep
    }

    Rectangle {
        anchors.fill: scale1
        color: "lightBlue"
    }

    LinearScale {
        id: scale1
        width: (orientation == LinearScale.Horizontal) ? parent.width : minimumWidth
        height: (orientation == LinearScale.Horizontal) ? minimumHeight : parent.height
        minimum: tank.minimum
        maximum: tank.maximum
        engine: majorEngine
        color: "white"
        beginningTickVisible: true
        endingTickVisible: true
        thickness: tank.thickness
        baselineVisible: true
        ticksVisible: true
        labelsVisible: true
        flipTicks: false
    }

    Rectangle {
        id: fill

        x: (orientation == LinearScale.Horizontal) ? scale1.pointAtValue(0).x : scale1.width
        y: (orientation == LinearScale.Horizontal) ? scale1.height : scale1.pointAtValue(tank.value).y
        width: (orientation == LinearScale.Horizontal) ? scale1.pointAtValue(tank.value).x - x : parent.width - x
        height: (orientation == LinearScale.Horizontal) ? parent.height - y : scale1.pointAtValue(0).y - y

        color: "green"
    }
}
