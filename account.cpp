#include "account.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QUrlQuery>
#include <iostream>

#include "youly.h"

Account::Account(QObject *parent) :
    QObject(parent),
    m_netMngr(new QNetworkAccessManager(this)), m_loginReply(nullptr)
{
    m_username = m_settings.value("account/username", "username").toString();
    m_password = m_settings.value("account/password", "password").toString();
    //m_seed = m_settings.value("account/seed").toString();
}

Account::~Account()
{
    delete m_netMngr;
}

void Account::login(const QString &username, const QString &password)
{
    QNetworkRequest request(QUrl(Youly::domain() + "user.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QUrlQuery params;
    params.addQueryItem("login", "{\"username\":\"" + username + "\", \"password\":\"" + password + "\"}");

    m_username = username;
    m_password = password;

    m_loginReply = m_netMngr->post(request, params.toString().toUtf8());

    connect (m_loginReply, SIGNAL(readyRead()), this, SLOT(loginReady()));

}

bool Account::haveCredentials() const
{
    if (m_settings.contains("account/username") && m_settings.contains("account/password"))
        return true;

    return false;
}

void Account::loginReady()
{
    if (m_loginReply->error() != QNetworkReply::NoError) {
        std::cerr << "Error with login!" << std::endl;
        return;
    }

    //std::wcout << QString(m_loginReply->readAll()).toStdWString() << std::endl;

    QJsonDocument doc = QJsonDocument::fromJson(m_loginReply->readAll());
    if ( doc.isObject() && doc.object().contains("success") && doc.object().contains("seed") ) {
        QJsonValue val = doc.object().value("success");
        if ( val.isString() && val.toString("false") == "true" ) {
            m_seed = doc.object().value("seed").toString();
            emit loginSuccessful();
            m_settings.setValue("account/username", m_username);
            m_settings.setValue("account/password", m_password);
            //m_settings.setValue("account/seed", m_seed);
        }
        else
            emit loginFailed();
    }
    else
        emit loginFailed();

    m_loginReply->deleteLater();
}
