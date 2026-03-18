#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
int main (int argc, char* argv[])
{
	if ( argc != 2 )
	{
	printf("Usage: ipshow [hostname]\n");
	return 2;
	}
	char ipstr [INET6_ADDRSTRLEN];
	int status;
	struct addrinfo hints;
	struct addrinfo* result;
	struct addrinfo* p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ( (status = getaddrinfo(argv[1], "80", &hints, &result)) != 0 )
	{
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
	}

	printf("IP addresses for %s .\n",argv[1]);
	for (p = result; p != NULL; p = p->ai_next)
	{
		void* ptoaddr;
		struct sockaddr_in* v4;
		struct sockaddr_in6* v6;
		char* ip_ver;
		if ( p->ai_family == AF_INET )
		{
			v4 = (struct sockaddr_in*)p->ai_addr;
			ptoaddr = &(v4->sin_addr);
			ip_ver = "IPV4";
		}
		else
		{
			v6 = (struct sockaddr_in6*)p->ai_addr;
			ptoaddr = &(v6->sin6_addr);
			ip_ver = "IPV6";
		}
		inet_ntop(p->ai_family,ptoaddr,ipstr,sizeof(ipstr));
		printf("%s: %s\n",ip_ver,ipstr);
	}
	freeaddrinfo(result);
	return 0;
}

