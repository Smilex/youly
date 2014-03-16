#include "barcodesurface.h"
#include <iostream>
#include "CameraImageWrapper.h"
#include <QImage>

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>

using namespace zxing;

BarcodeSurface::BarcodeSurface(QObject *parent) :
    QAbstractVideoSurface(parent), m_barcodeWorker(nullptr)
{
    m_barcodeWorker = new BarcodeWorker(this);
    m_decoder = new MultiFormatReader();
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
                 QImage::Format_RGB32);

    //std::cout << videoFrame.pixelFormat() << std::endl;
    m_lastFrame = image;

    emit frameReady();

    try {
        CameraImageWrapper * ciw = new CameraImageWrapper(image);

        Ref<LuminanceSource> imageRef(ciw);

        GlobalHistogramBinarizer * binz = new GlobalHistogramBinarizer(imageRef);

        Ref<Binarizer> bz (binz);
        BinaryBitmap * bb = new BinaryBitmap(bz);

        Ref<BinaryBitmap> ref(bb);
        Ref<Result> res = m_decoder->decode(ref, DecodeHints::EAN_8_HINT | DecodeHints::EAN_13_HINT);

        QString resStr(res->getText()->getText().c_str());

        std::cout<< "Success: " << resStr.toStdString() << std::endl;
    } catch (const zxing::Exception& e) {
        Q_UNUSED(e)
        std::cout<< e.what() << std::endl;
    }

    //m_barcodeWorker->addImage(new CameraImageWrapper(image));

    /*if (!m_surface.isNull()) {
        m_surface.loadFromData(m_lastFrame.bits(), m_lastFrame.mappedBytes());
    }*/

    videoFrame.unmap();

    return true;
}
