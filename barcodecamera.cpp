#include "barcodecamera.h"

#include <QPainter>
#include <QMediaObject>
#include <QUrl>

#include <iostream>

BarcodeCamera::BarcodeCamera(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent), m_camera(nullptr), m_surface(this)
{
    m_camera = new QCamera(this);
    if (m_camera) {
        //m_camera->start();

        //m_camera->setViewfinder( static_cast<QAbstractVideoSurface*>( &m_surface ) );
    }

    connect(&m_surface, SIGNAL(frameReady()), this, SLOT(updateFrame()));
    connect(&m_surface, SIGNAL(barcodeReady(QString)), this, SLOT(barcodeRead(QString)));
}

void BarcodeCamera::updateFrame()
{
    m_lastFrame = m_surface.lastFrame();
    update();
}

void BarcodeCamera::barcodeRead(QString barcode)
{
    emit barcodeReady(barcode);
}

void BarcodeCamera::start()
{
    m_camera->start();
    m_camera->setViewfinder( static_cast<QAbstractVideoSurface*>( &m_surface ) );
}

void BarcodeCamera::stop()
{
    m_camera->stop();
}


void BarcodeCamera::paint(QPainter *painter)
{
    if (painter) {
        if (m_lastFrame.isNull()) {
            painter->fillRect(this->x(), this->y(), this->width(), this->height(), Qt::lightGray);
        } else {
            painter->drawPixmap(this->x(), this->y(), this->width(), this->height(), m_lastFrame);
        }
    }
}

void BarcodeCamera::classBegin()
{
}

void BarcodeCamera::componentComplete()
{
}
