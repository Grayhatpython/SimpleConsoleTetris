#include "pch.h"
#include "MainMenu.h"
#include "ConsoleHelper.h"

void MainMenu::MenuOutput()
{
    ConsoleHelper::SetCursorPosition(0, 10);
    std::cout << "\t\t\t" << "@@@@@@@@@@@@  @@@@@@@@@   @@@@@@@@@@@  @@@@@@@@   @   @@@@@@@@@@@" << std::endl;
    std::cout << "\t\t\t" << "      @       @                @       @      @   @   @          " << std::endl;
    std::cout << "\t\t\t" << "      @       @                @       @      @   @   @          " << std::endl;
    std::cout << "\t\t\t" << "      @       @@@@@@@@@        @       @     @    @   @@@@@@@@@@@" << std::endl;
    std::cout << "\t\t\t" << "      @       @                @       @ @ @      @             @" << std::endl;
    std::cout << "\t\t\t" << "      @       @                @       @     @    @             @" << std::endl;
    std::cout << "\t\t\t" << "      @       @@@@@@@@@        @       @      @   @   @@@@@@@@@@@" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "\t\t\t\t\t\t" << "1. Game Start. " << std::endl;
    std::cout << "\t\t\t\t\t\t" << "2. Exit.       " << std::endl;
    std::cout << "\t\t\t\t\t\t" << "Input : ";
}

bool MainMenu::DoYouWantPlayGame()
{
    while (true)
    {
        MenuOutput();

        std::cin >> _userInput;

        if (std::cin.fail()) {
            std::cin.clear();          
            std::cin.ignore(100, '\n'); 
            system("cls");
        }

        if (_userInput == EXIT)
            return false;

        if (_userInput == GAME_START)
            break;
    }

    system("cls");

    return true;
}
