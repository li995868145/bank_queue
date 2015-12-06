#ifndef _LED_H_
#define _LED_H_
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QThread> 
#include <QCloseEvent>
#include <QPixmap>
//线程
class Thread :public QThread
{
	Q_OBJECT
public:
	Thread();
	QString *s;
	QLabel *lab;
	char str;
	void run();
public : signals:
	void showdat(char,int);

};
class LED:public QDialog
{
	Q_OBJECT
public:
	LED();
	~LED();
	QLabel *lab_f;
	QLabel *lab_e;
	QLabel *lab_led;
	Thread  thr;
	QLabel *lab_num0;
	QLabel *lab_num1;
	QLabel *lab_num2;
	QLabel *lab_num3;
	QLabel *lab_num4;
protected:
	void closeEvent(QCloseEvent *event);
	void clear_pix();
public slots:
	void showdata(char str,int num); //显示取得号码到屏幕
};

#endif
