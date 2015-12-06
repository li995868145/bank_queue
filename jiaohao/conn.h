#include "../msgtype.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int conn_to_ser() //创建TCP连接
{
    //创建socket
    int sd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==sd)
    {
        perror("socket create failed\n");
			return -1;
    }
    //准备地址
    struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8020);
    addr.sin_addr.s_addr=inet_addr("172.17.37.254");
    
    //绑定
    int res=connect(sd,(struct sockaddr*)&addr,sizeof(addr));
    if(-1==res)
    {
        perror("绑定失败\n");
			return-1;
    }
	return sd;
}

void sendmsg(int sd,char o_type,char s_type,int* num,int* w_num,int* enab)
{
	struct MSG_SEND msg_buf;
	msg_buf.ope_type=o_type;
	msg_buf.sig_type=s_type;
	send(sd,&msg_buf,sizeof(struct MSG_SEND),0);
	recv(sd,&msg_buf,sizeof(struct MSG_SEND),0);
	*num=msg_buf.number;
	*w_num=msg_buf.wait_num;
	*enab=msg_buf.enab;
}


int conn_to_led() //创建TCP连接
{
    //创建socket
    int sd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==sd)
    {
        perror("socket create failed\n");
			return -1;
    }
    //准比地址
    struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8010);
    addr.sin_addr.s_addr=inet_addr("172.17.37.254");
    
    //绑定
    int res=connect(sd,(struct sockaddr*)&addr,sizeof(addr));
    if(-1==res)
    {
        perror("绑定失败\n");
			return-1;
    }
	return sd;
}
void sendtoled(int sd,char o_type,char s_type,int num)
{
	struct MSG_SEND msg_buf;
	msg_buf.ope_type=o_type;
	msg_buf.sig_type=s_type;
	msg_buf.number=num;
	send(sd,&msg_buf,sizeof(struct MSG_SEND),0);
}

