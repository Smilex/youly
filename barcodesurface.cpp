#include "barcodesurface.h"
#include <iostream>
#include <QImage>

BarcodeSurface::BarcodeSurface(QObject *parent) :
    QAbstractVideoSurface(parent)
{
}

BarcodeSurface::~BarcodeSurface()
{
}

void BarcodeSurface::barcodeRead(QString barcode)
{
    emit barcodeReady(barcode);
}

QList<QVideoFrame::PixelFormat> BarcodeSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType)

    QList<QVideoFrame::PixelFormat> list;
    list.append(QVideoFrame::PixelFormat::Format_RGB32);
    return list;
}

bool BarcodeSurface::present(const QVideoFrame &frame)
{
    //m_lastFrame = frame;
    //m_lastFrame.map(QAbstractVideoBuffer::ReadOnly);

    QVideoFrame videoFrame = frame;
    videoFrame.map(QAbstractVideoBuffer::ReadOnly);

    QImage::Format format = QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat());

    QImage image(videoFrame.bits(), videoFrame.width(), videoFrame.height(), videoFrame.bytesPerLine(),
                 QImage::Format_RGB32);

    //std::cout << videoFrame.pixelFormat() << std::endl;
    m_lastFrame = image;

    emit frameReady();

    videoFrame.unmap();

    return true;
}
