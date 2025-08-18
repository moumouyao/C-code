#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <net/if.h>
    struct ip_mreqn{
        struct in_addr imr_multiaddr;  //组播地址
        struct in_addr imr_address;     //本地地址    INADDR_ANY
        int imr_ifindex;    //物理地址    物理硬件id函数  if_nametoindex("ens33")                
    };

int main(){
	
	int num = 1;
	//创建套接字
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1){
		perror("socket error");
		return -1;
	}
	//加入组播
	struct ip_mreqn val;
	val.imr_multiaddr.s_addr = inet_addr("225.0.0.1");
	val.imr_address.s_addr = INADDR_ANY;
	val.imr_ifindex = if_nametoindex("ens33");
	setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &val, sizeof(val));
	//发送信息
	char r_buf[128] = {0};
	//绑定	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("225.0.0.1");
	if(bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1){
		perror("bind error");
		return -1;
	}
	struct sockaddr_in addr_r;
	socklen_t len = sizeof(addr_r);
	while(1){
		printf("发送的信息: %s\n", r_buf);
		memset(r_buf, 0, sizeof(r_buf));
		recvfrom(fd, r_buf, sizeof(r_buf), 0, (struct sockaddr *)&addr_r, &len);
		sleep(1);
		num ++;
	}
	return 0;
}
