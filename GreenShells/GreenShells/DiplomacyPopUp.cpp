#include "DiplomacyPopUp.h"
#include "ButtonDiplomacyAction.h"
#include "GameSession.h"
#include "Player.h"
#include <iterator>

const char* DiplomacyPopUp::WINDOW_NAME = { "Diplomacy" };
const int DiplomacyPopUp::WINDOW_HEIGHT = 600;
const int DiplomacyPopUp::WINDOW_WIDTH = 1100;

DiplomacyPopUp::DiplomacyPopUp()
    :PopUpWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT)
    , m_buttons()
    , m_textFont()
    , m_buttonFont()
    , m_buttonClose()
{
    m_textFont = TTF_OpenFont("..\\Fonts\\roboto\\Roboto-Thin.ttf", m_fontSize);
    m_buttonFont = TTF_OpenFont("..\\Fonts\\roboto\\Roboto-Light.ttf", 16);
    int buttonX = (WINDOW_WIDTH / 2) - BUTTON_WIDTH / 2;
    int buttonY = WINDOW_HEIGHT - (BUTTON_HEIGHT * 2);
    m_buttonClose = new ButtonDiplomacyAction(buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT, "Close", m_buttonFont);
}

DiplomacyPopUp::~DiplomacyPopUp()
{
    TTF_CloseFont(m_textFont);
    TTF_CloseFont(m_buttonFont);
    delete m_buttonClose;
    m_buttonClose = nullptr;
    m_buttonFont = nullptr;
    m_textFont = nullptr;
}

bool DiplomacyPopUp::handleEvent(SDL_Event & e)
{
    if (m_buttonClose->IsUnpressed() && m_buttonClose->IsInside(e.button.x, e.button.y))
    {
        return true;
    }

    for (auto pair : m_buttons)
    {
        if (pair.first.IsUnpressed() && pair.first.IsInside(e.button.x, e.button.y))
        {
            pair.second();
            //pair.first.DoAction();
        }
    }
    return false;
}

