#include "barcodeworker.h"

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <iostream>

using namespace zxing;

BarcodeWorker::BarcodeWorker(QObject *parent) :
    QThread(parent)
{
    m_decoder = new MultiFormatReader;
}

void BarcodeWorker::run()
{
    while ( true ) {
        try {
            if (m_queue.length() == 0) {
                msleep(500);
                continue;
            }
            m_imageMutex.lock();
            CameraImageWrapper * ciw = m_queue.dequeue();
            m_imageMutex.unlock();
            Ref<LuminanceSource> imageRef(ciw);

            GlobalHistogramBinarizer * binz = new GlobalHistogramBinarizer(imageRef);

            Ref<Binarizer> bz (binz);
            BinaryBitmap * bb = new BinaryBitmap(bz);

            Ref<BinaryBitmap> ref(bb);
            Ref<Result> res = m_decoder->decode(ref, DecodeHints::EAN_13_HINT);

            ciw->release();
            QString resStr(res->getText()->getText().c_str());

            emit barcodeReady(resStr);
        } catch (const zxing::Exception& e) {
            Q_UNUSED(e)
            std::cout<< e.what() << std::endl;
        }
    }
}

void BarcodeWorker::addImage(CameraImageWrapper *image)
{
    m_imageMutex.lock();
    m_queue.enqueue(image);
    m_imageMutex.unlock();
}
