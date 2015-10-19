#pragma once
#include "DistrictBase.h"
#include "Texture.h"
#include <boost\property_tree\ptree.hpp>

template<class T>
class District : public DistrictBase
{
public:
	District(int& ownerID);
	~District();

	//Every method must be define in header file because of the static polymorphism
	Texture* GetTexture()
	{
		if (!m_Texture.IsLoaded())
		{
			static_cast<T*>(this)->LoadTexture();
		}
		return &m_Texture;
	}
};

