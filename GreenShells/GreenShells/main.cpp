#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "GameSession.h"
#include "GameWindow.h"

int CLIENT_SERVER_ARG = 1;
int PORT_ARG = 2;
int SERVER_IP_ARG = 3;

// These needs to be before main
bool SetUpServer(int argc, char* argv[])
{
	GameSession::GetGameSession().SetIsServer(true);
	if (argc == 3)
	{
		int port = atoi(argv[PORT_ARG]);
		if (port != 0)
		{
			GameSession::GetGameSession().SetPort(port);
		}
		else
		{
			std::cout << "Server requires a port number" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "server requires a port number" << std::endl;
		return false;
	}
	return true;
}

bool SetUpClient(int argc, char* argv[])
{
	GameSession::GetGameSession().SetIsServer(false);
	if (argc == 4)
	{
		GameSession::GetGameSession().SetServerIP(argv[SERVER_IP_ARG]);
		int port = atoi(argv[PORT_ARG]);
		if (port != 0)
		{
			GameSession::GetGameSession().SetPort(port);
		}
		else
		{
			std::cout << "Client requires a port number" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "client requires a server ip AND port number" << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		// We need to ask user to enter manually the data
	}
	else
	{
		// User is supposed to have written the values in the command line
		std::cout << "Starting game with arguments : " << std::endl;
		for (int i = 1; i < argc; ++i)
		{
			std::cout << argv[i] << std::endl;
		}

		//------- Client or Server -------  
		char* gameType = argv[CLIENT_SERVER_ARG];

		if (strcmp(gameType,"server") == 0)
		{
			if (!SetUpServer(argc, argv))
			{
				return 0;
			}
		} else if(strcmp(gameType, "client") == 0)
		{ 
			if (!SetUpClient(argc, argv))
			{
				return 0;
			}
			
		} else
		{
			std::cout << "Need to know if we are a \"Client\" or a \"Server\" in command line" << std::endl;
			return 0;
		}
	}

	GameWindow::GetInstance().Init(800,600);
	GameWindow::GetInstance().Show();
	return 0;
}