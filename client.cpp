#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <error.h>

#include <cstdio>

#include <string>
#include <vector>

#include "protocol.h"


using std::string;
using std::vector;


int main() {
	int sock;
	struct sockaddr_in addr;

	sock = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(protocol::port_number);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (::connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("connect");
		exit(2);
	}
	
	string message = "Hello!";
	vector<char> buf(message.size());
	::send(sock, message.c_str(), message.size(), 0);
	::recv(sock, &buf[0], buf.size(), 0);
	printf("Received:%s\n", &buf[0]);
	close(sock);
	return 0;
}
