#include "barcodecamera.h"

#include <QPainter>
#include <QMediaObject>
#include <QUrl>
#include <QQuickWindow>
#include <QSGSimpleRectNode>

#include <iostream>
#include <fstream>

using namespace zxing;

BarcodeCamera::BarcodeCamera(QQuickItem *parent) :
    QQuickItem(parent), m_camera(nullptr), m_texFrame(nullptr), m_texFrameNode(nullptr)
{
    m_surface = new BarcodeSurface(this);
    m_texFrameNode = new QSGSimpleTextureNode();

    connect(m_surface, SIGNAL(frameReady()), this, SLOT(updateFrame()));
    connect(m_surface, SIGNAL(barcodeReady(QString)), this, SLOT(barcodeRead(QString)));

    setFlag(ItemHasContents, true);
}

void BarcodeCamera::updateFrame()
{
    //m_lastFrame = m_surface->lastFrame();
    m_texFrame = this->window()->createTextureFromImage(m_surface->lastFrame());
    update();
}

void BarcodeCamera::barcodeRead(QString barcode)
{
    emit barcodeReady(barcode);
}

void BarcodeCamera::start()
{
    //m_camera->start();
    //m_camera->setViewfinder( static_cast<QAbstractVideoSurface*>( &m_surface ) );

        //std::cout<< m_mediaPlayer->state() << std::endl;
        //m_mediaPlayer->play();
        //std::cout<< m_mediaPlayer->state() << std::endl;
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
    /*m_mediaPlayer = new QMediaPlayer();
    if (m_mediaPlayer) {
        m_mediaPlayer->setMedia(QMediaContent(QUrl("http://mirrorblender.top-ix.org/peach/bigbuckbunny_movies/big_buck_bunny_480p_stereo.ogg")));
        //m_mediaPlayer->pause();
        m_mediaPlayer->setVideoOutput(m_surface);
        m_mediaPlayer->play();
    }*/
    m_camera = new QCamera(this);
    if (m_camera) {
        m_camera->setViewfinder( static_cast<QAbstractVideoSurface*>( m_surface ) );
        m_camera->start();
    }


    m_texFrameNode->setRect(this->x(), this->y(), this->width(), this->height());
    update();
}

QSGNode *BarcodeCamera::updatePaintNode(QSGNode * node, QQuickItem::UpdatePaintNodeData *)
{
    /*QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node);
    if (!n) {
        n = new QSGSimpleRectNode();
        n->setColor(Qt::red);
    }
    n->setRect(boundingRect());*/
    /*char buffer[1024];
    std::ifstream infile("/dev/video1");
    infile.read(buffer, 1024);
    infile.close();*/

    //m_texFrame = this->window()->createTextureFromImage(m_lastFrame);

    if (!m_texFrame) return node;

    QSGSimpleTextureNode *n = static_cast<QSGSimpleTextureNode *>(node);
    if (!n) {
        n = new QSGSimpleTextureNode();
    }

    n->setTexture(m_texFrame);
    n->setRect(boundingRect());

    return n;
}
