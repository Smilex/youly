#include "barcodesurface.h"
#include <iostream>
#include "CameraImageWrapper.h"
#include <QImage>

using namespace zxing;

BarcodeSurface::BarcodeSurface(QObject *parent) :
    QAbstractVideoSurface(parent), m_barcodeWorker(nullptr)
{
    m_barcodeWorker = new BarcodeWorker(this);
}

BarcodeSurface::~BarcodeSurface()
{
    if (m_barcodeWorker) {
        m_barcodeWorker->deleteLater();
    }

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
                 format);

    m_lastFrame = QPixmap::fromImage(image);

    emit frameReady();

    m_barcodeWorker->addImage(new CameraImageWrapper(image));

    if (!m_barcodeWorker->isRunning())
        m_barcodeWorker->start();

    /*if (!m_surface.isNull()) {
        m_surface.loadFromData(m_lastFrame.bits(), m_lastFrame.mappedBytes());
    }*/

    //m_lastFrame.unmap();
    videoFrame.unmap();

    return true;
}
