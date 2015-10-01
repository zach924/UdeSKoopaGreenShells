#pragma once

class Position;
class ClickManager
{
	ClickManager(ClickManager const&) = delete;
	void operator=(ClickManager const&) = delete;

	ClickManager();
	~ClickManager();

public:
	static ClickManager& GetInstance()
	{
		static ClickManager m_instance;
		return m_instance;
	}

	void ManageMapClick(const Position& position);
	void ManageLeftMenuClick(const int& x, const int& y);
	void ManageTopMenuClick(const int& x, const int& y);
};

