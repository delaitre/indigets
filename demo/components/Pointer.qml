import indigets 1.0
import QtQuick 1.0

Item {
    id: pointer
    property AbstractScale scale
    property real value: 0

    width: 1
    height: 1

    onScaleChanged: {
        if (scale)
            pointer.parent = scale.parent
        update();
    }
    onValueChanged: { update(); }

    function update() {
        if (!scale)
            return;

        var percent = scale.percentAtValue(pointer.value);
        var pos = scale.pointAtPercent(percent);
        pos = scale.mapToItem(pointer.parent, pos.x, pos.y);

        pointer.x = pos.x;
        pointer.y = pos.y;
        pointer.rotation = -(scale.angleAtPercent(percent) - 90);
    }
}
