#include <iostream>
#include "SkillTreePopUp.h"
#include "ButtonText.h"


SkillTreePopUp::SkillTreePopUp(const char * windowName, int width, int height)
    :PopUpWindow(windowName, width, height),
    m_closeButton(new ButtonText(m_width - 150, 5, 100, 40, "Close", []() {})),
    m_colomnWidth((width - COST_WIDTH) / 8), // 3 for army + 3 for empire + 2 for utility
    m_rowHeight((height - HEADER_HEIGHT) / 8) // 8 tiers
{
    m_heightSpacer = (m_rowHeight - BUTTON_HEIGHT) / 2;
    m_widthSpace = (m_colomnWidth - BUTTON_WIDTH) / 2;

    //Army Tree
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (0 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Ranger", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Militia", []() { std::cout << "Pressed Militia button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (0 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Sword 2", []() { std::cout << "Pressed Sword 2 button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (2 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Axe", []() { std::cout << "Pressed Axe button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (0 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Sword 3", []() { std::cout << "Pressed Sword 3 button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Ranger 2", []() { std::cout << "Pressed Ranger 2 button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (2 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Axe 2", []() { std::cout << "Pressed Axe 2 button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Mace", []() { std::cout << "Pressed Mace button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Ranger 3", []() { std::cout << "Pressed Ranger 3 button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (2 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Mace 2", []() { std::cout << "Pressed Mace 2 button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (0 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Fortress", []() { std::cout << "Pressed Fortress button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Shield", []() { std::cout << "Pressed Shield button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (7 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Cannons", []() { std::cout << "Pressed Cannons button" << std::endl; }));
                                          
    //Empire Tree 4-5-6                   
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (0 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Settler", []() { std::cout << "Pressed Settler button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Monastery", []() { std::cout << "Pressed Monastery button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Farm", []() { std::cout << "Pressed Farm button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Fishery", []() { std::cout << "Pressed Fishery button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Stable", []() { std::cout << "Pressed Stable button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Winmill", []() { std::cout << "Pressed Winmill button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Cathedral", []() { std::cout << "Pressed Cathedral button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Fort", []() { std::cout << "Pressed Fort button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Military Tent", []() { std::cout << "Pressed Military Tent button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Inns & Taverns", []() { std::cout << "Pressed Inns & Taverns button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Warehouse", []() { std::cout << "Pressed Warehouse button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Bonus Res.", []() { std::cout << "Pressed Bonus Res. button" << std::endl; }));
                                       
    //Utility Tree 7-8-9               
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (0 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Watchtower", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Science Bonus", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Border Growth", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Embark", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "+1 ActionPoint", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Vision Bonus", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Mountain Walk", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Armor", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "Mountain Cons", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "University", []() { std::cout << "Pressed Ranger button" << std::endl; }));
    m_buttons.emplace_back(new ButtonText(COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, "No Fog of War", []() { std::cout << "Pressed Ranger button" << std::endl; }));
}

SkillTreePopUp::~SkillTreePopUp()
{
}

void SkillTreePopUp::ShowButton(std::shared_ptr<ButtonText> button)
{
    //the button
    Texture* buttonTexture = button->GetButtonTexture(m_rend);
    int buttonX = button->GetLeftX();
    int buttonY = button->GetTopY();

    //this will stretch the texture to the following width/height
    int buttonWidth = button->GetWidth();
    int buttonHeight = button->GetHeight();
    SDL_Rect buttonRect = { buttonX, buttonY, buttonWidth, buttonHeight };
    SDL_RenderCopy(m_rend, buttonTexture->GetTexture(), NULL, &buttonRect);

    //the text on the button
    Texture * textTexture = button->GetTextTexture(m_rend);
    int textH = textTexture->GetHeight();
    int textW = textTexture->GetWidth();
    int horizontalOffset = (buttonWidth - textW) / 2;
    int verticalOffset = (buttonHeight - textH) / 2;
    SDL_Rect textRect = { buttonX + horizontalOffset, buttonY + verticalOffset, textW, textH };
    SDL_RenderCopy(m_rend, textTexture->GetTexture(), NULL, &textRect);
}

void SkillTreePopUp::ShowWindow(SDL_Renderer * rend)
{
    SDL_SetRenderDrawColor(m_rend, 0, 100, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_rend);

    SDL_SetRenderDrawColor(m_rend, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    //Vertical lines
    SDL_RenderDrawLine(m_rend, COST_WIDTH, 50, COST_WIDTH, m_height);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (3 * m_colomnWidth), 50, COST_WIDTH + (3 * m_colomnWidth), m_height);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (6 * m_colomnWidth), 50, COST_WIDTH + (6 * m_colomnWidth), m_height);

    //Horizontal lines
    SDL_RenderDrawLine(m_rend, 0, 50, m_width, 50);
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT, m_width, HEADER_HEIGHT);
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (1 * m_rowHeight), m_width, HEADER_HEIGHT + (1 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (2 * m_rowHeight), m_width, HEADER_HEIGHT + (2 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (3 * m_rowHeight), m_width, HEADER_HEIGHT + (3 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (4 * m_rowHeight), m_width, HEADER_HEIGHT + (4 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (5 * m_rowHeight), m_width, HEADER_HEIGHT + (5 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (6 * m_rowHeight), m_width, HEADER_HEIGHT + (6 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (7 * m_rowHeight), m_width, HEADER_HEIGHT + (7 * m_rowHeight));

    int x = 25;
    int y = 0;
    int width = 200;
    int height = m_fontSize;

    for (int i = 0; i < m_texts.size(); ++i)
    {
        SDL_Texture* texture = m_texts.at(i);

        y = (i * m_fontSize) + 10;

        SDL_Rect renderQuadText = { x, y, width, height };

        SDL_RenderCopy(m_rend, texture, NULL, &renderQuadText);
    }


    //Headers
    {
        int headerHight = 60;
        Texture costHeader;
        costHeader.CreateFromText("Costs", m_font, m_rend);
        int costX = 5;
        SDL_Rect costHeaderRect{ costX, headerHight, costHeader.GetWidth(), costHeader.GetHeight() };
        SDL_RenderCopy(m_rend, costHeader.GetTexture(), NULL, &costHeaderRect);

        Texture armyHeader;
        armyHeader.CreateFromText("Army Tree", m_font, m_rend);
        int armyX = COST_WIDTH + (3 * m_colomnWidth / 2) - (armyHeader.GetWidth()/2);
        SDL_Rect armyHeaderRect{ armyX, headerHight, armyHeader.GetWidth(), armyHeader.GetHeight() };
        SDL_RenderCopy(m_rend, armyHeader.GetTexture(), NULL, &armyHeaderRect);

        Texture empireHeader;
        empireHeader.CreateFromText("Empire Tree", m_font, m_rend);
        int empireX = COST_WIDTH + 3 * m_colomnWidth + (3 * m_colomnWidth / 2) - (armyHeader.GetWidth() / 2);
        SDL_Rect empireHeaderRect{ empireX, headerHight, empireHeader.GetWidth(), empireHeader.GetHeight() };
        SDL_RenderCopy(m_rend, empireHeader.GetTexture(), NULL, &empireHeaderRect);

        Texture utilityHeader;
        utilityHeader.CreateFromText("Utility Tree", m_font, m_rend);
        int utilityX = COST_WIDTH + 6 * m_colomnWidth + (2 * m_colomnWidth / 2) - (armyHeader.GetWidth() / 2);
        SDL_Rect utilityHeaderRect{ utilityX, headerHight, utilityHeader.GetWidth(), utilityHeader.GetHeight() };
        SDL_RenderCopy(m_rend, utilityHeader.GetTexture(), NULL, &utilityHeaderRect);

        Texture tierOne;
        tierOne.CreateFromText("1. 10S", m_font, m_rend);
        int tierOneX = 5;
        SDL_Rect tierOneRect{ tierOneX, HEADER_HEIGHT + (0 * m_rowHeight) + m_heightSpacer, tierOne.GetWidth(), tierOne.GetHeight() };
        SDL_RenderCopy(m_rend, tierOne.GetTexture(), NULL, &tierOneRect);

        Texture tierTwo;
        tierTwo.CreateFromText("2. 100S", m_font, m_rend);
        int tierTwoX = 5;
        SDL_Rect tierTwoRect{ tierTwoX, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer, tierTwo.GetWidth(), tierTwo.GetHeight() };
        SDL_RenderCopy(m_rend, tierTwo.GetTexture(), NULL, &tierTwoRect);

        Texture tierThree;
        tierThree.CreateFromText("3. 250S", m_font, m_rend);
        int tierThreeX = 5;
        SDL_Rect tierThreeRect{ tierThreeX, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer, tierThree.GetWidth(), tierThree.GetHeight() };
        SDL_RenderCopy(m_rend, tierThree.GetTexture(), NULL, &tierThreeRect);

        Texture tierFour;
        tierFour.CreateFromText("4. 500S", m_font, m_rend);
        int tierFourX = 5;
        SDL_Rect tierFourRect{ tierFourX, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer, tierFour.GetWidth(), tierFour.GetHeight() };
        SDL_RenderCopy(m_rend, tierFour.GetTexture(), NULL, &tierFourRect);

        Texture tierFive;
        tierFive.CreateFromText("5. 1000S", m_font, m_rend);
        int tierFiveX = 5;
        SDL_Rect tierFiveRect{ tierFiveX, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer, tierFive.GetWidth(), tierFive.GetHeight() };
        SDL_RenderCopy(m_rend, tierFive.GetTexture(), NULL, &tierFiveRect);

        Texture tierSix;
        tierSix.CreateFromText("6. 2000S", m_font, m_rend);
        int tierSixX = 5;
        SDL_Rect tierSixRect{ tierSixX, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer, tierSix.GetWidth(), tierSix.GetHeight() };
        SDL_RenderCopy(m_rend, tierSix.GetTexture(), NULL, &tierSixRect);

        Texture tierSeven;
        tierSeven.CreateFromText("7. 3500S", m_font, m_rend);
        int tierSevenX = 5;
        SDL_Rect tierSevenRect{ tierSevenX, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer, tierSeven.GetWidth(), tierSeven.GetHeight() };
        SDL_RenderCopy(m_rend, tierSeven.GetTexture(), NULL, &tierSevenRect);

        Texture tierEight;
        tierEight.CreateFromText("8. 5000S", m_font, m_rend);
        int tierEightX = 5;
        SDL_Rect tierEightRect{ tierEightX, HEADER_HEIGHT + (7 * m_rowHeight) + m_heightSpacer, tierEight.GetWidth(), tierEight.GetHeight() };
        SDL_RenderCopy(m_rend, tierEight.GetTexture(), NULL, &tierEightRect);
    }

    SDL_SetRenderDrawColor(m_rend, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    int halfButtonWidth = BUTTON_WIDTH / 2;
    //Army dependencies
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (0 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (0 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (2 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (0 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (0 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (0 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (2 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (2 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (2 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (2 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (0 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (1 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (7 * m_rowHeight) + m_heightSpacer);
    
    //Empire dependencies
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (0 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (3 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (5 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (4 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer);

    //Utility dependencies
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (0 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (1 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (2 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (3 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (4 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (6 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (5 * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (7 * m_colomnWidth) + m_widthSpace + halfButtonWidth, HEADER_HEIGHT + (6 * m_rowHeight) + m_heightSpacer);

    ShowButton(m_closeButton);
    for (auto button : m_buttons)
    {
        ShowButton(button);
    }

    SDL_RenderPresent(m_rend);
}

bool SkillTreePopUp::handleEvent(SDL_Event & e)
{
    if (m_closeButton->IsUnpressed() && m_closeButton->IsInside(e.button.x, e.button.y))
    {
        return true;
    }
    for (auto button : m_buttons)
    {
        if (button->IsUnpressed() && button->IsInside(e.button.x, e.button.y))
        {
            button->DoAction();
        }
    }
    return false;
}
