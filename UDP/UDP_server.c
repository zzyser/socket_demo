#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
int main()
{
	int len;
	char buf[100] = {0};
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr;
	int addr_len = sizeof(socklen_t);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(fd, (struct sockaddr*)&addr, sizeof(addr));
	while(1)
	{		
		len = recvfrom(fd, buf, 100, 0, (struct sockaddr*)&addr, &addr_len);
		printf("recv(%d):%s\n", len, buf);
	}
	return 0;
}
