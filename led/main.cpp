#include "led.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc,char** argv)
{
	QApplication a(argc,argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	LED l;
	l.resize(200,50);
	l.show();

	return a.exec();
}
