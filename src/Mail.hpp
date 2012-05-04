#ifndef MAIL_HPP
#define MAIL_HPP

#include <QString>
#include <QStringList>
#include <QList>
#include <QByteArray>

class Mail {
public:
	Mail() {
	}
	~Mail() {
	}

	QStringList getToAddress();
	void setToAddress(QStringList);
	QStringList getCcAddress();
	void setCcAddress(QStringList);
	QStringList getBccAddress();
	void setBccAddress(QStringList);
	QString getSubject();
	void setSubject(QString);
	QString getBodyData();
	void setBodyData(QString);
	QList<QByteArray> getAttachments();
	void setAttachments(QList<QByteArray>);

private:
	QStringList toAddress;
	QStringList ccAddress;
	QStringList bccAddress;
	QString subject;
	QString bodyData;
	QList<QByteArray> attachments;
};

#endif // MAIL_HPP
