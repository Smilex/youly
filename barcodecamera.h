#ifndef BARCODECAMERA_H
#define BARCODECAMERA_H

#include <QQuickPaintedItem>
#include <QCamera>
#include <QPixmap>

#include "barcodesurface.h"

class BarcodeCamera : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit BarcodeCamera(QQuickPaintedItem *parent = 0);

signals:

public slots:
    void updateFrame();

private:
    QCamera * m_camera;
    BarcodeSurface m_surface;
    QPixmap m_lastFrame;

    // QQuickPaintedItem interface
public:
    virtual void paint(QPainter *painter);

    // QQmlParserStatus interface
public:
    virtual void classBegin();
    virtual void componentComplete();
};

#endif // BARCODECAMERA_H
