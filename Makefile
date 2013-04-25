all:
	g++ -Wall client.cpp fileManager.cpp -o client
	g++ -Wall server.cpp fileManager.cpp -o server
