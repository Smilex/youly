#ifndef CAMERASURFACE_H
#define CAMERASURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QVideoFrame>
#include <QQuickItem>
#include <QCamera>
#include <QPixmap>
#include <zxing/MultiFormatReader.h>

class BarcodeSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit BarcodeSurface(QObject *parent = 0);

    QPixmap lastFrame() const { return m_lastFrame; }
signals:
    void frameReady();
public slots:

public:

    // QAbstractVideoSurface interface
public:
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    virtual bool present(const QVideoFrame &frame);

private:
    zxing::MultiFormatReader * m_decoder;
    QPixmap m_lastFrame;

    // Handler interface
public:
};

#endif // CAMERASURFACE_H
