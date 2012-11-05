MailSender
==========

Library for sending mail via SMTP protocol, built using the Qt Framework (http://qt.nokia.com/).<br>
Requires Qt4.<br>
Simply download the files and use <pre>qmake-qt4</pre> to generate appropriate Makefile. It will probably need a fix to compile: you need to add <pre>-I/usr/include/QtNetwork</pre> in the <pre>INCPATH</pre> line, and <pre>-lQtNetwork</pre> in the <pre>LIBS</pre> line. Then everything should work just fine. :)<p>
I didn't test this on Windows and appreciate any trial.
