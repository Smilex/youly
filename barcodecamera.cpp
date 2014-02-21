#include "barcodecamera.h"

#include <QPainter>

BarcodeCamera::BarcodeCamera(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent), m_camera(nullptr), m_surface(this)
{
    m_camera = new QCamera(this);
    if (m_camera) {
        m_camera->start();

        m_camera->setViewfinder( static_cast<QAbstractVideoSurface*>( &m_surface ) );
    }

    connect(&m_surface, SIGNAL(frameReady()), this, SLOT(updateFrame()));
}

void BarcodeCamera::updateFrame()
{
    m_lastFrame = m_surface.lastFrame();
    update();
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
