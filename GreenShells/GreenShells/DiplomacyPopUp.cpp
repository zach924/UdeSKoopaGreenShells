#include "DiplomacyPopUp.h"
#include "ButtonDiplomacyAction.h"
#include "GameSession.h"
#include "Player.h"
#include <iterator>

const char* DiplomacyPopUp::WINDOW_NAME = { "Diplomacy" };
const int DiplomacyPopUp::WINDOW_HEIGHT = 700;
const int DiplomacyPopUp::WINDOW_WIDTH = 1100;

DiplomacyPopUp::DiplomacyPopUp()
    :PopUpWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT)
    , m_buttons()
    , m_textFont()
    , m_buttonFont()
{
    m_textFont = TTF_OpenFont("..\\Fonts\\roboto\\Roboto-Thin.ttf", m_fontSize);
    m_buttonFont = TTF_OpenFont("..\\Fonts\\roboto\\Roboto-Light.ttf", 16);
}

DiplomacyPopUp::~DiplomacyPopUp()
{
    TTF_CloseFont(m_textFont);
    TTF_CloseFont(m_buttonFont);
    m_buttonFont = nullptr;
    m_textFont = nullptr;
    ClearButtons();
}

void DiplomacyPopUp::ClearButtons()
{
    //for (int i = 0; i < m_buttons.size(); ++i)
    //{
    //    auto pair = m_buttons[i];
    //    delete pair.first;
    //    pair.first = nullptr;
    //}
}

bool DiplomacyPopUp::handleEvent(SDL_Event & e)
{
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
    //ClearButtons();
    m_buttons.clear();
    SDL_SetRenderDrawColor(m_rend, 32, 32, 32, 0);
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
        int horizontalPosition = 0;
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

    Player* player{ GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID()) };

    auto diplomaticRelations = player->GetDiplomaticRelations();
    diplomaticRelations[1] = DiplomaticRelation(RelationStatus::Peace);
    diplomaticRelations[2] = DiplomaticRelation(RelationStatus::Alliance);
    diplomaticRelations[3] = DiplomaticRelation(RelationStatus::War);
    diplomaticRelations[4] = DiplomaticRelation(RelationStatus::NegocatingAlliance);
    diplomaticRelations[5] = DiplomaticRelation(RelationStatus::NegociatingPeace);

    for (auto relation = diplomaticRelations.begin(); relation != diplomaticRelations.end(); ++relation)
    {
        int horizontalPosition = 0;
        int otherPlayerId = relation->first;
        Texture playerNameTexture;
        std::string playerName = "Maxime";//GameSession::GetInstance().GetWorldState()->GetPlayerCopy(playerId)->GetPlayerName();
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

            newButtons.emplace_back(ButtonDiplomacyAction(horizontalPosition + columnSpacer, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Offer Peace", m_buttonFont), [otherPlayerId, &player]() {player->SendPeaceProposition(otherPlayerId); });
            break;
        case RelationStatus::Peace:
            status = PEACE_TEXT;

            buttonPos = horizontalPosition + columnSpacer; //we can't change the horizontal position because we need to draw the status first
            newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Offer Alliance", m_buttonFont), [otherPlayerId, &player]() {player->SendAllianceProposition(otherPlayerId); });
            buttonPos += buttonSpacer;
            newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Declare War", m_buttonFont), [otherPlayerId, &player]() {player->GoToWar(otherPlayerId); });
            break;
        case RelationStatus::Alliance:
            status = ALLIANCE_TEXT;
            break;
        case RelationStatus::NegociatingPeace:
            status = NEGOCIATING_PEACE_TEXT;
            buttonPos = horizontalPosition + columnSpacer; //we can't change the horizontal position because we need to draw the status first
            if (false)//relation->second.GetMustAnswerPlayerId() != otherPlayerId)
            {
                newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Accept Peace", m_buttonFont), [otherPlayerId, &player]() {player->RespondPeaceProposition(otherPlayerId, true); });
                buttonPos += buttonSpacer;
                newButtons.emplace_back(ButtonDiplomacyAction(buttonPos, verticalPosition, BUTTON_WIDTH, BUTTON_HEIGHT, "Refuse Peace", m_buttonFont), [otherPlayerId, &player]() {player->RespondPeaceProposition(otherPlayerId, false); });
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
            if (true)//relation->second.GetMustAnswerPlayerId() != otherPlayerId)
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

    // Show No Button
    //int x = m_buttonNo->GetLeftX();
    //int y = m_buttonNo->GetTopY();
    //int width = m_buttonNo->GetWidth();
    //int height = m_buttonNo->GetHeight();
    //SDL_Rect renderQuadNo = { x, y, width, height };

    //Texture* buttonTextureNo = m_buttonNo->GetButtonTexture(m_rend);
    //Texture * textTextureNo = m_buttonNo->GetTextTexture(m_rend);

    //SDL_RenderCopy(m_rend, buttonTextureNo->GetTexture(), NULL, &renderQuadNo);
    //SDL_RenderCopy(m_rend, textTextureNo->GetTexture(), NULL, &renderQuadNo);

    SDL_RenderPresent(m_rend);
}