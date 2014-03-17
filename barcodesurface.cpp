#include "barcodesurface.h"
#include <iostream>
#include "CameraImageWrapper.h"
#include <QImage>
#include <QTime>

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>

using namespace zxing;
using namespace zbar;

#define zbar_fourcc(a, b, c, d)                 \
        ((unsigned long)(a) |                   \
         ((unsigned long)(b) << 8) |            \
         ((unsigned long)(c) << 16) |           \
         ((unsigned long)(d) << 24))

class QZBarImage
    : public Image
{
public:

    /// construct a zbar library image based on an existing QImage.

    QZBarImage (const QImage &qimg)
        : qimg(qimg)
    {
        QImage::Format fmt = qimg.format();
        if(fmt != QImage::Format_RGB32 &&
           fmt != QImage::Format_ARGB32 &&
           fmt != QImage::Format_ARGB32_Premultiplied)
            throw FormatError();

        unsigned bpl = qimg.bytesPerLine();
        unsigned width = bpl / 4;
        unsigned height = qimg.height();
        set_size(width, height);
        set_format(zbar_fourcc('B','G','R','4'));
        unsigned long datalen = qimg.byteCount();
        set_data(qimg.bits(), datalen);

        if((width * 4 != bpl) ||
           (width * height * 4 > datalen))
            throw FormatError();
    }

private:
    QImage qimg;
};

BarcodeSurface::BarcodeSurface(QObject *parent) :
    QAbstractVideoSurface(parent), m_barcodeWorker(nullptr)
{
    m_barcodeWorker = new BarcodeWorker(this);
    m_decoder = new MultiFormatReader();
    m_scanner.set_handler(*this);
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

    QTime t;
    t.start();

    /*try {
        CameraImageWrapper * ciw = CameraImageWrapper::Factory(image, 640, 480, false);

        Ref<LuminanceSource> imageRef(ciw);

        GlobalHistogramBinarizer * binz = new GlobalHistogramBinarizer(imageRef);

        Ref<Binarizer> bz (binz);
        BinaryBitmap * bb = new BinaryBitmap(bz);

        MultiFormatReader decoder;

        Ref<BinaryBitmap> ref(bb);
        Ref<Result> res = decoder.decode(ref, DecodeHints::EAN_8_HINT | DecodeHints::EAN_13_HINT);

        QString resStr(res->getText()->getText().c_str());

        std::cout<< "Success: " << resStr.toStdString() << std::endl;
    } catch (const zxing::Exception& e) {
        Q_UNUSED(e)
        //std::cout<< e.what() << std::endl;
    }*/

    QZBarImage img(image);
    //m_scanner.recycle_image(img);
    Image tmp = img.convert(*(long*)"Y800");
    m_scanner.scan(tmp);
    img.set_symbols(tmp.get_symbols());
    if (img.symbol_begin() != img.symbol_end())
        std::cout << "Success?" << std::endl;

    //std::cout<< "Time: " << t.elapsed() << std::endl;

    //m_barcodeWorker->addImage(new CameraImageWrapper(image));

    /*if (!m_surface.isNull()) {
        m_surface.loadFromData(m_lastFrame.bits(), m_lastFrame.mappedBytes());
    }*/

    videoFrame.unmap();

    return true;
}


void BarcodeSurface::image_callback(Image &image)
{
    std::cout << "derp" << std::endl;
}
