#ifndef CAMERASURFACE_H
#define CAMERASURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QVideoFrame>
#include <QQuickItem>
#include <QCamera>
#include <QPixmap>
#include <zbar.h>

class BarcodeSurface : public QAbstractVideoSurface, public zbar::Decoder::Handler
{
    Q_OBJECT
public:
    explicit BarcodeSurface(QObject *parent = 0);

signals:
public slots:

public:

    // QAbstractVideoSurface interface
public:
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    virtual bool present(const QVideoFrame &frame);

private:
    zbar::Decoder m_decoder;
    zbar::Scanner m_scanner;
    QVideoFrame m_lastFrame;

    // Handler interface
public:
    virtual void decode_callback(zbar::Decoder &decoder);
};

#endif // CAMERASURFACE_H
