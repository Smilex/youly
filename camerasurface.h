#ifndef CAMERASURFACE_H
#define CAMERASURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QVideoFrame>
#include <QQuickItem>
#include <QCamera>
#include <QPixmap>
#include <zbar.h>

class CameraSurface : public QAbstractVideoSurface, public zbar::Decoder::Handler
{
    Q_OBJECT
    Q_PROPERTY(quint32 width READ width WRITE setWidth)
    Q_PROPERTY(quint32 height READ height WRITE setHeight)
public:
    explicit CameraSurface(QObject *parent = 0);

signals:
    void drawReady(void);
public slots:

public:
    Q_INVOKABLE void show(void);
    Q_INVOKABLE void hide(void);

    quint32 width(void) const {return m_width;}
    void setWidth(quint32 rhs) {m_width = rhs;}

    quint32 height(void) const {return m_height;}
    void setHeight(quint32 rhs) {m_height = rhs;}

    // QAbstractVideoSurface interface
public:
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    virtual bool isFormatSupported(const QVideoSurfaceFormat &format) const;
    virtual QVideoSurfaceFormat nearestFormat(const QVideoSurfaceFormat &format) const;
    virtual bool start(const QVideoSurfaceFormat &format);
    virtual void stop();
    virtual bool present(const QVideoFrame &frame);

private:
    zbar::Decoder m_decoder;
    zbar::Scanner m_scanner;
    QCamera m_camera;
    QVideoFrame m_lastFrame;
    QPixmap m_surface;

    quint32 m_width;
    quint32 m_height;

    // Handler interface
public:
    virtual void decode_callback(zbar::Decoder &decoder);
};

#endif // CAMERASURFACE_H
