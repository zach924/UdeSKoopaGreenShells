#include <iostream>
#include <SDL.h>

#include "GameWindow.h"

int main(int, char**) {
    
    GameWindow::GetInstance().Init();
    GameWindow::GetInstance().Show(800, 600);
    GameWindow::GetInstance().Close();

    return 0;
}