#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>	
#include <sys/socket.h> 
#include <netinet/in.h>	
#include "client.h"

#define SECOND 1000  //sleep() function use millisecond
#define MAXCHAR 255  //max char of filename
#define BUF_SIZE 1000 

int main(int argc,char* argv[])
{
	char read_buffer[BUF_SIZE];
	char* main_buffer = NULL;
	int main_count = 0;//not include '\0'
	char ip[15];  //if "999.999.999.999" 
	int port; 
	char filename[MAXCHAR];

	check_args(argc,argv,ip,&port);

	fprintf(stderr,"saveas filename: ");
	fscanf(stderr,"%s",filename);
	while (1)
	{
		//create a socket
		int sock = socket(AF_INET,SOCK_STREAM,0);

		//bind the socket to the IP and port
		struct sockaddr_in serv_addr;

		memset(&serv_addr,0,sizeof(serv_addr));  //each byte is padded with 0

		serv_addr.sin_family = AF_INET;  //use IPv4 address
		serv_addr.sin_addr.s_addr = inet_addr(ip); //specific IP address
		serv_addr.sin_port = htons(port);  //port

		while ( (connect(sock, (struct sockaddr*)&serv_addr ,sizeof(serv_addr) )) != 0)
		{ 
			fprintf(stderr,"connect error: ip=%s, port=%d. retry...\n",ip, port);
			sleep(3 * SECOND);
			//if network broke
		}
		fprintf(stderr,"success\n");


		//read the server returns data
		int count;
		memset(read_buffer,0,sizeof(read_buffer));
		while((count = read(sock,read_buffer,sizeof(read_buffer)-1 )) > 0){
			main_count += count;
			main_buffer = realloc(main_buffer, main_count + 1); //+1='\0'

			strcat(main_buffer,read_buffer);

			memset(read_buffer,0,sizeof(read_buffer));
		}
		//close socket
		close(sock);
		
		//write to file
		FILE* fp;
		while ((fp = (fopen(filename,"a"))) == NULL){
			fprintf(stderr,"Error: target file cannot open \n");
			fprintf(stderr,"New file name: ");
			fscanf(stderr,"%s",filename);
		}
		fprintf(stderr,"opened file \n");
		fputs(main_buffer,fp);

		free(main_buffer);
		main_buffer = NULL;
		main_count = 0;
		fclose(fp);
		sleep(1 * SECOND);
	}

	return 0;
}
	
