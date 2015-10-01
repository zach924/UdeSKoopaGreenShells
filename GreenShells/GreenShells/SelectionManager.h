#pragma once
class Position;
class SelectionManager
{
	SelectionManager(SelectionManager const&) = delete;
	void operator=(SelectionManager const&) = delete;

	SelectionManager();
	~SelectionManager();
public:

	static SelectionManager& GetInstance()
	{
		static SelectionManager m_instance;
		return m_instance;
	}

	void HandleSelection(Position pos);
	
};

