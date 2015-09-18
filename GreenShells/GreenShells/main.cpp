#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "GameSession.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		// We need to ask user to enter manually the data
	}
	else
	{
		// User is supposed to have written the values in the command line

		//------- Client or Server -------  
		if (strcmp(argv[1],"Server"))
		{
			// We are Server
			SetUpServer(argc,argv);
		} else if(strcmp(argv[1], "Client"))
		{ 
			// Wer are Client
			SetUpClient(argc, argv);
			
		} else
		{
			std::cout << "Need to know if we are a \"Client\" or a \"Server\" in command line" << std::endl;
			return 0;
		}
	}
	return 0;
}

void SetUpServer(int argc, char* argv[])
{
	GameSession::GetGameSession().SetIsServer(true);
}

void SetUpClient(int argc, char* argv[])
{
	GameSession::GetGameSession().SetIsServer(false);
}