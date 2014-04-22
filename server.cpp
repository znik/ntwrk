#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <error.h>
#include <netdb.h>


#include <vector>

#include "protocol.h"


using std::vector;


void get_peer_data(int peer_sock_fd) {
	struct sockaddr_storage addr;
	vector<char> ip(INET6_ADDRSTRLEN);
	int port;

	socklen_t len = sizeof(addr);
	if (0 > getpeername(peer_sock_fd, (struct sockaddr*)&addr, &len)) {
		perror("getpeername");
		exit(6);
	}
	if (AF_INET != addr.ss_family) {
		return;
	}
	
	struct sockaddr_in *s = (struct sockaddr_in *)&addr;
	inet_ntop(AF_INET, &s->sin_addr, &ip[0], ip.size());
	printf("ip: %s\n", &ip[0]);
}


int main() {
	int sock, listener;
	struct sockaddr_in addr;
	vector<char> buf(1024);
	int bytes_read;

	listener = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listener < 0) {
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(protocol::port_number);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (::bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(2);
	}

	listen(listener, 1);

	printf("waiting for connections...\n");

	while(1) {
		sock = ::accept(listener, NULL, NULL);
		if (sock < 0) {
			perror("accept");
			exit(3);
		}

		get_peer_data(sock);


		while(1) {
			bytes_read = ::recv(sock, &buf[0], buf.size(), 0);
			if (bytes_read <= 0)
				break;
			printf("Sending back %d bytes..\n", bytes_read);
			::send(sock, &buf[0], bytes_read, 0);
		}
		close(sock);
	}
	return 0;
}

