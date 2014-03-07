#include "barcodecamera.h"

#include <QPainter>
#include <QMediaObject>
#include <QUrl>
#include <QQuickWindow>
#include <QSGSimpleRectNode>

#include <iostream>

BarcodeCamera::BarcodeCamera(QQuickItem *parent) :
    QQuickItem(parent), m_camera(nullptr), m_surface(this), m_texFrame(nullptr), m_texFrameNode(nullptr)
{
    m_texFrameNode = new QSGSimpleTextureNode();
    m_camera = new QCamera(this);
    if (m_camera) {
        m_camera->start();

        m_camera->setViewfinder( static_cast<QAbstractVideoSurface*>( &m_surface ) );
    }

    connect(&m_surface, SIGNAL(frameReady()), this, SLOT(updateFrame()));
    connect(&m_surface, SIGNAL(barcodeReady(QString)), this, SLOT(barcodeRead(QString)));

    setFlag(ItemHasContents, true);
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

void BarcodeCamera::classBegin()
{
}

void BarcodeCamera::componentComplete()
{
}

QSGNode *BarcodeCamera::updatePaintNode(QSGNode *, QQuickItem::UpdatePaintNodeData *)
{
    if (m_texFrame) {
        delete m_texFrame;
    }
    m_texFrame = this->window()->createTextureFromImage(m_lastFrame);
    m_texFrameNode->setTexture(m_texFrame);
    return m_texFrameNode;
}
