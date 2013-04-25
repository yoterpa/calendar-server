#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream>
#include "fileManager.h"
#include <signal.h>
#include "macros.h"

using namespace std;

void queryHandling(int);
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void intHandler(int waste=1)
{
    error("\nThe user pressed Ctrl-C, so terminating...\n");
}
int main(int argc, char *argv[])
{
	signal(SIGINT, intHandler);
	int sockfd, newsockfd, portno, pid;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int mode;
	if (argc < 3)
	{
		cout<<"ERROR, no port provided. Usage is "<<argv[0]<<" ./server <port-number> <server mode>\n";
		cout<<"Server mode can be one of the following:\n1: Iterative (one at a time, in while loop)\n2. Multi-threaded\n3. Using select() function\n";
		exit(1);
	}
	mode = atoi ( argv[2] );
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	

	int reuseYES=1;
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuseYES,sizeof(int)) == -1)
	{
		perror("setsockopt: Could not clear the port that was being used earlier.");
		exit(1);
	}
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	
	if ( mode == 1 ){
		while (true){
			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
			if (newsockfd < 0) 
				error("ERROR on accept");
			queryHandling ( newsockfd );
			close(newsockfd);
		}
	}
	if ( mode == 2 ){
		signal(SIGCHLD,SIG_IGN);
		while (1) {
			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
			if (newsockfd < 0) 
				error("ERROR on accept");
			pid = fork();
			if (pid < 0)
				error("ERROR on fork");
			if (pid == 0)  {
				close(sockfd);
				queryHandling (newsockfd);
				exit(0);
			}
			else close(newsockfd);
		}
	}
	if ( mode == 3 ){
			fd_set master;
			fd_set read_fds;
			int fdmax;
			char buffer[2560];
			FD_ZERO(&master);
			FD_ZERO(&read_fds);
			FD_SET ( sockfd , &master );
			
			fdmax = sockfd;
			while(1){
				read_fds = master;
				if ( select ( fdmax+1 , &read_fds , NULL , NULL , NULL) == -1)
					error("select() function failed \n");

				
				for ( int i = 0; i <= fdmax; i++ ){
					if ( FD_ISSET ( i , &read_fds ) ){
						if ( i == sockfd ){
							
							cout << "Ready to accept a new connection\n";
							clilen = sizeof cli_addr;
							
							newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
							if (newsockfd < 0)
								error("Select() Server could not accept new connection\n ");
							else {
								FD_SET (newsockfd , &master );
								if ( newsockfd > fdmax )
									fdmax = newsockfd;
							}
						}
						else {
							
							bzero(buffer,2560);

							
							int rdatalen = recv ( i, buffer, 2559, 0);
							if ( rdatalen <= 0 ) {
								
								if (rdatalen == 0) {
									printf("selectserver: socket %d hung up\n", i);
								}
								else
									error("Receiving error:- Did not receive from client when expected");
								close(i);
								FD_CLR(i, &master);
							}
							else {
								stringstream ss;
								ss << buffer;
								string query = ss.str();
								string output = execQuery(query);

								char writeOut[2560];
								bzero(writeOut,2560);
								strcpy ( writeOut , output.c_str() );
								int n = write(i,writeOut,strlen(writeOut));

								if (n < 0)
									error("ERROR writing to socket");
							}
						} 
					}
				} 
			} 
	} 
	if ( mode != 1 || mode != 2 || mode != 3 ){ 
		close(sockfd);
		cout<<"The argument for mode is wrong. \nServer mode can be one of the following:\n1: Iterative (one at a time, in while loop)\n2. Multi-threaded\n3. Using select() function\n" ;
		exit (1);
	}
	close(sockfd);
	return 0; 
}

void queryHandling (int sock)
{
	int n;
	char buffer[2560];

	bzero(buffer,2560);
	n = read(sock,buffer,2559);
	if ( n < 0 )
		error("ERROR reading from socket");

	stringstream convert;
	convert << buffer;
	string query = convert.str();

	string output = execQuery(query);

	char writeOut[2560];
	bzero(writeOut,2560);
	strcpy ( writeOut , output.c_str() );
	n = write(sock,writeOut,strlen(writeOut));
	if (n < 0)
		error("ERROR writing to socket");

	if ( string::npos != output.find(totalLines) ){
		unsigned pos = output.find(" ");
		int numLines = atoi(output.substr(0,pos).c_str());
		for ( int i=1; i<=numLines; i++ ){
			bzero(buffer,2560);
			n = read(sock,buffer,2559);
			stringstream convert;
			convert << buffer;
			string getLineQuery = convert.str();

			string output = execQuery(getLineQuery);
			bzero(writeOut,2560);
			strcpy ( writeOut , output.c_str() );
			n = write(sock,writeOut,strlen(writeOut));
			if (n < 0)
				error("ERROR writing to socket");
			}
			bzero(writeOut,2560);
	}
}
