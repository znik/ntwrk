CXX = g++
CFLAGS = -Wall
CLIBS =

all: server client

client:
	$(CXX) $(SOURCES) client.cpp  -o $@ $(CFLAGS) $(CLIBS)

server:
	$(CXX) $(SOURCES) server.cpp  -o $@ $(CFLAGS) $(CLIBS)

clean:
	rm client
	rm server

