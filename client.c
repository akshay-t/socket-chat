#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>


int main(){
	int soc;

	struct sockaddr_in server;

	soc=socket(AF_INET,SOCK_STREAM,0);
	if(!soc)
		printf("\n Error in socket open");	
		
	server.sin_family=AF_INET;
	server.sin_port =htons(5555);
	server.sin_addr.s_addr= inet_addr("127.0.0.1"); 

	printf("\nconnecting to server");

	int s=connect(soc,(struct sockaddr *)&server,sizeof(server));
	if(s)
		printf("\n Error in connect-%d",s);	
	printf("\nconnected to server");
	send(soc,"Hello Earcth",12,0);
	
	while(1){
	char buf[30];
	
	read(soc,buf,30);

	printf("\nMsgServer - %s",buf);
	char buf1[30];
	printf("\nMsgclient -");	
	fgets(buf1,30,stdin);
	send(soc,buf1,sizeof(buf1),0);
	}
	return 0;
  
}
