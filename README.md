MailSender
==========

Library for sending mail via SMTP protocol, built using the Qt Framework (http://qt.nokia.com/).
Requires Qt4.
Simply download the files and use qmake-qt4 to generate appropriate Makefile. It will probably need a fix to compile: you need to add -I/usr/include/QtNetwork in the INCPATH line, and -lQtNetwork in the LIBS line. Then everything should work just fine. :)

I didn't test this on Windows and appreciate any trial.
