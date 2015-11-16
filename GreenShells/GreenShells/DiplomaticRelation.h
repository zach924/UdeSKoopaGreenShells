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
    int m_propositionTurn;

public:
    DiplomaticRelation(int propositionTurn = -1, RelationStatus status = RelationStatus::Peace, int mustAnswerPlayerId = -1);
    ~DiplomaticRelation();
    void ChangeRelationStatus(RelationStatus status, int currentTurn, int mustAnswerPlayerId = -1);
    int GetMustAnswerPlayerId();
    RelationStatus GetRelationStatus();
    int GetPropositionTurn();
};

