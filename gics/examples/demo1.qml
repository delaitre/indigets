import ".." 1.0
import Qt 4.7

Rectangle {
    id: root
    width: 600
    height: 400

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#ff525252" }
        GradientStop { position: 1.0; color: "#ff181818" }
    }

    Flow {
        anchors.fill: parent
        spacing: 40

        Column {
            spacing: 4
            width:  parent.width * 0.3
            height:  parent.height * 0.5

            Gauge {
                id: gauge
                baselineRadius: 150
            }

            ValueChanger { subject: gauge }
        }

        Column {
            spacing: 4
            width:  parent.width * 0.3
            height:  parent.height * 0.5

            Gauge {
                id: gauge2
                baselineRadius: 200
            }

            ValueChanger { subject: gauge2 }
        }

        Column {
            y: 20
            spacing: 20
            width: 30

            Led {
                onColor: "green"
                offColor: "black"

                width: parent.width
                height: width

                on: gauge.value < gauge.middle
            }

            Led {
                onColor: "orange"
                offColor: "black"

                width: parent.width
                height: width

                on: gauge.value >= gauge.middle && gauge.value < gauge.middle + (gauge.maximum - gauge.middle) * 0.5
            }

            Led {
                onColor: "red"
                offColor: "black"

                width: parent.width
                height: width

                on: gauge.value >= gauge.middle + (gauge.maximum - gauge.middle) * 0.5
            }
        }

        Column {
            spacing: 4
            width:  200
            height:  400

            StepScaleEngine {
                id: tankMajorEngine
                minimum: -50
                maximum: 40
                step: 10
            }

            LinearScale {
                id: tankScale
                baselineLength: 280
                minimum: tankMajorEngine.minimum
                maximum: tankMajorEngine.maximum
                engine: tankMajorEngine
                color: "white"
                beginningTickVisible: true
                endingTickVisible: true
                thickness: 2
                baselineVisible: true
                ticksVisible: true
                labelsVisible: true
                flipTicks: false
                orientation: LinearScale.Vertical
            }

            Tank {
                id: tank
                scale: tankScale
                from: -20
                fillWidth: 20
                fillElement: Rectangle {
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "green" }
                        GradientStop { position: 1.0; color: "lightGreen" }
                    }
                }

                Behavior on to { NumberAnimation { duration: 400 } }
            }

            ValueChanger {
                subject: QtObject {
                    property alias value: tank.to
                    property alias minimum: tankScale.minimum
                    property alias maximum: tankScale.maximum
                }
            }
        }

        Column {
            spacing: 4
            width:  400
            height:  200

            StepScaleEngine {
                id: tankMajorEngine2
                minimum: -50
                maximum: 40
                step: 10
            }

            LinearScale {
                id: tankScale2
                baselineLength: 160
                minimum: tankMajorEngine2.minimum
                maximum: tankMajorEngine2.maximum
                engine: tankMajorEngine2
                color: "white"
                beginningTickVisible: true
                endingTickVisible: true
                thickness: 2
                baselineVisible: true
                ticksVisible: true
                labelsVisible: true
                flipTicks: false
                orientation: LinearScale.Horizontal
            }

            Tank {
                id: tank2
                scale: tankScale2
                from: -20
                fillWidth: 40
                fillElement: Rectangle {
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "green" }
                        GradientStop { position: 1.0; color: "lightGreen" }
                    }
                }

                Behavior on to { NumberAnimation { duration: 400 } }
            }

            ValueChanger {
                subject: QtObject {
                    property alias value: tank2.to
                    property alias minimum: tankScale2.minimum
                    property alias maximum: tankScale2.maximum
                }
            }
        }

        Column {
            spacing: 4
            width:  300
            height:  300

            StepScaleEngine {
                id: rotatorEngine
                minimum: -40
                maximum: 60
                step: 10
            }

            CircularScale {
                id: rotatorScale
                baselineRect: Qt.rect(0, 0, 100, 100)
                minimum: rotatorEngine.minimum
                maximum: rotatorEngine.maximum
                startAngle: 145
                spanAngle: 250
                engine: rotatorEngine
                color: "white"
                beginningTickVisible: true
                endingTickVisible: true
                thickness: 3
                flipTicks: false
                smooth: true
            }

            Rectangle { id: needle; color: "green"; width: 50; height: 2 }

            Rotator {
                id: rotator
                scale: rotatorScale
                pointer: needle
                value: 0
                pointerOriginX: 0
                pointerOriginY: needle.height * 0.5
                scaleOriginX: rotatorScale.width * 0.5
                scaleOriginY: rotatorScale.height * 0.5
                pointerWidth: needle.width
                pointerHeight: needle.height

                Behavior on value { NumberAnimation { duration: 400 } }
            }

            ValueChanger {
                subject: QtObject {
                    property alias value: rotator.value
                    property alias minimum: rotatorScale.minimum
                    property alias maximum: rotatorScale.maximum
                }
            }
        }
    }
}
