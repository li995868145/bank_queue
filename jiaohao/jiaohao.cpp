#include "jiaohao.h"
#include "conn.h"
#include <QMessageBox>
#include <QString>

JIAOHAO::JIAOHAO()
{
	QPalette p;
	p.setColor(QPalette::Active,QPalette::Window,QColor(80,109,218));
	p.setColor(QPalette::Inactive,QPalette::Window,QColor(80,109,218));
	p.setColor(QPalette::Active,QPalette::Button,QColor(80,109,218));
	p.setColor(QPalette::Inactive,QPalette::Button,QColor(80,109,218));
	setPalette(p);
	setWindowTitle(tr("叫号端"));
	lab_title = new QLabel(tr("排队取号系统－－－叫号处"));
	lab_number = new QLabel();
	lab_nu = new QLabel;
	lab_nu->setPixmap(QPixmap("./image/dqhm.png"));
	lab_wait = new QLabel();
	lab_wa = new QLabel;
	lab_wa->setPixmap(QPixmap("./image/dengdai.png"));
	but_a = new QPushButton;
	but_a->setFlat(true);
	but_a->setIcon(QPixmap("./image/ja.png"));
	but_a->setIconSize(QPixmap("./image/ja.png").size());
	but_b = new QPushButton;
	but_b->setFlat(true);
	but_b->setIcon(QPixmap("./image/jb.png"));
	but_b->setIconSize(QPixmap("./image/jb.png").size());
	but_c = new QPushButton;
	but_c->setFlat(true);
	but_c->setIcon(QPixmap("./image/jc.png"));
	but_c->setIconSize(QPixmap("./image/jc.png").size());

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
	lay_num->addWidget(lab_nu);
	lay_num->addWidget(lab_number);
	lay_num->addWidget(lab_num0);
	lay_num->addWidget(lab_num1);
	lay_num->addWidget(lab_num2);
	lay_num->addWidget(lab_num3);
	lay_num->addWidget(lab_num4);
	lay_num->addStretch();
	QHBoxLayout *lay_wa = new QHBoxLayout;
	lay_wa->addWidget(lab_wa);
	//lay_wa->addWidget(lab_wait);
	lay_wa->addWidget(lab_wat0);
	lay_wa->addWidget(lab_wat1);
	lay_wa->addWidget(lab_wat2);
	lay_wa->addWidget(lab_wat3);
	lay_wa->addWidget(lab_wat4);
	lay_wa->addStretch();
	QVBoxLayout *layout= new QVBoxLayout(this);
	//layout->addWidget(lab_title);
	layout->addWidget(but_a);
	layout->addWidget(but_b);
	layout->addWidget(but_c);
	layout->addLayout(lay_num);
	layout->addLayout(lay_wa);
	layout->addStretch();

	connect(but_a,SIGNAL(clicked()),this,SLOT(a_slot()));
	connect(but_b,SIGNAL(clicked()),this,SLOT(b_slot()));
	connect(but_c,SIGNAL(clicked()),this,SLOT(c_slot()));
	conn=conn_to_ser(); //连接到服务器
	if(-1==conn)
	{
		QMessageBox::information(this,tr("网络故障"),tr("网络连接失败，请检查网络连接状况！"),QMessageBox::Ok,QMessageBox::Ok);
		exit(0);
	}

	conn2=conn_to_led(); //连接到服务器
	if(-1==conn2)
	{
		QMessageBox::information(this,tr("网络故障"),tr("LED连接失败，请检查网络连接状况！"),QMessageBox::Ok,QMessageBox::Ok);
	}
}
JIAOHAO::~JIAOHAO()
{

}
void JIAOHAO::a_slot()
{
	int number=0;
	int wait_number=0;
	int enab=0;
	//QString *s = new QString;
	sendmsg(conn,'A','B',&number,&wait_number,&enab);
	if(enab==3)
	{
		lab_number->setText(tr("无人办理业务！"));
		clear_pix();
	}else
	{
		//lab_number->setText('A'+s->setNum(number));
		showdata('A',number,wait_number);
		sendtoled(conn2,'A','L',number);
	}
	//lab_wait->setText(s->setNum(wait_number));
}
void JIAOHAO::b_slot()
{
	int number=0;
	int wait_number=0;
	int enab=0;
	//QString *s = new QString;
	sendmsg(conn,'B','B',&number,&wait_number,&enab);
	if(enab==3)
	{
		lab_number->setText(tr("无人办理业务！"));
		clear_pix();
	}else
	{
		//lab_number->setText('B'+s->setNum(number));
		showdata('B',number,wait_number);
		sendtoled(conn2,'B','L',number);
	}
	//lab_wait->setText(s->setNum(wait_number));
}
void JIAOHAO::c_slot()
{
	int number=0;
	int wait_number=0;
	int enab=0;
	//QString *s = new QString;
	sendmsg(conn,'C','B',&number,&wait_number,&enab);
	if(enab==3)
	{
		lab_number->setText(tr("无人办理业务！"));
		clear_pix();
	}else
	{
		//lab_number->setText('C'+s->setNum(number));
		showdata('C',number,wait_number);
		sendtoled(conn2,'C','L',number);

	}
	//lab_wait->setText(s->setNum(wait_number));
}

void JIAOHAO::showdata(char str,int num,int waitnum)
{
	switch(str)
	{
		case 'A':
			lab_number->setPixmap(QPixmap("./image/a.png"));
			break;
		case 'B':
			lab_number->setPixmap(QPixmap("./image/b.png"));
			break;
		case 'C':
			lab_number->setPixmap(QPixmap("./image/c.png"));
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
void JIAOHAO::clear_pix()
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
			lab_wat4->setPixmap(QPixmap(""));
			lab_wat4->hide();
			lab_wat3->setPixmap(QPixmap(""));
			lab_wat3->hide();
			lab_wat2->setPixmap(QPixmap(""));
			lab_wat2->hide();
			lab_wat1->setPixmap(QPixmap(""));
			lab_wat1->hide();
			lab_wat0->setPixmap(QPixmap(""));
			lab_wat0->hide();
}
