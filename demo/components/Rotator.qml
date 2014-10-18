import indigets 1.0
import QtQuick 2.3

Item {
    id: rotator
    property AbstractScale scale
    property real value: 0
    rotation: angleForValue(value)

    width: 1
    height: 1

    onScaleChanged: {
        if (scale)
            rotator.parent = scale.parent
    }

    function angleForValue(v) {
        if (!scale)
            return rotator.rotation;

        var pos = scale.pointAtValue(v);
        pos = scale.mapToItem(rotator.parent, pos.x, pos.y);

        return Indigets.angle(Qt.point(rotator.x, rotator.y), Qt.point(pos.x, pos.y));
    }
}
