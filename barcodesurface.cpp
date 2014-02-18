#include "barcodesurface.h"
#include <iostream>


using namespace zbar;

BarcodeSurface::BarcodeSurface(QObject *parent) :
    QAbstractVideoSurface(parent),m_decoder(), m_scanner(m_decoder)
{
    m_decoder.set_handler(*this);
}

QList<QVideoFrame::PixelFormat> BarcodeSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType)

    QList<QVideoFrame::PixelFormat> list;
    list.append(QVideoFrame::PixelFormat::Format_BGR24);
    list.append(QVideoFrame::PixelFormat::Format_RGB24);
    return list;
}

bool BarcodeSurface::present(const QVideoFrame &frame)
{
    m_lastFrame = frame;
    m_lastFrame.map(QAbstractVideoBuffer::ReadOnly);
    m_scanner.new_scan();
    m_scanner.scan_rgb24(m_lastFrame.bits());
    m_scanner.flush();

    /*if (!m_surface.isNull()) {
        m_surface.loadFromData(m_lastFrame.bits(), m_lastFrame.mappedBytes());
    }*/

    m_lastFrame.unmap();

    return true;
}


void BarcodeSurface::decode_callback(Decoder &decoder)
{
    std::cout<< "decode\n";
}
