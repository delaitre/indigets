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
                width: parent.width
                height: parent.height - 20
            }

            Marker {
                scale: gauge.scale
                value: gauge.value
            }

            ValueChanger { subject: gauge }
        }

        Column {
            spacing: 4
            width:  parent.width * 0.3
            height:  parent.height * 0.5

            Gauge {
                id: gauge2
                width: parent.width
                height: parent.height - 20
            }

            Marker {
                scale: gauge2.scale
                value: gauge2.value
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

            Tank {
                id: tank
                width: parent.width
                height: 40
                orientation: LinearScale.Horizontal
                minimum: -40
                maximum: 40
                from: -20
            }

            Marker {
                scale: tank.scale
                value: tank.to
            }

            ValueChanger {
                subject: QtObject {
                    property alias value: tank.to
                    property alias minimum: tank.minimum
                    property alias maximum: tank.maximum
                }
            }
        }

        Column {
            spacing: 4
            height:  200

            Tank {
                id: tank2
                width: 40
                height: parent.height - 20
                orientation: LinearScale.Vertical
                minimum: -40
                maximum: 40
                from: -20
            }

            Marker {
                scale: tank2.scale
                value: tank2.to
            }

            ValueChanger {
                subject: QtObject {
                    property alias value: tank2.to
                    property alias minimum: tank2.minimum
                    property alias maximum: tank2.maximum
                }
            }
        }
    }
}
