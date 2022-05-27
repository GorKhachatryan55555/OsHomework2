#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <string>

int main()
{
	std::string  str1 = "Ping";
	std::string  str2 = "Pong";
	char  buffer[4];

	
	int P1[2];
	int P2[2];

	if(pipe(P1) < 0)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	if(pipe(P2) < 0)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}

	pid_t pid = fork();

	if(pid < 0)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	

	while(true)
	{
		if(pid == 0)
		{
			write(P2[1] , str1.c_str() , 4);
			wait(NULL);
			sleep(1);
			read(P1[0] , buffer , 4);
			sleep(1);
			std::cout << std::string(buffer , strlen(buffer)) << std::endl;
		}
		else
		{
			write(P1[1] , str2.c_str() , 4);
			read(P2[0] , buffer , 4);
			sleep(1);
			std::cout << std::string(buffer , strlen(buffer)) << std::endl;
		}
	}

}
