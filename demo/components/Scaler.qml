import indigets 1.0
import QtQuick 1.0

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

        var posFrom = scale.pointAtValue(scaler.from);
        posFrom = scale.mapToItem(scaler.parent, posFrom.x, posFrom.y);
        var posTo = scale.pointAtValue(scaler.to);
        posTo = scale.mapToItem(scaler.parent, posTo.x, posTo.y);

        var x, y, w, h;
        if (scale.orientation == LinearScale.Horizontal) {
            x = posFrom.x;
            y = posFrom.y + scaler.spacing;
            w = posTo.x - x;
            h = scaler.fillWidth;
        } else {
            x = posFrom.x + scaler.spacing;
            y = posFrom.y;
            w = scaler.fillWidth;
            h = posTo.y - y;
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
