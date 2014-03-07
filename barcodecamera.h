#ifndef BARCODECAMERA_H
#define BARCODECAMERA_H

#include <QQuickPaintedItem>
#include <QCamera>
#include <QImage>
#include <QSGTexture>
#include <QSGSimpleTextureNode>

#include "barcodesurface.h"

class BarcodeCamera : public QQuickItem
{
    Q_OBJECT
public:
    explicit BarcodeCamera(QQuickItem *parent = 0);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
signals:
    void barcodeReady(QString barcode);
public slots:
    void updateFrame();
    void barcodeRead(QString barcode);

private:
    QCamera * m_camera;
    BarcodeSurface m_surface;
    QImage m_lastFrame;
    QSGTexture * m_texFrame;
    QSGSimpleTextureNode * m_texFrameNode;

public:
    virtual void classBegin();
    virtual void componentComplete();

    // QQuickItem interface
protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
};

#endif // BARCODECAMERA_H
