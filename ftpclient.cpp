#include "ftpclient.h"

FtpClient::FtpClient()
{
    m_pManager=new QNetworkAccessManager();
    m_pUrl = new QUrl();
    m_pUrl->setScheme("ftp");
    connect(m_pManager,SIGNAL(finished(QNetworkReply *)),this,SLOT(finished(QNetworkReply *)));
}
void FtpClient::finished(QNetworkReply *reply)
{
    m_pFile->write(reply->readAll());
    m_pFile->flush();
    m_pFile->close();
    reply->deleteLater();
}

void FtpClient::FtpGet(QString sor,QString dev )
{
   QFileInfo info;
   info.setFile(dev);
   m_pFile = new QFile(info.filePath());
   m_pFile ->open(QIODevice::Append|QIODevice::WriteOnly);
   m_pUrl ->setPath(sor);

   m_pReply = m_pManager->get(QNetworkRequest(*m_pUrl));
}
void FtpClient::FtpPut(QString source,QString dev)
{
   QFile file(source);
   file.open(QIODevice::ReadOnly);
   QByteArray data = file.readAll();

   m_pUrl->setPath(dev);
   m_pManager->put(QNetworkRequest(*m_pUrl),data);
}
void FtpClient::FtpSetUserInfor(QString user,QString pwd)
{
    m_pUrl->setUserName(user);
    m_pUrl->setPassword(pwd);
}
void FtpClient::FtpSetHostPort(QString str,int port)
{
    m_pUrl->setHost(str);
    m_pUrl->setPort(port);
}
