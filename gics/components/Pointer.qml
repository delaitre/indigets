import ".." 1.0
import Qt 4.7

Item {
    id: pointer
    property AbstractScale scale
    property real value: 0
    x: scale.pointAtValue(value).x
    y: scale.pointAtValue(value).y
    rotation: -(scale.angleAtValue(value) - 90)

    width: 1
    height: 1

    onScaleChanged: {
        if (scale)
            pointer.parent = scale.parent
    }
}
