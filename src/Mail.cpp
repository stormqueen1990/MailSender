#include "Mail.hpp"

QStringList Mail::getToAddress() {
	return toAddress;
}

void Mail::setToAddress(QStringList toAddress) {
	this->toAddress = toAddress;
}

QStringList Mail::getCcAddress() {
	return ccAddress;
}

void Mail::setCcAddress(QStringList ccAddress) {
	this->ccAddress = ccAddress;
}

QStringList Mail::getBccAddress() {
	return bccAddress;
}

void Mail::setBccAddress(QStringList bccAddress) {
	this->bccAddress = bccAddress;
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

QList<QByteArray> Mail::getAttachments() {
	return attachments;
}

void Mail::setAttachments(QList<QByteArray> attachments) {
	this->attachments = attachments;
}
