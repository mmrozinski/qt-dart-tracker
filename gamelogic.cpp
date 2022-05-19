#include "gamelogic.h"

GameLogic::GameLogic(const int playerCount)
{
    this->playerCount = playerCount;
    this->currentPlayer = 0;
    this->currentThrow = 1;
}

void GameLogic::setMode(const int maxNumber)
{
    this->isStandard = true;
    this->maxNumber = maxNumber;

    for (int i = 0; i < playerCount; i++)
        this->scores.push_back(this->maxNumber);
}

void GameLogic::setMode(const int minNumber, const int maxNumber)
{
    this->isStandard = false;
    this->minNumber = minNumber;
    this->maxNumber = maxNumber;
}

void GameLogic::addPlayer(const std::string name)
{
    this->playerNames.push_back(name);
}

int GameLogic::getCurrentPlayer() const
{
    return this->currentPlayer;
}

std::string GameLogic::getPlayer(int index) const
{
    return this->playerNames.at(index);
}

int GameLogic::getScore(const int index) const
{
    return this->scores.at(index);
}

void GameLogic::commitThrow(const int score)
{
    if (isStandard)
    {
        scores.at(currentPlayer) -= score;
        history.push_back(score);

        currentThrow++;

        if (scores.at(currentPlayer) < 0)
        {
            undo(currentThrow - 1);
            nextPlayer();
        }

        if (currentThrow > 3)
        {
            currentThrow = 1;
            nextPlayer();
        }

        while (scores.at(currentPlayer) == 0)
            nextPlayer();
    }
}

void GameLogic::undo(const int n)
{
    for (int i = 0; i < n; i++)
    {
        if (currentThrow > 1)
            currentThrow--;
        else
        {
            currentThrow = 3;
            if (currentPlayer > 0)
                currentPlayer--;
            else
                currentPlayer = playerCount - 1;
        }

        scores.at(currentPlayer) += history.back();
        history.pop_back();
    }
}

int GameLogic::getCurrentThrow() const
{
    return this->currentThrow;
}

void GameLogic::nextPlayer()
{
    if (currentPlayer < playerCount - 1)
        currentPlayer++;
    else
        currentPlayer = 0;
}
