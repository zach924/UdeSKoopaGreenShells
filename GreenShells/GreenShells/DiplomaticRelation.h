#pragma once


enum RelationStatus
{
    Peace,
    War,
    Alliance,
    NegociatingPeace,
    NegocatingAlliance
};

class DiplomaticRelation
{
    RelationStatus m_status;
    int m_mustAnswerPlayerId;

public:
    DiplomaticRelation(RelationStatus status = RelationStatus::Peace, int mustAnswerPlayerId = -1);
    ~DiplomaticRelation();
    void ChangeRelationStatus(RelationStatus status, int mustAnswerPlayerId = -1);
    int GetMustAnswerPlayerId();
    RelationStatus GetRelationStatus();
};

