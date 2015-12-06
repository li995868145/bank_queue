#include "jiaohao.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc,char** argv)
{
	QApplication a(argc,argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	JIAOHAO j;
	j.show();
	return a.exec();

}
