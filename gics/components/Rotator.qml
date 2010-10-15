import ".." 1.0
import Qt 4.7

Item {
    id: rotator
    property CircularScale scale
    property Item pointer
    property real value: 0
    property real scaleOriginX: 0
    property real scaleOriginY: 0
    property real pointerOriginX: 0
    property real pointerOriginY: 0
    property alias pointerWidth: pointerWrapper.width
    property alias pointerHeight: pointerWrapper.height

    x: childrenRect.x
    y: childrenRect.y
    width: childrenRect.width
    height: childrenRect.height

    Item {
        id: pointerWrapper
        z: 2
        property real angle: 0
        transform: [
            Translate {
                x: -rotator.pointerOriginX
                y: -rotator.pointerOriginY
            },
            Rotation {
                angle: pointerWrapper.angle
            },
            Translate {
                x: rotator.scaleOriginX
                y: rotator.scaleOriginY
            }
        ]
        smooth: true
    }

    onValueChanged: { update(); }

    onScaleChanged:  {
        scale.parent = rotator;
        scale.z = 1;
        scale.x = 0;
        scale.y = 0;
        update();
    }

    onPointerChanged: {
        pointer.parent = pointerWrapper;
        pointer.anchors.fill = pointerWrapper;
        update();
    }

    function update() {
        pointerWrapper.angle = angleForValue(rotator.value);
    }

    function angleForValue(v) {
        if (!scale || !pointer)
            return 0.;

        var pos = scale.pointAtValue(v);

        return Gics.angle(Qt.point(scaleOriginX, scaleOriginY), pos);
    }
}
