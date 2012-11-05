#include "SMTPClient.hpp"

SMTPClient::SMTPClient(QString host, quint16 port, QString domain, QString username, QString password) {
	// Stores data
	this->host = host;
	this->port = port;
	this->domain = domain;
	this->username = username;
	this->password = password;
	this->disconnected = true;

	// Adjusts codecs
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

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

bool SMTPClient::sendMail(Mail mail) {
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
		qDebug() << "HELLO SENT";
		return false;
	}

	if(!sendAuth()) {
		return false;
	}

	if(!sendUser()) {
		return false;
	}

	if(!sendPass()) {
		return false;
	}

	if(!sendMailFrom()) {
		return false;
	}

	if(!sendReceiptTo(mail)) {
		return false;
	}

	if(!sendBodyData(mail)) {
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

bool SMTPClient::sendAuth() {
	smtpSocket->write("AUTH LOGIN\r\n");
	return waitForSent();
}

bool SMTPClient::sendUser() {
	smtpSocket->write(username.toUtf8().toBase64());
	smtpSocket->write("\r\n");
	return waitForSent();
}

bool SMTPClient::sendPass() {
	smtpSocket->write(password.toUtf8().toBase64());
	smtpSocket->write("\r\n");
	return waitForSent();
}

bool SMTPClient::sendMailFrom() {
	smtpSocket->write("MAIL FROM:<");
	smtpSocket->write(username.toUtf8());
	smtpSocket->write(">\r\n");
	return waitForSent();
}

bool SMTPClient::sendReceiptTo(Mail mail) {
	foreach(QString to, mail.getToAddress()) {
		QString receiptTo("RCPT TO:");
		receiptTo.append("<").append(to.toUtf8());
		receiptTo.append(">\r\n");
		smtpSocket->write(receiptTo.toUtf8());
	}
	return waitForSent();
}

bool SMTPClient::sendBodyData(Mail mail) {
	smtpSocket->write("DATA\r\n");
	if(waitForSent()) {
		QString bodyData("From: ");
		bodyData.append(username);
		bodyData.append("\r\n");
		bodyData.append("To: ");

		foreach(QString to, mail.getToAddress()) {
			bodyData.append(to);
			bodyData.append(",");
		}

		bodyData.append("\r\n");
		bodyData.append("Subject: ");
		bodyData.append(mail.getSubject());
		bodyData.append("\r\n");
		bodyData.append("Content-Type: text/plain; charset=utf-8\r\n");
		bodyData.append("\r\n");
		bodyData.append(mail.getBodyData());
		bodyData.append("\r\n.\r\n");

		smtpSocket->write(bodyData.toUtf8());

		return waitForSent();
	}

	return false;
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
