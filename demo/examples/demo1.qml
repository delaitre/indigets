import indigets 1.0
import demo 1.0
import Qt 4.7

Rectangle {
    id: root
    width: 800
    height: 600

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#ff525252" }
        GradientStop { position: 1.0; color: "#ff181818" }
    }

    Item {
        id: mainPanel
        width: childrenRect.width
        height: childrenRect.height
        anchors.centerIn: root

        Item {
            id: mainGaugeWrapper
            width: childrenRect.width
            height: childrenRect.height

            Gauge {
                id: mainGauge
                width: 200
                height: 200

                Marker {
                    scale: parent.scale
                    value: parent.value
                }
            }

            ValueChanger {
                subject: mainGauge
                anchors.top: subject.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: subject.horizontalCenter
            }
        }

        Item {
            id: mainHTankWrapper
            anchors.bottom: mainGaugeWrapper.top
            anchors.bottomMargin: 20
            anchors.left: mainGaugeWrapper.left
            anchors.right: mainGaugeWrapper.right

            Tank {
                id: mainHTank
                height: 40
                orientation: LinearScale.Horizontal
                minimum: -40
                maximum: 40
                from: -20
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: mainHTankValue.top

                Marker {
                    scale: parent.scale
                    value: parent.to
                }
            }

            ValueChanger {
                id: mainHTankValue
                subject: QtObject {
                    property alias value: mainHTank.to
                    property alias minimum: mainHTank.minimum
                    property alias maximum: mainHTank.maximum
                }
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: mainHTank.horizontalCenter
            }
        }


        Item {
            id: mainVTankWrapper
            anchors.right: mainGaugeWrapper.left
            anchors.rightMargin: 20
            anchors.top: mainGaugeWrapper.top
            anchors.bottom: mainGaugeWrapper.bottom

            Tank {
                id: mainVTank
                width: 40
                orientation: LinearScale.Vertical
                minimum: 0
                maximum: 120
                from: 0
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right

                Marker {
                    scale: parent.scale
                    value: parent.to
                }
            }

            ValueChanger {
                id: mainVTankValue
                subject: QtObject {
                    property alias value: mainVTank.to
                    property alias minimum: mainVTank.minimum
                    property alias maximum: mainVTank.maximum
                }
                anchors.top: mainVTank.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: mainVTank.horizontalCenter
            }
        }


        Item {
            id: mainLeds
            anchors.left: mainGaugeWrapper.right
            anchors.leftMargin: 20
            anchors.top: mainGaugeWrapper.top
            anchors.bottom: mainGaugeWrapper.bottom

            Column {
                spacing: 6
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                Led {
                    id: mainLed1
                    onColor: "green"
                    offColor: "black"
                    width: height
                    on: mainGauge.value < mainGauge.middle
                }

                Led {
                    id: mainLed2
                    onColor: "orange"
                    offColor: "black"
                    width: height
                    on: mainGauge.value >= mainGauge.middle && mainGauge.value < mainGauge.middle + (mainGauge.maximum - mainGauge.middle) * 0.5
                }

                Led {
                    id: mainLed3
                    onColor: "red"
                    offColor: "black"
                    width: height
                    on: mainGauge.value >= mainGauge.middle + (mainGauge.maximum - mainGauge.middle) * 0.5
                }
            }
        }
    }

    Item {
        id: panel
        width: childrenRect.width
        height: childrenRect.height
        anchors.top: mainPanel.bottom
        anchors.topMargin: 80
        anchors.left: mainPanel.left

        Item {
            id: subGauge
            width: childrenRect.width
            height: childrenRect.height
            anchors.top: panel.top
            anchors.left: panel.left

            CircularScale {
                id: subGaugeScale
                anchors.top: parent.top
                anchors.left: parent.left
                width: 80
                height: width
                minimum: -3000
                maximum: 2000
                startAngle: 200
                spanAngle: 140
                mapper: LinearValueMapper { minimum: subGaugeScale.minimum; maximum: subGaugeScale.maximum }
                zones: [
                    StandardScaleZone {
                        scale: subGaugeScale
                        parent: subGaugeScale
                        minimum: subGaugeScale.minimum
                        maximum: subGaugeScale.maximum
                        tickEngine: StepTickEngine { step: 1000 }
                        color: "white"
                        baselineVisible: true
                        ticksVisible: true
                        labelsVisible: true
                        beginningTickVisible: true
                        endingTickVisible: true
                        thickness: 3
                        tickLength: 3
                        flipTicks: false
                        smooth: true
                    }
                ]
            }

            Rotator {
                id: subGaugeRotator
                scale: subGaugeScale
                value: 0
                x: subGaugeScale.width / 3
                y: subGaugeScale.width * 0.7

                Rectangle { width: 60; height: 2; color: "green"; smooth: true }
                Behavior on value { NumberAnimation { duration: 400 } }
            }


            ValueChanger {
                subject: QtObject {
                    property alias value: subGaugeRotator.value
                    property alias minimum: subGaugeScale.minimum
                    property alias maximum: subGaugeScale.maximum
                }
                anchors.top: subGaugeScale.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: subGaugeScale.horizontalCenter
            }
        }


        Item {
            id: subGauge2
            width: childrenRect.width
            height: childrenRect.height
            anchors.top: panel.top
            anchors.left: subGauge.right
            anchors.leftMargin: 30

            LinearScale {
                id: subGaugeScale2
                anchors.top: parent.top
                anchors.left: parent.left
                width: 200
                height: 20
                minimum: 0
                maximum: 4
                orientation: LinearScale.Horizontal
                mapper: LinearValueMapper { minimum: subGaugeScale2.minimum; maximum: subGaugeScale2.maximum }
                zones: [
                    StandardScaleZone {
                        scale: subGaugeScale2
                        parent: subGaugeScale2
                        minimum: subGaugeScale2.minimum
                        maximum: subGaugeScale2.maximum
                        tickEngine: StepTickEngine { step: 0.5 }
                        color: "white"
                        baselineVisible: true
                        ticksVisible: true
                        labelsVisible: false
                        beginningTickVisible: true
                        endingTickVisible: true
                        thickness: 2
                        tickLength: 3
                        flipTicks: true
                        smooth: true
                    },
                    StandardScaleZone {
                        scale: subGaugeScale2
                        parent: subGaugeScale2
                        minimum: subGaugeScale2.minimum
                        maximum: subGaugeScale2.maximum
                        tickEngine: FixedTickEngine { data: [[0, "good"], [2, "beware"], [4, "not good"]] }
                        color: "green"
                        baselineVisible: false
                        ticksVisible: true
                        labelsVisible: true
                        beginningTickVisible: true
                        endingTickVisible: true
                        thickness: 3
                        tickLength: 5
                        flipTicks: false
                        smooth: true
                    }
                ]
            }

            Rotator {
                id: subGaugeRotator2
                scale: subGaugeScale2
                value: 0
                x: subGaugeScale2.width / 2
                y: subGaugeScale2.height

                Rectangle { width: 60; height: 2; color: "green"; smooth: true }
                Behavior on value { NumberAnimation { duration: 400 } }
            }


            ValueChanger {
                subject: QtObject {
                    property alias value: subGaugeRotator2.value
                    property alias minimum: subGaugeScale2.minimum
                    property alias maximum: subGaugeScale2.maximum
                }
                anchors.top: subGaugeScale2.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: subGaugeScale2.horizontalCenter
            }
        }


        Led {
            id: funkyLed
            width: 50
            height: 50
            anchors.top: panel.top
            anchors.left: subGauge2.right
            anchors.leftMargin: 30
            onColor: "orange"
            offColor: "black"
            on: false

            Timer {
                id: timer
                interval: 120
                running: funkyLed.on
                repeat: true
                onTriggered: {
                    funkyLed.onColor = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
                }
            }
        }

        CircularButton {
            id: circButton
            width: 50
            height: 50
            anchors.top: panel.top
            anchors.left: funkyLed.right
            anchors.leftMargin: 30
            label.text: "Go\nFunky"
            label.font.pointSize: 8
            checkable: true

            onClicked: funkyLed.on = isDown
        }
    }
}
