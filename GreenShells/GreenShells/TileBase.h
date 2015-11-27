#pragma once
#include <memory>
#include "Texture.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"
#include "MapFilter.h"

class DistrictBase;
class UnitBase;

class TileBase
{
private :
    static const int PLAYER_ONE_SEEN   = 0x00000001;
    static const int PLAYER_TWO_SEEN   = 0x00000010;
    static const int PLAYER_THREE_SEEN = 0x00000100;
    static const int PLAYER_FOUR_SEEN  = 0x00001000;
    static const int PLAYER_FIVE_SEEN  = 0x00010000;
    static const int PLAYER_SIX_SEEN   = 0x00100000;
    static const int PLAYER_SEVEN_SEEN = 0x01000000;
    static const int PLAYER_EIGHT_SEEN = 0x10000000;

protected:
    bool m_OverlayVisible;
    std::shared_ptr<DistrictBase> m_district;
    std::shared_ptr<UnitBase> m_unit;
    int m_owner;
    Position m_position;

    int m_playerDiscovered;
    int m_playerSee;

public:

    virtual Color GetMinimapColor() =0;
    TileBase(Position position = Position(-1, -1));
    virtual ~TileBase();
    virtual TileBase* Clone() = 0;
    bool GetOverlayVisible();
    void SetOverlayVisible(bool visible);
    virtual Position GetPosition();
    virtual Texture* GetTexture() = 0;
    virtual bool CanTraverse(MapFilter filter)=0;
    virtual int GetTypeAsInt() = 0;
    virtual TileBase* Deserialize(boost::property_tree::ptree tileNode, Position pos);
    virtual void NotifyNewTurn(int turn);
    virtual std::shared_ptr<DistrictBase> GetDistrict();
    virtual void SetDistrict(std::shared_ptr<DistrictBase> district);
    virtual std::shared_ptr<UnitBase> GetUnit();
    virtual void SetUnit(std::shared_ptr<UnitBase> unit);
    virtual int GetPlayerOwnerId();
    virtual void SetPlayerOwnerId(int id);

    void PlayerDiscover(int playerId);
    bool IsDiscovered(int playerId);
    void PlayerSee(int playerId);
    void PlayerDontSeeAnymore(int playerId);
    bool IsSeen(int playerId);

    bool IsFree();
    boost::property_tree::ptree Serialize();
};
