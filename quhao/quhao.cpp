#include "quhao.h"
#include "conn.h"
#include <QMessageBox>
#include <QString>
#include <QPixmap>
#include <QBitmap>
#include <QChar>
QUHAO::QUHAO()
{
	/* 属性设置*/
	setAutoFillBackground(true);
	QPalette p;
	p.setColor(QPalette::Active,QPalette::Window,QColor(80,109,218));
	p.setColor(QPalette::Inactive,QPalette::Window,QColor(80,109,218));
	p.setColor(QPalette::Active,QPalette::Button,QColor(80,109,218));
	p.setColor(QPalette::Inactive,QPalette::Button,QColor(80,109,218));
	setPalette(p);
	setWindowTitle(tr("取号端"));
	lab_title = new QLabel(tr("排队取号系统－－－取号处"));
	lab_numtype= new QLabel();
	lab_nu = new QLabel;
	lab_nu->setPixmap(QPixmap("./image/qdhm.png"));
	lab_wait = new QLabel;
	lab_wait->setPixmap(QPixmap("./image/dengdai.png"));

	lab_num0 = new QLabel;
	lab_num1 = new QLabel;
	lab_num2 = new QLabel;
	lab_num3 = new QLabel;
	lab_num4 = new QLabel;

	lab_wat0 = new QLabel;
	lab_wat1 = new QLabel;
	lab_wat2 = new QLabel;
	lab_wat3 = new QLabel;
	lab_wat4 = new QLabel;

	QHBoxLayout *lay_num = new QHBoxLayout;
	lay_num->addWidget(lab_numtype);
	lay_num->addWidget(lab_num0);
	lay_num->addWidget(lab_num1);
	lay_num->addWidget(lab_num2);
	lay_num->addWidget(lab_num3);
	lay_num->addWidget(lab_num4);
	lay_num->addStretch();
	
	QHBoxLayout *lay_wait = new QHBoxLayout;
	lay_wait->addWidget(lab_wat0);
	lay_wait->addWidget(lab_wat1);
	lay_wait->addWidget(lab_wat2);
	lay_wait->addWidget(lab_wat3);
	lay_wait->addWidget(lab_wat4);
	lay_wait->addStretch();
	
	but_a = new QPushButton; //A类业务
	but_a->setFlat(true);
	but_a->setAutoDefault(true);
	but_a->setAutoFillBackground(true);
	but_a->setIcon(QPixmap("./image/opa.png"));
	but_a->setIconSize(QPixmap("./image/opa.png").size());
	but_b = new QPushButton; //B类业务
	but_b->setFlat(true);
	but_b->setAutoFillBackground(true);
	but_b->setIcon(QPixmap("./image/opb.png"));
	but_b->setIconSize(QPixmap("./image/opb.png").size());
	but_c = new QPushButton; //C类业务
	but_c->setFlat(true);
	but_c->setAutoFillBackground(true);
	but_c->setIcon(QPixmap("./image/opc.png"));
	but_c->setIconSize(QPixmap("./image/opc.png").size());
	QVBoxLayout *lay_but = new QVBoxLayout;
	lay_but->addWidget(but_a);
	lay_but->addWidget(but_b);
	lay_but->addWidget(but_c);
	
	QVBoxLayout *layout= new QVBoxLayout;
	//layout->addWidget(lab_title);
	//layout->addLayout(lay_but);
	layout->addWidget(lab_nu);
	layout->addLayout(lay_num);
	layout->addWidget(lab_wait);
	layout->addLayout(lay_wait);
	
	QHBoxLayout *lay_main = new QHBoxLayout(this);
	lay_main->addLayout(lay_but);
	lay_main->addLayout(layout);

	connect(but_a,SIGNAL(clicked()),this,SLOT(a_slot()));
	connect(but_b,SIGNAL(clicked()),this,SLOT(b_slot()));
	connect(but_c,SIGNAL(clicked()),this,SLOT(c_slot()));
	conn=conn_to_ser(); //连接到服务器
	if(-1==conn)
	{
		QMessageBox::information(this,tr("网络故障"),tr("网络连接失败，请检查网络连接状况！"),QMessageBox::Ok,QMessageBox::Ok);
		exit(0);
	}
}
QUHAO::~QUHAO()
{

}
void QUHAO::a_slot()
{
	int number=0;
	int wait_number=0;
	//QString *s = new QString;
	sendmsg(conn,'A','A',&number,&wait_number);
	//lab_number->setText('A'+s->setNum(number));
	//lab_wait->setText(s->setNum(wait_number));
	showdata('A',number,wait_number);
}
void QUHAO::b_slot()
{
	int number=0;
	int wait_number=0;
	//QString *s = new QString;
	sendmsg(conn,'B','A',&number,&wait_number);
	//lab_number->setText('B'+s->setNum(number));
	//lab_wait->setText(s->setNum(wait_number));
	showdata('B',number,wait_number);
}
void QUHAO::c_slot()
{
	int number=0;
	int wait_number=0;
	//QString *s = new QString;
	sendmsg(conn,'C','A',&number,&wait_number);
	//lab_numtype->setPixmap(QPixmap("./image/a.png"));
	//lab_number->setText('C'+s->setNum(number));
	//lab_wait->setText(s->setNum(wait_number));
	showdata('C',number,wait_number);
}
void QUHAO::showdata(char str,int num,int waitnum)
{
	switch(str)
	{
		case 'A':
			lab_numtype->setPixmap(QPixmap("./image/a.png"));
			break;
		case 'B':
			lab_numtype->setPixmap(QPixmap("./image/b.png"));
			break;
		case 'C':
			lab_numtype->setPixmap(QPixmap("./image/c.png"));
			break;
	}
	clear_pix();
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

	s=QString::number(waitnum);
	n=s.size();
	//QChar s1;
	switch(n)
	{
		case 5:
			s1=s[4];
			lab_wat4->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_wat4->show();
		case 4:
			s1=s[3];
			lab_wat3->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_wat3->show();
		case 3:
			s1=s[2];
			lab_wat2->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_wat2->show();
		case 2:
			s1=s[1];
			lab_wat1->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_wat1->show();
		case 1:
			s1=s[0];
			lab_wat0->setPixmap(QPixmap("./image/"+temp.setUnicode(&s1,1)+".png"));
			lab_wat0->show();
			break;
	}
}
void QUHAO::clear_pix()
{
	lab_num4->setPixmap(QPixmap(""));
	lab_num3->setPixmap(QPixmap(""));
	lab_num2->setPixmap(QPixmap(""));
	lab_num1->setPixmap(QPixmap(""));
	lab_num0->setPixmap(QPixmap(""));
	lab_wat4->setPixmap(QPixmap(""));
	lab_wat3->setPixmap(QPixmap(""));
	lab_wat2->setPixmap(QPixmap(""));
	lab_wat1->setPixmap(QPixmap(""));
	lab_wat0->setPixmap(QPixmap(""));
	lab_num4->hide();
	lab_num3->hide();
	lab_num2->hide();
	lab_num1->hide();
	lab_num0->hide();
	lab_wat4->hide();
	lab_wat3->hide();
	lab_wat2->hide();
	lab_wat1->hide();
	lab_wat0->hide();
}
