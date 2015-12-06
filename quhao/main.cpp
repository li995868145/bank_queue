#include "quhao.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc,char** argv)
{
	QApplication a(argc,argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	QUHAO q;
	q.resize(500,200);
	q.show();
	return a.exec();

}
