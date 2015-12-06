/*
	定义数据结构
*/
#ifndef _MSGTYPE_H_
#define _MSGTYPE_H_
struct MSG_SEND //通信结构体
{
	char ope_type; //业务类型 ： A B C D。。。。
	char sig_type; //信号类型 ：A：取号 ，B：叫号
	int number; //排队数据
	int wait_num; //等待人数
	int enab;  // 当无人办理业务时将此值设为一个有效值，发给叫号端。 
};
struct SER_MSG //服务器存储队列的结构
{
	int sum; //总人数
	int num; //以叫号人数
	int wnum;//等待人数
};

#endif


