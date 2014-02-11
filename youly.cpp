#include "youly.h"

#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <iostream>

Youly::Youly(QObject *parent) :
    QObject(parent), m_netMngr(new QNetworkAccessManager(this)), m_barcodeReply(nullptr)
{
}

Youly::~Youly()
{
    delete m_netMngr;
}

void Youly::testBarcode(const QString &barcode, const QString &seed)
{
    QNetworkRequest request(QUrl(Youly::domain() + "product.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QUrlQuery params;
    params.addQueryItem("getProducts", "{\"seed\":\"" + seed + "\", \"product\":{\"barcode\":\"" + barcode + "\"}}");

    m_barcodeReply = m_netMngr->post(request, params.toString().toUtf8());

    connect (m_barcodeReply, SIGNAL(readyRead()), this, SLOT(barcodeTestReady()));
}

void Youly::barcodeTestReady()
{
    if (m_barcodeReply->error() != QNetworkReply::NoError) {
        std::cerr << "Error with sending barcode!" << std::endl;
        return;
    }

    //std::wcout << QString(m_barcodeReply->readAll()).toStdWString() << std::endl;

    QJsonDocument doc = QJsonDocument::fromJson(m_barcodeReply->readAll());
    if (doc.isObject() && doc.object().contains("product")) {
        QJsonValue product = doc.object().value("product");
        if ( product.isObject() ) {
            emit barcodeValid();
        } else {
            emit barcodeInvalid();
        }
    } else {
        emit barcodeInvalid();
    }

    m_barcodeReply->deleteLater();
}