void DiplomacyPopUp::ShowWindow(SDL_Renderer* rend)
{
    //clear screen
    m_buttons.clear();
    SDL_SetRenderDrawColor(m_rend, 0, 100, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_rend);
    int verticalSpacer = BUTTON_HEIGHT + 10;
    int verticalPosition = 0 + verticalSpacer;
    int columnSpacer = 0;
    int buttonSpacer = BUTTON_WIDTH + 10;
    TTF_SizeText(m_textFont, LARGEST_NAME, &columnSpacer, NULL);


    ////*********
    //DisplayHeaders
    ////*********
    {
        int horizontalPosition = 5;
        Texture playersHeader;
        playersHeader.CreateFromText("Players", m_textFont, m_rend);
        SDL_Rect playerHeaderRect{ horizontalPosition, verticalPosition, playersHeader.GetWidth(), playersHeader.GetHeight() };
        SDL_RenderCopy(m_rend, playersHeader.GetTexture(), NULL, &playerHeaderRect);

        horizontalPosition += columnSpacer;

        Texture relationsHeader;
        relationsHeader.CreateFromText("Status", m_textFont, m_rend);
        SDL_Rect relationHeaderRect{ horizontalPosition, verticalPosition, relationsHeader.GetWidth(), relationsHeader.GetHeight() };
        SDL_RenderCopy(m_rend, relationsHeader.GetTexture(), NULL, &relationHeaderRect);
    }
    verticalPosition += verticalSpacer;

    SDL_SetRenderDrawColor(m_rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(m_rend, 0, verticalPosition - 3, WINDOW_WIDTH, verticalPosition - 3);

    ////*********
    //Players
    ////*********

    int playerId = GameSession::GetInstance().GetCurrentPlayerID();
    Player* player{ GameSession::GetInstance().GetWorldState()->GetPlayerCopy(playerId) };
    auto diplomaticRelations = player->GetDiplomaticRelations();
    //diplomaticRelations[1] = DiplomaticRelation(RelationStatus::Peace);
    //diplomaticRelations[2] = DiplomaticRelation(RelationStatus::Alliance);
    //diplomaticRelations[3] = DiplomaticRelation(RelationStatus::War);
    //diplomaticRelations[4] = DiplomaticRelation(RelationStatus::NegocatingAlliance);
    //diplomaticRelations[5] = DiplomaticRelation(RelationStatus::NegociatingPeace);
    //diplomaticRelations[6] = DiplomaticRelation(RelationStatus::War);
    //diplomaticRelations[7] = DiplomaticRelation(RelationStatus::NegocatingAlliance);

    for (auto relation = diplomaticRelations.begin(); relation != diplomaticRelations.end(); ++relation)
    {
        int horizontalPosition = 5;
        int otherPlayerId = relation->first;
        Texture playerNameTexture;
        std::string playerName = /*"Maxime";*/GameSession::GetInstance().GetWorldState()->GetPlayerCopy(otherPlayerId)->GetPlayerName();
        playerNameTexture.CreateFromText(playerName, m_textFont, m_rend);
        SDL_Rect playerNameRect{ horizontalPosition, verticalPosition, playerNameTexture.GetWidth(), playerNameTexture.GetHeight() };
        SDL_RenderCopy(m_rend, playerNameTexture.GetTexture(), NULL, &playerNameRect);

        horizontalPosition += columnSpacer;

        Texture statusTexture;
        Texture messageToPlayer;
        std::string status;
        std::vector<std::pair<ButtonDiplomacyAction, std::function<void()> > > newButtons;
        int buttonPos = 0;


        switch (relation->second.GetRelationStatus())
        {
        case RelationStatus::War:
            status = WAR_TEXT;
            buttonPos = horizontalPosition + columnSpacer;
            newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Offer Peace", m_buttonFont), [otherPlayerId, playerId]() {GameSession::GetInstance().GetWorldState()->GetPlayerCopy(playerId)->SendPeaceProposition(otherPlayerId); });
            break;
        case RelationStatus::Peace:
            status = PEACE_TEXT;

            buttonPos = horizontalPosition + columnSpacer; //we can't change the horizontal position because we need to draw the status first
            newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Offer Alliance", m_buttonFont), [otherPlayerId, playerId]() {GameSession::GetInstance().GetWorldState()->GetPlayerCopy(playerId)->SendAllianceProposition(otherPlayerId); });
            buttonPos += buttonSpacer;
            newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Declare War", m_buttonFont), [otherPlayerId, playerId]() {GameSession::GetInstance().GetWorldState()->GetPlayerCopy(playerId)->GoToWar(otherPlayerId); });
            break;
        case RelationStatus::Alliance:
            status = ALLIANCE_TEXT;
            break;
        case RelationStatus::NegociatingPeace:
            status = NEGOCIATING_PEACE_TEXT;
            buttonPos = horizontalPosition + columnSpacer; //we can't change the horizontal position because we need to draw the status first
            if (relation->second.GetMustAnswerPlayerId() != otherPlayerId)
            {
                newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Accept Peace", m_buttonFont), [otherPlayerId, playerId]() {GameSession::GetInstance().GetWorldState()->GetPlayerCopy(playerId)->RespondPeaceProposition(otherPlayerId, true); });
                buttonPos += buttonSpacer;
                newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Refuse Peace", m_buttonFont), [otherPlayerId, playerId]() {GameSession::GetInstance().GetWorldState()->GetPlayerCopy(playerId)->RespondPeaceProposition(otherPlayerId, false); });
            }
            else
            {
                messageToPlayer.CreateFromText("Waiting for Player", m_textFont, m_rend);
                SDL_Rect messageRect = { buttonPos, verticalPosition, messageToPlayer.GetWidth(), messageToPlayer.GetHeight() };
                SDL_RenderCopy(m_rend, messageToPlayer.GetTexture(), NULL, &messageRect);
            }

            break;
        case RelationStatus::NegocatingAlliance:
            status = NEGOCIATING_ALLIANCE_TEXT;
            buttonPos = horizontalPosition + columnSpacer;//we can't change the horizontal position because we need to draw the status first
            if (relation->second.GetMustAnswerPlayerId() != otherPlayerId)
            {
                newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Accept Alliance", m_buttonFont), [otherPlayerId, &player]() {player->RespondAllianceProposition(otherPlayerId, true); });
                buttonPos += buttonSpacer;
                newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Refuse Alliance", m_buttonFont), [otherPlayerId, &player]() {player->RespondAllianceProposition(otherPlayerId, false); });
            }
            else
            {
                messageToPlayer.CreateFromText("Waiting for Player", m_textFont, m_rend);
                SDL_Rect messageRect = { buttonPos, verticalPosition, messageToPlayer.GetWidth(), messageToPlayer.GetHeight() };
                SDL_RenderCopy(m_rend, messageToPlayer.GetTexture(), NULL, &messageRect);
            }
            break;
        }

        statusTexture.CreateFromText(status, m_textFont, m_rend);
        SDL_Rect statusRect = { horizontalPosition, verticalPosition, statusTexture.GetWidth(), statusTexture.GetHeight() };
        SDL_RenderCopy(m_rend, statusTexture.GetTexture(), NULL, &statusRect);
        horizontalPosition += horizontalPosition;

        for (auto pair : newButtons)
        {
            Texture* buttonTexture = pair.first.GetButtonTexture(m_rend);
            int buttonWidth = pair.first.GetWidth();
            int buttonHeight = pair.first.GetHeight();
            SDL_Rect buttonRect = { horizontalPosition, verticalPosition, buttonWidth, buttonHeight };
            SDL_RenderCopy(m_rend, buttonTexture->GetTexture(), NULL, &buttonRect);

            Texture * textTexture = pair.first.GetTextTexture(m_rend);
            int textH = textTexture->GetHeight();
            int textW = textTexture->GetWidth();
            int horizontalOffset = (buttonWidth - textW) / 2;
            int verticalOffset = (buttonHeight - textH) / 2;
            SDL_Rect textRect = { horizontalPosition + horizontalOffset, verticalPosition + verticalOffset, textW, textH };
            SDL_RenderCopy(m_rend, textTexture->GetTexture(), NULL, &textRect);
            horizontalPosition += buttonSpacer;
        }
        std::move(newButtons.begin(), newButtons.end(), std::back_inserter(m_buttons));

        verticalPosition += verticalSpacer;
        SDL_SetRenderDrawColor(m_rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(m_rend, 0, verticalPosition - 3, WINDOW_WIDTH, verticalPosition - 3);
    }

    // Show close button
    {
        int buttonX = m_buttonClose->GetLeftX();
        int buttonY = m_buttonClose->GetTopY();
        int buttonWidth = m_buttonClose->GetWidth();
        int buttonHeight = m_buttonClose->GetHeight();

        SDL_Rect closeButtonRect = { buttonX, buttonY, buttonWidth, buttonHeight };
        Texture* buttonCloseText = m_buttonClose->GetButtonTexture(m_rend);
        SDL_RenderCopy(m_rend, buttonCloseText->GetTexture(), NULL, &closeButtonRect);


        Texture* textCloseText = m_buttonClose->GetTextTexture(m_rend);
        int textH = textCloseText->GetHeight();
        int textW = textCloseText->GetWidth();
        int horizontalOffset = (buttonWidth - textW) / 2;
        int verticalOffset = (buttonHeight - textH) / 2;
        SDL_Rect textRect = { buttonX + horizontalOffset, buttonY + verticalOffset, textW, textH };
        SDL_RenderCopy(m_rend, textCloseText->GetTexture(), NULL, &textRect);

    }

    SDL_RenderPresent(m_rend);
}