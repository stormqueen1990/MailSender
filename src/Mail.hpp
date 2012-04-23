#ifndef MAIL_HPP
#define MAIL_HPP

#include <QString>

class Mail {
public:
	Mail() {
	}
	~Mail() {
	}

	QString getFromAddress();
	void setFromAddress(QString);
	QString getToAddress();
	void setToAddress(QString);
	QString getSubject();
	void setSubject(QString);
	QString getBodyData();
	void setBodyData(QString);

private:
	QString fromAddress;
	QString toAddress;
	QString ccAddress;
	QString bccAddress;
	QString subject;
	QString headers;
	QString bodyData;
	QString attachments;
};

#endif // MAIL_HPP
