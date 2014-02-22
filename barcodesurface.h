#ifndef CAMERASURFACE_H
#define CAMERASURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QVideoFrame>
#include <QQuickItem>
#include <QCamera>
#include <QPixmap>

#include "barcodeworker.h"

class BarcodeSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit BarcodeSurface(QObject *parent = 0);
    virtual ~BarcodeSurface(void);

    QPixmap lastFrame() const { return m_lastFrame; }
signals:
    void frameReady();
    void barcodeReady(QString barcode);
public slots:
    void barcodeRead(QString barcode);
public:

    // QAbstractVideoSurface interface
public:
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    virtual bool present(const QVideoFrame &frame);

private:
    QPixmap m_lastFrame;
    BarcodeWorker * m_barcodeWorker;
};

#endif // CAMERASURFACE_H
