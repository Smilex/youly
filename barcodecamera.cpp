#include "barcodecamera.h"

BarcodeCamera::BarcodeCamera(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent), m_camera(nullptr), m_surface(this)
{
    m_camera = new QCamera(this);
    if (m_camera) {
        m_camera->start();

        m_camera->setViewfinder( static_cast<QAbstractVideoSurface*>( &m_surface ) );
    }
}


void BarcodeCamera::paint(QPainter *painter)
{
}

void BarcodeCamera::classBegin()
{
}

void BarcodeCamera::componentComplete()
{
}
