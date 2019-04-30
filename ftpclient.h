#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include <QObject>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QByteArray>
#include <QMessageBox>
#include <QFileInfo>
#include <QDir>

class FtpClient : public QObject
{
    Q_OBJECT

protected slots:
    void finished(QNetworkReply *reply);
public:
    FtpClient();
    void FtpGet(QString sor,QString dev );
    void FtpPut(QString source,QString dev);
    void FtpSetUserInfor(QString user,QString pwd);
    void FtpSetHostPort(QString str,int port = 21);
private:
    QFile * m_pFile;
    QNetworkReply *m_pReply;
    QNetworkAccessManager *m_pManager;
    QUrl * m_pUrl;

};

#endif // FTPCLIENT_H
