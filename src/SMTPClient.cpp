#include "SMTPClient.hpp"

SMTPClient::SMTPClient(QString host, quint16 port, QString domain, QString username, QString password) {
	// Stores data
	this->host = host;
	this->port = port;
	this->domain = domain;
	this->username = username;
	this->password = password;
	this->disconnected = true;

	// Connects the socket
	smtpSocket = new QSslSocket();
	
	smtpSocket->open(QIODevice::ReadWrite);
}

SMTPClient::~SMTPClient() {
	delete smtpSocket;
}

bool SMTPClient::connect() {
	smtpSocket->connectToHostEncrypted(host, port);
	bool res = smtpSocket->waitForEncrypted();
	if(res) {
		QObject::connect(smtpSocket, SIGNAL(encryptedBytesWritten(qint64)), this, SLOT(dataSent()));
	}

	disconnected = !res;

	return res;
}

bool SMTPClient::sendMail() {
	if(disconnected) {
		QObject::disconnect(smtpSocket, SIGNAL(encryptedBytesWritten(qint64)), this, SLOT(dataSent()));
		smtpSocket->disconnectFromHost();
		if(smtpSocket->waitForDisconnected()) {
			if(!connect()) {
				qDebug() << smtpSocket->errorString();
				return false;
			}
		} else {
			return false;
		}
	}

	if(!sendHello()) {
		return false;
	}

	if(!sendQuit()) {
		return false;
	}
	
	return true;
}

bool SMTPClient::sendHello() {
	QString hello("EHLO %1\r\n");
	QByteArray arr = hello.arg(domain).toUtf8();
	smtpSocket->write(arr);
	return waitForSent();
}

bool SMTPClient::sendMailFrom() {
	return true;
}

bool SMTPClient::sendReceiptTo() {
	return true;
}

bool SMTPClient::sendBodyData() {
	return true;
}

bool SMTPClient::sendQuit() {
	smtpSocket->write("QUIT\r\n");
	disconnected = true;
	return waitForSent();
}

void SMTPClient::dataSent() {
	qDebug() << "SENT!";
	if(smtpSocket->waitForReadyRead()) {
		qDebug() << smtpSocket->readAll().data();
	}
}

bool SMTPClient::waitForSent() {
	bool res = smtpSocket->waitForBytesWritten();
	if(!res) {
		qDebug() << smtpSocket->errorString();
	}

	return res;
}
