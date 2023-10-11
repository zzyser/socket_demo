#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
int main()
{
	int i;
	char buf[100] = "Hello, my socket...\n";
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = inet_addr("169.254.1.230");
	while(1)
	{
		sendto(fd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
		sleep(1);
	}
	return 0;
}
