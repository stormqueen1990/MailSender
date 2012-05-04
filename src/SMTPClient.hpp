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
	bool sendMail(Mail mail);
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
	bool sendAuth();
	bool sendUser();
	bool sendPass();
	bool sendMailFrom();
	bool sendReceiptTo(Mail mail);
	bool sendBodyData(Mail mail);
	bool sendQuit();
	bool waitForSent();

public slots:
	void dataSent();
};

#endif // SMTPCLIENT_HPP
