#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./client.h"

//#define ADDR_GPL "./LICENSE"
#define P_HELP 3

void check_args(int argc,char* argv[],char* ip,int* port)
{
	if (argc > 1){
		switch (argc){
			case 2: {
					if ((strncmp(argv[1],"-help",5)) == 0) 
						print_help();
					if ((strncmp(argv[1],"-license",8) == 0) || ((strncmp(argv[1],"-gpl",4) == 0))) 
						print_license();
					
					strcpy(ip,argv[1]);
					break;
			}
			case 3: {
					strcpy(ip,argv[1]);
					*port = atoi(argv[2]);
					break;
			}
			default:{
					fprintf(stderr,"type -help for help\n");
			}
		}
	}
	else{
		strcpy(ip,"127.0.0.1");  //need change this.
		*port = 4601;
	}	 
}


void print_help()
{
	printf("Usage: <exe> \"ip\" \"port\"\n");
	printf("if you want , just type <exe>,but you need to change the default value.\n");
	printf("You can find more instructions on README.md.\n");
	printf("If you want to know more of mindray, browse \"https://www.mindray.com\".\n");
	exit(P_HELP);
}

void print_license()
{
	/*
		FILE* fp;
		if ((fp = fopen(ADDR_GPL,"r")) == NULL){
			printf("Error: cannot open %s",ADDR_GPL);
			exit(1);
		}
		char buffer[100];
		while ((fgets(buffer,101,fp)) != NULL)
		{
			fputs(buffer,stderr);
		}
		fclose(fp);
		exit(0);
	*/
	system("less ./LICENSE");
	exit(P_HELP);
}
