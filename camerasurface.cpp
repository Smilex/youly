#include "camerasurface.h"
#include <iostream>


using namespace zbar;

CameraSurface::CameraSurface(QObject *parent) :
    QAbstractVideoSurface(parent),m_decoder(), m_scanner(m_decoder)
{
    m_camera.setViewfinder(this);
    m_decoder.set_handler(*this);
}

void CameraSurface::show()
{
    if (m_surface.isNull()) {
        m_surface = QPixmap(m_width, m_height);
    }
}

void CameraSurface::hide()
{

}


QList<QVideoFrame::PixelFormat> CameraSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType)

    QList<QVideoFrame::PixelFormat> list;
    list.append(QVideoFrame::PixelFormat::Format_BGR24);
    list.append(QVideoFrame::PixelFormat::Format_RGB24);
    return list;
}

bool CameraSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    return supportedPixelFormats(format.handleType()).contains(format.pixelFormat());
}

QVideoSurfaceFormat CameraSurface::nearestFormat(const QVideoSurfaceFormat &format) const
{
    return format;
}

bool CameraSurface::start(const QVideoSurfaceFormat &format)
{
    return QAbstractVideoSurface::start(format);
}

void CameraSurface::stop()
{
    QAbstractVideoSurface::stop();
}

bool CameraSurface::present(const QVideoFrame &frame)
{
    m_lastFrame = frame;
    m_lastFrame.map(QAbstractVideoBuffer::ReadOnly);
    m_scanner.new_scan();
    m_scanner.scan_rgb24(m_lastFrame.bits());
    m_scanner.flush();

    if (!m_surface.isNull()) {
        m_surface.loadFromData(m_lastFrame.bits(), m_lastFrame.mappedBytes());
    }

    m_lastFrame.unmap();

    emit drawReady();
}


void CameraSurface::decode_callback(Decoder &decoder)
{
}
