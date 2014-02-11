#ifndef YOULY_H
#define YOULY_H

#include <QObject>
#include <QQmlEngine>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Youly : public QObject
{
    Q_OBJECT
public:
    static QString domain() { return "http://ec2-54-228-242-127.eu-west-1.compute.amazonaws.com/future/"; }

    explicit Youly(QObject *parent = 0);
    ~Youly(void);

    Q_INVOKABLE void testBarcode ( const QString& barcode, const QString& seed );
signals:
    void barcodeValid();
    void barcodeInvalid();
public slots:
    void barcodeTestReady(void);

private:
    QNetworkAccessManager * m_netMngr;
    QNetworkReply * m_barcodeReply;
};

static QObject * YoulySingletonProvider(QQmlEngine * engine, QJSEngine * script) {
    Q_UNUSED(engine)
    Q_UNUSED(script)

    return new Youly();
}

#endif // YOULY_H
