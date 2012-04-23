#ifndef SMTPCLIENT_HPP
#define SMTPCLIENT_HPP

#include <QApplication>
#include <QtNetwork>
#include <QtCore>
#include "Mail.hpp"

class SMTPClient : public QObject {
Q_OBJECT
public:
	SMTPClient(QString host, quint16 port, QString domain, QString username, QString password);
	~SMTPClient();
	bool sendMail();
	bool connect();

private:
	QString host;
	quint16 port;
	QString domain;
	QString username;
	QString password;
	QSslSocket *smtpSocket;
	bool disconnected;

	bool sendHello();
	bool sendMailFrom();
	bool sendReceiptTo();
	bool sendBodyData();
	bool sendQuit();
	bool waitForSent();

public slots:
	void dataSent();
};

#endif // SMTPCLIENT_HPP
