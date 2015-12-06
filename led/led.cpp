#include "led.h"
#include "../msgtype.h"
#include "conn.h"

Thread::Thread()
{
	lab = new QLabel;
	s = new QString;
	str=' ';
}
void Thread::run()
{
	int sd=crelink();//创建socket
	while(int sd2=linkacc(sd)) //等待连接
	{	
		if(sd2==-1)
		{
			continue;
		}		
		while(int rec=linkrecv(sd2,&str))//等待消息
		{
			if(rec==-1)
			{
				break;
			}
			//lab->setText(tr("请 ")+str+s->setNum(rec)+tr("来此办理业务!"));//显示消息
			emit showdat(str,rec);
		}
	}
}
LED::LED()
{
	QPalette p;
	p.setColor(QPalette::Active,QPalette::Window,QColor(80,109,218));
	p.setColor(QPalette::Inactive,QPalette::Window,QColor(80,109,218));
	setPalette(p);
	setWindowTitle(tr("LED屏幕"));
	lab_f = new QLabel;
	lab_e = new QLabel;
	lab_num0 = new QLabel;
	lab_num1 = new QLabel;
	lab_num2 = new QLabel;
	lab_num3 = new QLabel;
	lab_num4 = new QLabel;
	lab_led = new QLabel;
	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->addWidget(lab_f);
	layout->addWidget(lab_led);
	layout->addWidget(lab_num0);
	layout->addWidget(lab_num1);
	layout->addWidget(lab_num2);
	layout->addWidget(lab_num3);
	layout->addWidget(lab_num4);
	layout->addWidget(lab_e);
	layout->addStretch();
	connect(&thr,SIGNAL(showdat(char,int)),this,SLOT(showdata(char,int)));
	thr.lab=lab_led;
	thr.start(); //开始一个线程 维护socket连接
}
LED::~LED()
{

}
void LED::closeEvent(QCloseEvent *event)
{
	thr.terminate(); //杀死线程
	thr.wait();
}
void LED::showdata(char str,int num)
{
	clear_pix(); //清除屏幕数字
	lab_f->setPixmap(QPixmap("./image/qing.png"));
	lab_e->setPixmap(QPixmap("./image/blyw.png"));
switch(str) //设置业务类型
	{
		case 'A':
			lab_led->setPixmap(QPixmap("./image/a.png"));
			break;
		case 'B':
			lab_led->setPixmap(QPixmap("./image/b.png"));
			break;
		case 'C':
			lab_led->setPixmap(QPixmap("./image/c.png"));
			break;
	}
	QString s,temp;
	s=QString::number(num);
	int n=s.size();
	QChar s1;
	switch(n)
	{
		case 5:
			s1=s[4];
			lab_num4->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_num4->show();
		case 4:
			s1=s[3];
			lab_num3->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_num3->show();
		case 3:
			s1=s[2];
			lab_num2->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_num2->show();
		case 2:
			s1=s[1];
			lab_num1->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_num1->show();
		case 1:
			s1=s[0];
			lab_num0->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_num0->show();
			break;
	}
}

void LED::clear_pix()
{
			lab_num4->setPixmap(QPixmap(""));
			lab_num4->hide();
			lab_num3->setPixmap(QPixmap(""));
			lab_num3->hide();
			lab_num2->setPixmap(QPixmap(""));
			lab_num2->hide();
			lab_num1->setPixmap(QPixmap(""));
			lab_num1->hide();
			lab_num0->setPixmap(QPixmap(""));
			lab_num0->hide();
}
