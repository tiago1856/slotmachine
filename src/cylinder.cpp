#include "cylinder.h"
#include <random>
#include <algorithm>
#include <ctime>



Cylinder::Cylinder()
{
    setConfig(true);
}

Cylinder::~Cylinder()
{
}

void Cylinder::setConfig(bool shuffle)
{
    // if there's already a config ... clear it
    config.clear();

    // at least 1 occurrence of each symbol
    for (auto i = 0; i < NUMBER_OF_SYMBOLS; i++)
    {
        config.push_back(SYMBOLS[i % NUMBER_OF_SYMBOLS]);
    }

    // now the rest is random
    for (auto i = NUMBER_OF_SYMBOLS; i < CYLINDER_SIZE; i++)
    {
        config.push_back(SYMBOLS[getRandomInt(0, NUMBER_OF_SYMBOLS - 1)]);
    }

    if (shuffle)
    {
        std::random_shuffle ( config.begin(), config.end() );
    }
}


void Cylinder::setConfig(const std::vector<char>& newconfig)
{
    // just using the good old assign operator
    config = newconfig;
}

const std::vector<char>& Cylinder::getConfig() const
{
    return config;
}

int Cylinder::getRandomInt(int min, int max)
{
    //static std::random_device rd; // obtain a random number from hardware
    static std::mt19937 eng(std::time(nullptr)); // seed the generator
    std::uniform_int_distribution<> distr(min, max);
    return distr(eng);
}

char Cylinder::getSymbol() const
{
    return config[getRandomInt(0,CYLINDER_SIZE - 1)];
}


std::ostream & operator << (std::ostream &out, const Cylinder &c)
{
    for (const auto& x : c.config)
        out << x;
    return out;
}
