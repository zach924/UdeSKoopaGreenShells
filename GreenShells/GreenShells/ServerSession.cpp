#include <thread>

#include "ServerSession.h"

ServerSession::ServerSession()
	:m_dispatcher(nullptr), m_rpcServerManager(nullptr)
{

}

void ServerSession::run()
{
	while (true)
	{
		while (!m_worldState.AreAllPlayerReady())
		{
			m_dispatcher->Dispatch();
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		m_worldState.NotifyNewTurn();
	}
}

ServerSession::~ServerSession()
{

}

void ServerSession::StartServer(int port)
{
	//Prepare WorldState
	m_worldState.PrepareGame();

	//StartListening
	m_rpcServerManager = new RPCManager(port);
	m_rpcServerManager->SetEventQueue(&m_events);
	m_rpcServerManager->StartListening();

	m_dispatcher = new RPCDispatcher();
	m_dispatcher->SetEventQueue(&m_events);
	m_dispatcher->SetWorldState(&m_worldState);

	m_serverSessionThread = new std::thread(&ServerSession::run, this);
}