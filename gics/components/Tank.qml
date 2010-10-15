import ".." 1.0
import Qt 4.7

Item {
    id: tank
    property LinearScale scale
    property Item fillElement
    property real from: 0
    property real to: 0
    property real spacing: 2

    width: 80
    height: 200

    Item {
        id: fillWrapper
        z: 2
        property real xScale: 1;
        property real yScale: 1;
        transform: Scale {
            origin.x: fillWrapper.width * 0.5
            origin.y: fillWrapper.height * 0.5
            xScale: fillWrapper.xScale
            yScale: fillWrapper.yScale
        }
    }

    onWidthChanged: { updateScaleWidth() }

    function updateScaleWidth() {
        if (!scale)
            return;
        scale.width = (scale.orientation == LinearScale.Horizontal) ? tank.width : scale.minimumWidth;
    }

    onHeightChanged:  { updateScaleHeight() }

    function updateScaleHeight() {
        if (!scale)
            return;
        scale.height = (scale.orientation == LinearScale.Horizontal) ? scale.minimumHeight : tank.height;
    }

    onScaleChanged: {
        scale.parent = tank;
        scale.z = 1
        scale.x = 0;
        scale.y = 0;
        updateScaleWidth();
        updateScaleHeight();
        update();
    }

    onFillElementChanged: {
        fillElement.parent = fillWrapper;
        fillElement.anchors.fill = fillWrapper;
        update()
    }

    onFromChanged: { update() }
    onToChanged: { update() }

    function update() {
        if (!scale || !fillElement)
            return;

        var x, y, w, h;
        if (scale.orientation == LinearScale.Horizontal) {
            x = scale.pointAtValue(tank.from).x;
            y = scale.height + tank.spacing;
            w = scale.pointAtValue(tank.to).x - x;
            h = tank.height - y;
        } else {
            x = scale.width + tank.spacing;
            y = scale.pointAtValue(tank.from).y;
            w = tank.width - x;
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
