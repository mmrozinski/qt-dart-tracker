#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <iostream>
#include <vector>

class GameLogic
{
private:
    std::vector<std::string> playerNames;
    std::vector<int> scores;
    std::vector<int> history;
    int playerCount;
    int minNumber;
    int maxNumber;
    int currentPlayer;
    int currentThrow;
    bool isStandard;

private:
    void nextPlayer();

public:
    GameLogic(const int playerCount);
    void setMode(const int maxNumber); // Standard mode
    void setMode(const int minNumber, const int maxNumber); // In-order mode
    void addPlayer(const std::string playerName);
    int getCurrentPlayer() const;
    std::string getPlayer(const int index) const;
    int getScore(const int index) const;
    void commitThrow(const int score);
    void undo(const int n = 1);
    int getCurrentThrow() const;
};

#endif // GAMELOGIC_H
