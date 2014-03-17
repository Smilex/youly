#ifndef CAMERASURFACE_H
#define CAMERASURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QVideoFrame>
#include <QQuickItem>
#include <QCamera>
#include <QImage>
#include <QMutex>
#include <iostream>
#include <zxing/MultiFormatReader.h>
#include <zbar.h>

#include "barcodeworker.h"

class BarcodeSurface : public QAbstractVideoSurface,
        public zbar::Image::Handler
{
    Q_OBJECT
public:
    explicit BarcodeSurface(QObject *parent = 0);
    virtual ~BarcodeSurface(void);

    QImage lastFrame() const {
        return m_lastFrame;
    }

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
    QImage m_lastFrame;
    BarcodeWorker * m_barcodeWorker;
    zxing::MultiFormatReader * m_decoder;
    zbar::ImageScanner m_scanner;

    // Handler interface
public:
    void image_callback(zbar::Image &image);
};

#endif // CAMERASURFACE_H
