#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include <stdlib.h>
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
	server.sin_addr.s_addr=  INADDR_ANY; 
	int opt=1;

	if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))!=0) {
   		 perror("setsockopt");
    		exit(EXIT_FAILURE);
	}
	printf("\n Binding");
	int b =bind(soc,(struct sockaddr *)&server,sizeof(server)); 
	if(b){
		printf("\n Error in bind-%d",b);exit(1);	
	}
printf("\n list");
	if(listen(soc,2)){
		printf("\n Error in listen");	
	}
	
	struct sockaddr_in client_add;
	int client_adrr_len=sizeof(client_add);
	int client_sco=accept(soc,(struct sockaddr *)&client_add,(socklen_t*)&client_adrr_len);

	printf("\naccepted");
	if(client_sco<0)
		{printf("\nclient error conn"); exit(1);}
	
	char buf[30];

	printf("\nReading ");

	
	int rev_len;
	while(1){
	rev_len= read(client_sco,buf,30);
	
	printf("\nMsgclient - %s",buf);	
	char buf1[30];
	printf("\nMsgServer-");
	fgets(buf1,30,stdin);
	send(client_sco,buf1,sizeof(buf1),0);
	}
	return 0;		
}
