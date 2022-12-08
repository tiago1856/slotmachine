#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H

#include <iostream>
#include <vector>
#include <array>
#include <iomanip>

#include "config.h"
#include "slotqueue.h"
#include "cylinder.h"

typedef std::array<char, NUMBER_OF_CYLINDERS> OutcomeSymbols;

// data structure to save the results of 1 play
struct Results
{
    OutcomeSymbols outcome;
    int bet;
    int prizevalue;
    friend std::ostream & operator << (std::ostream &out, const Results &c)
    {
        out << std::setw(8);
        for (int i = 0; i < NUMBER_OF_CYLINDERS; i++)
            out << c.outcome[i];

        out << std::setw(8) << c.bet;
        out << std::setw(8) << c.prizevalue;
        out << std::setw(8) << c.bet * c.prizevalue;

        return out;
    }
};

typedef SlotQueue <Results,MEMORY_LIST_SIZE> MemoryQueue;


class SlotMachine
{
    public:
        SlotMachine();
        virtual ~SlotMachine();

        // has the player won or lose?
        bool hasWon() const;

        // roll ... if not bet => false else true
        bool play();

        // returns the 3 symbols
        const OutcomeSymbols& getOutcome() const;

        // returns the cylinders symbols as a string separated by a space
        std::string getOutcomeStr() const;

        // returns the last n Results
        const MemoryQueue& getLastNResults() const;

        // set and returns the actual bet [1,10]
        int setBet(int value);
        int getBet() const;

        // value of the prize value ... 0 if not won
        int getPrizeValue() const;

        // value of the prize * bet
        int getWinnings() const;

        // save the last n Results to a text file
        void saveLastNResults(const char* filename);

    private:
        // self-explanatory
        void createCylinders();
        // check the winning condition and set bWin
        void checkWin();
        // parts of the machine
        std::vector<Cylinder*>cylinders;
        // outcome of each play
        OutcomeSymbols outcome;
        // where to store the last MEMORY_LIST_SIZE results
        MemoryQueue last_outcomes;
        // self-explanatory
        bool bWin;

        int currentBet;


};

#endif // SLOTMACHINE_H
