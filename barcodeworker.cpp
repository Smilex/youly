#include "barcodeworker.h"

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>

using namespace zxing;

BarcodeWorker::BarcodeWorker(QObject *parent) :
    QThread(parent)
{
    m_decoder = new MultiFormatReader;
}

void BarcodeWorker::run()
{
    while ( !m_queue.isEmpty() ) {
        try {
            m_imageMutex.lock();
            CameraImageWrapper * ciw = m_queue.dequeue();
            m_imageMutex.unlock();
            Ref<LuminanceSource> imageRef(ciw);

            GlobalHistogramBinarizer * binz = new GlobalHistogramBinarizer(imageRef);

            Ref<Binarizer> bz (binz);
            BinaryBitmap * bb = new BinaryBitmap(bz);

            Ref<BinaryBitmap> ref(bb);
            Ref<Result> res = m_decoder->decode(ref);

            QString resStr(res->getText()->getText().c_str());

            emit barcodeReady(resStr);
        } catch (const zxing::Exception& e) {
            Q_UNUSED(e)
        }
    }
}

void BarcodeWorker::addImage(CameraImageWrapper *image)
{
    m_imageMutex.lock();
    m_queue.enqueue(image);
    m_imageMutex.unlock();
}
