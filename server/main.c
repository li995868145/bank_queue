#include "../msgtype.h"
#include<sys/types.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <pthread.h>
void* task(void* p);
struct SER_MSG a_data={0}; //A类数据
struct SER_MSG b_data={0}; //B类数据
struct SER_MSG c_data={0}; //C类数据
int main()
{
	int sd=socket(AF_INET,SOCK_STREAM,0); //创建socket
	if(-1==sd) //判断socket是否创建成功
	{
		perror("Socket 创建失败!\n"); //如果创建失败打印出错信息
		return -1; //退出程序
	}
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET; //协议簇
	addr.sin_port=htons(8020); //端口
	addr.sin_addr.s_addr=inet_addr("172.17.37.254"); //IP
	int res=bind(sd,(struct sockaddr*)&addr,sizeof(addr)); //绑定socket
	if(-1==res)
	{
		perror("绑定端口失败!\n");
		return -1;
	}
	int li=listen(sd,100); //开始监听
	if(-1==li)//判断监听是否成功
	{
		perror("监听失败\n");
		return -1;
	}
	while(1)
	{
		struct sockaddr_in form;
		memset(&form,0,sizeof(form));
		int len=sizeof(struct sockaddr_in);
		int sd2=accept(sd,(struct sockaddr*)&form,&len); //等待建立连接
		if(-1==sd2)
		{
			perror("客户端连接失败\n");
			continue;
		}
		pthread_t t1; //创建进程维护建立的连接
		//printf("ptherad create dddok!\n");
		//int pth=pthread_create(&t1,NULL,task((void*)&sd2),0);
		int pth=pthread_create(&t1,NULL,task,(void*)&sd2);
		//printf("ptherad create ok11!\n");
		if(0!=pth)
		{
			perror("创建线程失败!\n");
			exit(-1);
		}
		//printf("ptherad create ok!\n");
	}
}


void* task(void* p)
{
	int sd2=*(int*)p;
	while(1)
    	{
			struct MSG_SEND msg_buf;
        if(0==recv(sd2,&msg_buf,sizeof(struct MSG_SEND),0))//判断连接是否正常
			{
				close(sd2); //关闭socket连接
				break;
			}      
			//printf("ope_type:%c\n",msg_buf.ope_type);
			//printf("sig_type:%c\n",msg_buf.sig_type);
			switch(msg_buf.sig_type)
			{
				case 'A':    //取号
					switch(msg_buf.ope_type)
					{
						case 'A':  //A类作业类型取号
							a_data.sum++; //排队人数加1
							msg_buf.number=a_data.sum;
							msg_buf.wait_num=a_data.wnum;
							a_data.wnum++;//等待人数加1
							break;
						case 'B': //B类作业类型取号
							b_data.sum++; //排队人数加1
							msg_buf.number=b_data.sum;
							msg_buf.wait_num=b_data.wnum;
							b_data.wnum++;//等待人数加1
							break;
						case 'C': //C类作业类型取号
							c_data.sum++; //排队人数加1		
							msg_buf.number=c_data.sum;
							msg_buf.wait_num=c_data.wnum;
							c_data.wnum++;//等待人数加1
							break;
						default:  //其他
							break;  
					}
					send(sd2,&msg_buf,sizeof(struct MSG_SEND),0); //返回取号信息给取号端
					break;
				case 'B':    //叫号
					switch(msg_buf.ope_type)
					{
						case 'A':  //A类作业类型叫号
							if(a_data.wnum==0)
							{
								msg_buf.enab=3; 
							}else
							{
								a_data.num++; //叫号人数加1
								a_data.wnum--;//等待人数减1
								msg_buf.number=a_data.num;
								msg_buf.wait_num=a_data.wnum;
							}
							break;
						case 'B': //B类作业类型叫号
							if(b_data.wnum==0)
							{
								msg_buf.enab=3;
							}else
							{
								b_data.num++; //叫号人数加1
								b_data.wnum--;//等待人数减1
								msg_buf.number=b_data.num;
								msg_buf.wait_num=b_data.wnum;
							}
							break;
						case 'C': //C类作业类型叫号
							if(c_data.wnum==0)
							{
								msg_buf.enab=3;
							}else
							{	
								c_data.num++; //叫号人数加1
								c_data.wnum--;//等待人数减1
								msg_buf.number=c_data.num;
								msg_buf.wait_num=c_data.wnum;
							}
							break;
						default:  //其他
							break;  
					}
					send(sd2,&msg_buf,sizeof(struct MSG_SEND),0); //返回取号信息给取号端
				break;
				default:
				break;
			}				
    	}
	pthread_exit;//终止线程
}

