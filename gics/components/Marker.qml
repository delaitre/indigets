import "." 1.0
import Qt 4.7

Pointer {
    z: scale.z + 1

    Image {
        source: "marker.svg"
        width: 10
        height: 10
        sourceSize.width: width
        sourceSize.height: height
        smooth: true
        x: -width
        y: -height / 2
    }

    //Behavior on value { NumberAnimation { duration: 400 } }
}
