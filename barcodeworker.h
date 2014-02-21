#ifndef BARCODEWORKER_H
#define BARCODEWORKER_H

#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QString>
#include "CameraImageWrapper.h"

#include <zxing/MultiFormatReader.h>

class BarcodeWorker : public QThread
{
    Q_OBJECT
public:
    explicit BarcodeWorker(QObject *parent = 0);

    void run() Q_DECL_OVERRIDE;

    void addImage(CameraImageWrapper* image);

signals:
    void barcodeReady(QString barcode);
public slots:

private:
    QQueue<CameraImageWrapper*> m_queue;
    zxing::MultiFormatReader * m_decoder;
    QMutex m_imageMutex;
};

#endif // BARCODEWORKER_H
