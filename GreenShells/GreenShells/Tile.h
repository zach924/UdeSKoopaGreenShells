#pragma once
#include "Position.h"
#include <boost\property_tree\ptree.hpp>
#include "TileBase.h"

template<class T>
class Tile : public TileBase
{
public:
    static Texture m_Texture;
	static bool m_forceLoading;
    static Color m_MinimapColor;

    void LoadTexture() {};
    virtual int GetTypeAsInt() = 0;

    virtual Color GetMinimapColor()
    {
        return m_MinimapColor;
    }

    Tile(Position position = Position(-1, -1))
        : TileBase(position)
    {
    }

    virtual TileBase* Clone() = 0;

    ~Tile()
    {
    }

    virtual Tile* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position(-1, 0))
    {
        return nullptr;
    }

    //Every method must be define in header file because of the static polymorphism
    Texture* GetTexture()
    {
        if (!m_Texture.IsLoaded() || m_forceLoading)
        {
            static_cast<T*>(this)->LoadTexture();
			m_forceLoading = false;
        }
        return &m_Texture;
    }
	static void ForceReload()
	{
		m_forceLoading = true;
	}
};
