#ifndef CONFIG_H
#define CONFIG_H

const static int NUMBER_OF_SYMBOLS = 6;
const static int CYLINDER_SIZE = 12;
const static int NUMBER_OF_CYLINDERS = 3;
const static int MIN_BET = 1;
const static int MAX_BET = 10;
const static int MEMORY_LIST_SIZE = 5;

// if changed, check getPrizeValue() in slotmachine.cpp
const static char SYMBOLS[NUMBER_OF_SYMBOLS] = {'A','B','C','D','E','F'};

const static int PRIZES[NUMBER_OF_SYMBOLS] = {11,13,17,21,23,29};



#endif // CONFIG_H
