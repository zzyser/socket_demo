#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
	FILE *fp=NULL;
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	addr.sin_port=htons(8080);

	int socket_server = socket(PF_INET,SOCK_STREAM,0);
	if(socket_server < 0){
		printf("create socket failed\n");
		exit(1);
	}
	int on=1;
	setsockopt(socket_server,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	int Bind=bind(socket_server,(struct sockaddr*)&addr,sizeof(addr));
	if(Bind<0){
		printf("bind error\n");
		exit(1);
	}
	int l = listen(socket_server,10);
	if(l<0){
		printf("server listen failed\n");
		exit(1);
	}
	printf("server listenning...\n");
	struct sockaddr_in client_addr;
	socklen_t length=sizeof(client_addr);
	int new_socket=accept(socket_server,(struct sockaddr*)&client_addr,&length);
	if(new_socket<0){
		printf("server accept error\n");
		exit(1);
	}
	printf("listen success,new_socket=%d\n",new_socket);
	printf("client ip = %s\n",inet_ntoa(client_addr.sin_addr));
	printf("client port = %d\n",ntohs(client_addr.sin_port));
	char buf[4096];
	char file_name[]="socket_file01";
	while(1){
		memset(buf,0,sizeof(buf));
	
		printf("waiting for file..\n");
		length = recv(new_socket,buf,4096,0);
		if(length>0){
			printf("recv client_file success\n");
		}else{
			printf("connect error\n");
			break;
		}
		fp = fopen(file_name,"w");
		if(fp==NULL){
			printf("file error\n");
		}else{
			printf("file open success");
			
			fprintf(fp,"%s",buf);
			
			printf("file transfer finished\n");
		}
		if(file_name[12]<57){ 		//'9' = (ascII) 57
			file_name[12]++;
		}else{
			file_name[11]++;
			file_name[12]='0';
		}
	}

	close(new_socket);
	close(socket_server);
	fclose(fp);

	return 0;
}
