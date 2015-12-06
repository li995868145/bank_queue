#ifndef _CONN_H_
#define _CONN_H_
#include "../msgtype.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int crelink()
{
	int sd=socket(AF_INET,SOCK_STREAM,0); //创建socket
	if(-1==sd) //判断socket是否创建成功
	{
		perror("Socket 创建失败!\n"); //如果创建失败打印出错信息
		return -1; //退出程序
	}
	struct sockaddr_in addr;
	addr.sin_family=AF_INET; //协议簇
	addr.sin_port=htons(8010); //端口
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
	printf("create socket ok\n");
	return sd;
}

int linkacc(int sd)
{
	struct sockaddr_in form;
	memset(&form,0,sizeof(form));
	socklen_t len=sizeof(struct sockaddr_in);
	printf("wait link\n");
	int sd2=accept(sd,(struct sockaddr*)&form,&len); //等待建立连接
	if(-1==sd2)
	{
		perror("客户端连接失败\n");
		return -1;
	}
	printf("link ok\n");
	return sd2;
}

int linkrecv(int sd2,char* str)
{
	struct MSG_SEND msg_buf;
	printf("wait msg\n");
   if(0==recv(sd2,&msg_buf,sizeof(struct MSG_SEND),0))//判断连接是否正常
	{
		return -1;	
	}  
	printf("%c\t%c\t%d\n",msg_buf.ope_type,msg_buf.sig_type,msg_buf.number);
	*str=msg_buf.ope_type;
	return msg_buf.number;
}

#endif
