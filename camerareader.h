#ifndef CAMERAREADER_H
#define CAMERAREADER_H

#include <QObject>
#include <QQmlEngine>
#include <zxing/ZXing.h>

class CameraReader :
        public QObject,
{
    Q_OBJECT
public:
    explicit CameraReader(QObject *parent = 0);

    //virtual void image_callback(zbar::Image &image);

    Q_INVOKABLE void run(void);
    Q_INVOKABLE void scan(void);
signals:

public slots:

private:
    void enableVideo(void);
    //void processImage(zbar::Image &image);
private:
    QString m_device;
    bool m_videoEnabled;
    //zbar::Video* m_video;
    //zbar::ImageScanner m_scanner;
};

static QObject * CameraReaderSingletonProvider(QQmlEngine * engine, QJSEngine * script) {
    Q_UNUSED(engine)
    Q_UNUSED(script)

    return new CameraReader();
}

#endif // CAMERAREADER_H
