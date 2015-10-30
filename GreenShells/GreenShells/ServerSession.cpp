#include <thread>
#include <sstream>
#include <chrono>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <iostream>

#include "ServerSession.h"
#include "Player.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif
using namespace std::chrono;

ServerSession::ServerSession()
	:m_dispatcher(nullptr), m_rpcServerManager(nullptr), m_worldState(false), m_isStopped(false)
{

}

void ServerSession::run()
{
	while (true)
	{
		while (!m_worldState.AreAllPlayerReady())
		{
			//30 ticks / second
			auto before = system_clock::now();

			//Server is done.
			if (m_isStopped)
			{
				return;
			}

			//Check for disconnects
			auto players = m_rpcServerManager->GetDisconnectedPlayers();
			for (auto player : players)
			{
				m_worldState.GetPlayer(player).SetIsDisconnected();
			}

			if (m_dispatcher->Dispatch())
			{
				Replicate();
			}

			auto after = system_clock::now();
			std::this_thread::sleep_for(milliseconds(33) - duration_cast<milliseconds>(after - before));
		}

		m_worldState.NotifyNewTurn();
		Replicate();
	}
}

ServerSession::~ServerSession()
{

}

void ServerSession::StartServer(int port)
{
	//Prepare WorldState
	m_worldState.PrepareLocalGame();

	//StartListening
	m_rpcServerManager = new RPCManager(port);
	m_rpcServerManager->SetEventQueue(&m_events);
	m_rpcServerManager->StartListening();

	m_dispatcher = new RPCDispatcher();
	m_dispatcher->SetEventQueue(&m_events);
	m_dispatcher->SetWorldState(&m_worldState);

	m_serverSessionThread = new std::thread(&ServerSession::run, this);
}

void ServerSession::StopServer()
{
	m_isStopped = true;
	m_serverSessionThread->join();
	delete m_rpcServerManager;
	m_rpcServerManager = nullptr;
	delete m_dispatcher;
	m_dispatcher = nullptr;
}

void ServerSession::Replicate()
{
	std::stringstream ss;
	boost::property_tree::write_xml(ss, m_worldState.Serialize());
	std::stringstream data;
	auto size = static_cast<int>(ss.str().size());
	data.write(reinterpret_cast<char*>(&size), sizeof(size));
	data.write(ss.str().c_str(), size);
	m_rpcServerManager->SendToClients(data.str());
}

int ServerSession::AddPlayer(std::string playerName)
{
	return m_worldState.AddPlayer(playerName);
}
