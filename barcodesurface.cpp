#include "barcodesurface.h"
#include <iostream>
#include "CameraImageWrapper.h"
#include <QImage>

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>

using namespace zxing;

BarcodeSurface::BarcodeSurface(QObject *parent) :
    QAbstractVideoSurface(parent)
{
    m_decoder = new MultiFormatReader();
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
    //m_lastFrame = frame;
    //m_lastFrame.map(QAbstractVideoBuffer::ReadOnly);

    QVideoFrame videoFrame = frame;
    videoFrame.map(QAbstractVideoBuffer::ReadOnly);

    QImage image(videoFrame.bits(), videoFrame.width(), videoFrame.height(), videoFrame.bytesPerLine(),
                 QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat()));

    m_lastFrame = QPixmap::fromImage(image);

    emit frameReady();

    CameraImageWrapper * ciw = new CameraImageWrapper(image);
    Ref<LuminanceSource> imageRef(ciw);

    GlobalHistogramBinarizer * binz = new GlobalHistogramBinarizer(imageRef);

    Ref<Binarizer> bz (binz);
    BinaryBitmap * bb = new BinaryBitmap(bz);

    Ref<BinaryBitmap> ref(bb);
    Ref<Result> res = m_decoder->decode(ref);

    QString resStr(res->getText()->getText().c_str());

    std::cout << res->getText()->getText() << std::endl;

    /*if (!m_surface.isNull()) {
        m_surface.loadFromData(m_lastFrame.bits(), m_lastFrame.mappedBytes());
    }*/

    //m_lastFrame.unmap();
    videoFrame.unmap();

    return true;
}
