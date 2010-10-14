import ".." 1.0
import Qt 4.7

Rectangle {
    id: root
    width: 200
    height: 200

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
                width: parent.width
                height: parent.height - 40
            }

            Item {
                width:  parent.width
                height:  20

                Label {
                    id: gaugeLabel
                    text: "Value"
                    width: 50
                    height: parent.height
                }

                Field {
                    id: gaugeValue
                    width: 60
                    height: gaugeLabel.height
                    anchors.left: gaugeLabel.right
                    validator: DoubleValidator { bottom: gauge.minimum; top: gauge.maximum }
                    onTextChanged: if (acceptableInput) gauge.value = text
                    text: gauge.value
                }


                SquareButton {
                    id: buttonGauge
                    width: 100
                    height: gaugeLabel.height
                    anchors.left: gaugeValue.right
                    anchors.leftMargin: 4
                    label.text: "Start / Stop"
                    checkable: true
                    onClicked: { gaugeTimer.running = isDown }
                }

                Timer {
                    id: gaugeTimer
                    interval: 1000
                    running: false
                    repeat: true
                    onTriggered: {
                        if (gauge.value == gauge.minimum)
                            gauge.value = gauge.maximum
                        else if (gauge.value == gauge.maximum)
                            gauge.value = gauge.minimum
                    }
                }
            }
        }

        Column {
            spacing: 4
            width:  parent.width * 0.3
            height:  parent.height * 0.5

            Gauge {
                id: gauge2
                width: parent.width
                height: parent.height - 40
            }

            Item {
                width:  parent.width
                height:  20

                Label {
                    id: gaugeLabel2
                    text: "Value"
                    width: 50
                    height: parent.height
                }

                Field {
                    id: gaugeValue2
                    width: 60
                    height: gaugeLabel2.height
                    anchors.left: gaugeLabel2.right
                    validator: DoubleValidator { bottom: gauge2.minimum; top: gauge2.maximum }
                    onTextChanged: if (acceptableInput) gauge2.value = text
                    text: gauge2.value
                }


                SquareButton {
                    id: buttonGauge2
                    width: 100
                    height: gaugeLabel2.height
                    anchors.left: gaugeValue2.right
                    anchors.leftMargin: 4
                    label.text: "Start / Stop"
                    checkable: true
                    onClicked: { gaugeTimer2.running = isDown }
                }

                Timer {
                    id: gaugeTimer2
                    interval: 1000
                    running: false
                    repeat: true
                    onTriggered: {
                        if (gauge2.value == gauge2.minimum)
                            gauge2.value = gauge2.maximum
                        else if (gauge2.value == gauge2.maximum)
                            gauge2.value = gauge2.minimum
                    }
                }
            }
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

            Tank {
                id: tank
                width: parent.width
                height: parent.height - 40
            }

            Item {
                width:  parent.width
                height:  20

                Label {
                    id: tankLabel
                    text: "Value"
                    width: 50
                    height: parent.height
                }

                Field {
                    id: tankValue
                    width: 60
                    height: tankLabel.height
                    anchors.left: tankLabel.right
                    validator: DoubleValidator { bottom: tank.minimum; top: tank.maximum }
                    onTextChanged: if (acceptableInput) tank.value = text
                    text: tank.value
                }


                SquareButton {
                    id: buttonTank
                    width: 100
                    height: tankLabel.height
                    anchors.left: tankValue.right
                    anchors.leftMargin: 4
                    label.text: "Start / Stop"
                    checkable: true
                    onClicked: { tankTimer.running = isDown }
                }

                Timer {
                    id: tankTimer
                    interval: 1000
                    running: false
                    repeat: true
                    onTriggered: {
                        if (tank.value == tank.minimum)
                            tank.value = tank.maximum
                        else if (tank.value == tank.maximum)
                            tank.value = tank.minimum
                    }
                }
            }
        }

        Column {
            spacing: 4
            width:  400
            height:  200

            Tank {
                id: tank2
                width: parent.width
                height: parent.height - 40
                orientation: LinearScale.Horizontal
            }

            Item {
                width:  parent.width
                height:  20

                Label {
                    id: tankLabel2
                    text: "Value"
                    width: 50
                    height: parent.height
                }

                Field {
                    id: tankValue2
                    width: 60
                    height: tankLabel2.height
                    anchors.left: tankLabel2.right
                    validator: DoubleValidator { bottom: tank2.minimum; top: tank2.maximum }
                    onTextChanged: if (acceptableInput) tank2.value = text
                    text: tank2.value
                }


                SquareButton {
                    id: buttonTank2
                    width: 100
                    height: tankLabel2.height
                    anchors.left: tankValue2.right
                    anchors.leftMargin: 4
                    label.text: "Start / Stop"
                    checkable: true
                    onClicked: { tankTimer2.running = isDown }
                }

                Timer {
                    id: tankTimer2
                    interval: 1000
                    running: false
                    repeat: true
                    onTriggered: {
                        if (tank2.value == tank2.minimum)
                            tank2.value = tank2.maximum
                        else if (tank2.value == tank2.maximum)
                            tank2.value = tank2.minimum
                    }
                }
            }
        }
    }
}
