#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QQmlEngine>
#include <QSettings>


class Account : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QString username READ username CONSTANT)
    Q_PROPERTY (QString password READ password CONSTANT)
    Q_PROPERTY (QString seed READ seed CONSTANT)
public:
    explicit Account(QObject *parent = 0);
    ~Account(void);

    Q_INVOKABLE void login(const QString& username, const QString& password);
    Q_INVOKABLE bool haveCredentials(void) const;
    QString username() const {return m_username;}
    QString password() const {return m_password;}
    QString seed() const {return m_seed;}
signals:
    void loginSuccessful(void);
    void loginFailed(void);

public slots:
    void loginReady();

private:
    QNetworkAccessManager * m_netMngr;
    QNetworkReply * m_loginReply;
    QString m_username;
    QString m_password;
    QString m_seed;
    QSettings m_settings;
};

static QObject * AccountSingletonProvider(QQmlEngine * engine, QJSEngine * script) {
    Q_UNUSED(engine)
    Q_UNUSED(script)

    return new Account();
}

#endif // ACCOUNT_H
