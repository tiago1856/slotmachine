#include "slotmachine.h"

#include <fstream>

SlotMachine::SlotMachine()
{
    createCylinders();

    // init all variables
    bWin = false;
    currentBet = 0;
    for (int i = 0; i < NUMBER_OF_CYLINDERS; i++)
        outcome[i] = 0;
}

SlotMachine::~SlotMachine()
{
    for (auto cylinder: cylinders)
    {
        delete cylinder;
        cylinder = nullptr;
    }

    cylinders.clear();
}

void SlotMachine::createCylinders()
{
    for (int i = 0; i < NUMBER_OF_CYLINDERS; i++)
        cylinders.push_back(new Cylinder());
}

bool SlotMachine::hasWon() const
{
    return bWin;
}

void SlotMachine::checkWin()
{
    bWin = true;
    for (int i = 0; i < NUMBER_OF_CYLINDERS - 1; i++)
    {
        if (outcome[i] != outcome[i+1])
        {
            bWin = false;
            return;
        }
    }
}

bool SlotMachine::play()
{
    if (this->currentBet == 0)
        return false;

    for (int i = 0; i < NUMBER_OF_CYLINDERS; i++)
        outcome[i] = cylinders[i]->getSymbol();

    checkWin();

    // save results
    Results result = {outcome, getBet(), getPrizeValue()};
    last_outcomes.push(result);

    return true;
}

const OutcomeSymbols& SlotMachine::getOutcome() const
{
    return outcome;
}

int SlotMachine::getPrizeValue() const
{
    if (bWin)
    {
        // this only works if symbols are continuous
        return PRIZES[outcome[0]- SYMBOLS[0]];
    }
    return 0;
}

std::string SlotMachine::getOutcomeStr() const
{
    std::string str(std::begin(outcome), std::end(outcome));

    // insert space between the symbols
    for (int i = NUMBER_OF_CYLINDERS-1; i > 0 ; i--)
        str.insert(i, " ");

    return str;
}

int SlotMachine::setBet(int value)
{
    if (value > MAX_BET)
        this->currentBet = MAX_BET;
    else if (value < MIN_BET)
        this->currentBet = MIN_BET;
    else
        this->currentBet = value;
    return this->currentBet;
}

int SlotMachine::getBet() const
{
    return this->currentBet;
}

int SlotMachine::getWinnings() const
{
    return this->currentBet * getPrizeValue();
}


const MemoryQueue& SlotMachine::getLastNResults() const
{
    return last_outcomes;
}


void SlotMachine::saveLastNResults(const char* filename)
{

    std::ofstream file;
    file.open (filename);
    file << std::setw(10) << "SYMBOLS"
        << std::setw(10) << "BET"
        << std::setw(10) << "PRIZE"
        << std::setw(10) << "WINNINGS" << std::endl;
    file<< "------------------------------------------" << std::endl;

    for (auto a: last_outcomes)
    {
        file << a << std::endl;
    }
    file << std::endl << std::endl;

    file.close();

}
