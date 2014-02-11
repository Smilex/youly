#include "camerareader.h"

#include <QCamera>
#include <iostream>
#include <string>

CameraReader::CameraReader(QObject *parent) :
    QObject(parent), m_device(QCamera::availableDevices().at(0))
{
}

/*void CameraReader::image_callback(zbar::Image &image)
{
    for(zbar::Image::SymbolIterator sym = image.symbol_begin();
        sym != image.symbol_end();
        ++sym)
        if(!sym->get_count()) {
            std::cout<< sym->get_data() << std::endl;
        }
}*/

void CameraReader::enableVideo()
{
    //m_scanner.enable_cache(true);
    //m_video->enable(true);

    //zbar::Image image = m_video->next_image();
}

/*void CameraReader::processImage(zbar::Image &image)
{
    m_scanner.recycle_image(image);
    zbar::Image tmp = image.convert(*(long*)"Y800");
    m_scanner.scan(tmp);
    image.set_symbols(tmp.get_symbols());
}*/

void CameraReader::run()
{

}

void CameraReader::scan()
{
    std::string devstr = m_device.toStdString();
    //m_video = new zbar::Video(devstr);

    enableVideo();
}
