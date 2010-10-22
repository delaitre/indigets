import ".." 1.0
import Qt 4.7

Item {
    id: scaler
    property LinearScale scale
    property real from: 0
    property real to: 0
    property real spacing: 2
    property real fillWidth: 20

    transform: Scale {
        id: transform
        origin.x: width * 0.5
        origin.y: height * 0.5
        xScale: 1
        yScale: 1
    }

    onScaleChanged: {
        if (scale)
            scaler.parent = scale.parent;
        update();
    }

    onFromChanged: { update(); }
    onToChanged: { update(); }
    onSpacingChanged: { update(); }
    onFillWidthChanged: { update(); }

    function update() {
        if (!scale)
            return;

        var x, y, w, h;
        if (scale.orientation == LinearScale.Horizontal) {
            var pos = scale.pointAtValue(scaler.from);
            x = pos.x;
            y = pos.y + scaler.spacing;
            w = scale.pointAtValue(scaler.to).x - x;
            h = scaler.fillWidth;
        } else {
            var pos = scale.pointAtValue(scaler.from);
            x = pos.x + scaler.spacing;
            y = pos.y;
            w = scaler.fillWidth;
            h = scale.pointAtValue(scaler.to).y - y;
        }

        if (w < 0) {
            transform.xScale = -1;
            w = -w;
            x = x - w;
        } else
            transform.xScale = 1;

        if (h < 0) {
            transform.yScale = -1;
            h = -h;
            y = y - h;
        } else
            transform.yScale = 1;

        scaler.x = x;
        scaler.y = y;
        scaler.width = w;
        scaler.height = h;
    }
}
