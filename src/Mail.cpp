#include "Mail.hpp"

QString Mail::getFromAddress() {
	return fromAddress;
}

void Mail::setFromAddress(QString fromAddress) {
	this->fromAddress = fromAddress;
}

QString Mail::getToAddress() {
	return toAddress;
}

void Mail::setToAddress(QString toAddress) {
	this->toAddress = toAddress;
}

QString Mail::getSubject() {
	return subject;
}

void Mail::setSubject(QString subject) {
	this->subject = subject;
}

QString Mail::getBodyData() {
	return bodyData;
}

void Mail::setBodyData(QString bodyData) {
	this->bodyData = bodyData;
}
