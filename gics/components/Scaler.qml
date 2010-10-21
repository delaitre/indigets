import ".." 1.0
import Qt 4.7

Item {
    id: tank
    property LinearScale scale
    property Item fillElement
    property real from: 0
    property real to: 0
    property real spacing: 2
    property real fillWidth: 20

    x: childrenRect.x
    y: childrenRect.y
    width: childrenRect.width
    height: childrenRect.height

    Item {
        id: fillWrapper
        z: 2
        property real xScale: 1
        property real yScale: 1
        transform: Scale {
            origin.x: fillWrapper.width * 0.5
            origin.y: fillWrapper.height * 0.5
            xScale: fillWrapper.xScale
            yScale: fillWrapper.yScale
        }
    }

    onFromChanged: { update() }
    onToChanged: { update() }
    onSpacingChanged: { update() }
    onFillWidthChanged: { update() }

    onScaleChanged: {
        scale.parent = tank;
        scale.z = 1;
        scale.x = 0;
        scale.y = 0;
        update();
    }

    onFillElementChanged: {
        fillElement.parent = fillWrapper;
        fillElement.anchors.fill = fillWrapper;
        update()
    }

    function update() {
        if (!scale || !fillElement)
            return;

        var x, y, w, h;
        if (scale.orientation == LinearScale.Horizontal) {
            var pos = scale.pointAtValue(tank.from);
            x = pos.x;
            y = pos.y + tank.spacing;
            w = scale.pointAtValue(tank.to).x - x;
            h = tank.fillWidth;
        } else {
            var pos = scale.pointAtValue(tank.from);
            x = pos.x + tank.spacing;
            y = pos.y;
            w = tank.fillWidth;
            h = scale.pointAtValue(tank.to).y - y;
        }

        if (w < 0) {
            fillWrapper.xScale = -1;
            w = -w;
            x = x - w;
        } else
            fillWrapper.xScale = 1;

        if (h < 0) {
            fillWrapper.yScale = -1;
            h = -h;
            y = y - h;
        } else
            fillWrapper.yScale = 1;

        fillWrapper.x = x;
        fillWrapper.y = y;
        fillWrapper.width = w;
        fillWrapper.height = h;
    }
}
