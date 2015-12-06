#ifndef _JIAOHAO_H_
#define _JIAOHAO_H_
#include<QLabel>
#include<QPushButton>
#include<QLayout>
#include<QDialog>

class JIAOHAO :public QDialog
{
	Q_OBJECT
public:
	JIAOHAO();
	~JIAOHAO();
	QLabel *lab_title;
	QLabel *lab_nu;
	QLabel *lab_number;
	QLabel *lab_wa;
	QLabel *lab_wait;
	QPushButton *but_a;
	QPushButton *but_b;
	QPushButton *but_c;
	int conn; //socket连接描述符
	int conn2; //led socket
public slots:
	void a_slot(); //A类业务槽函数
	void b_slot(); //B类业务槽函数
	void c_slot(); //C类业务槽函数
private:
	QLabel *lab_num0;
	QLabel *lab_num1;
	QLabel *lab_num2;
	QLabel *lab_num3;
	QLabel *lab_num4;

	QLabel *lab_wat0;
	QLabel *lab_wat1;
	QLabel *lab_wat2;
	QLabel *lab_wat3;
	QLabel *lab_wat4;
	void clear_pix();
	void showdata(char str,int num,int waitnum); //显示取得号码到屏幕
};

#endif
