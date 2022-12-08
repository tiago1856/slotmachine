#ifndef CYLINDER_H
#define CYLINDER_H


#include <vector>
#include <iostream>

#include "config.h"


class Cylinder
{
    public:
        Cylinder();
        virtual ~Cylinder();

        // the first 6 are A,B,C,D,E,F and the rest are randomly selected
        // if shuffle then randomize the entire vector at the end
        void setConfig(bool shuffle = false);
        // manual setting
        void setConfig(const std::vector<char>& newconfig);

        // returns the current cylinder configuration: sequence
        // of the symbols
        const std::vector<char>& getConfig() const;

        // no need to physically simulate the cylinder rolling
        // => just return the symbol of a random position
        char getSymbol() const;

        // used for debug
        friend std::ostream & operator << (std::ostream &out, const Cylinder &c);
    private:
        // returns a random integer [min, max]
        // uses the Mersenne Twister pseudo-random generator
        static int getRandomInt(int min, int max);
        // holds the current sequence of symbols of the cylinder
        std::vector<char>config;
};

#endif // CYLINDER_H
