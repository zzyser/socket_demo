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
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		printf("socket error\n");
		exit(1);
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8080);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int ret =connect(sockfd,(const struct sockaddr *)&addr,sizeof(addr));
	if(ret<0){
		printf("connect erron");
		exit(1);
	}
	printf("connect success\n");
	char send_name[21];
	char send_line[256];
	char send_buf[4096];
	while(1){
		memset(send_buf,0,sizeof(send_buf));
		memset(send_name,0,sizeof(send_name));
		memset(send_line,0,sizeof(send_line));

		printf("send file`s name:");
		scanf("%s",send_name);
		if(!strncmp(send_name,"+++",3))
			break;
		fp = fopen(send_name,"r");
		if(fp==NULL){
			printf("file open error\n");
			exit(1);
		}
		printf("file: %s open success,sending..\n",send_name);
		while(!feof(fp)){
			fscanf(fp,"%s",send_line);
			printf("%s\n",send_line);
			strcat(send_buf,send_line);
			strcat(send_buf,"\n");
			memset(send_line,0,sizeof(send_line));
		}
		int s=send(sockfd,send_buf,4096,0);
		if(s<0){
			printf("send error\n");
			exit(1);
		}

	
	}
	printf("client close\n");
	fclose(fp);
	close(sockfd);
	
	return 0;
}
