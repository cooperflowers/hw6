#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here


        unsigned long long wals[5] = { 0, 0, 0, 0, 0};               //defualting to zero
        int id = static_cast<int>(k.size()) - 1;                        // starting at last spot

        for(int i = 4; i >= 0 && id >= 0; --i)                      //loop to fill 
        {
            unsigned long long mult = 1;                      //        
            unsigned long long val  = 0;                             

            for(int count = 0; count < 6 && id >= 0; ++count, --id)     // take up to 6 chars
            {
                unsigned long long digit = static_cast<unsigned long long>(letterDigitToNumber(k[id]));         //digit val for the character
                val += digit * mult;                                                                        // update val with digit and multiplier                
                mult *= 36;                                                                                 //next digit goes up power
            }

            wals[i] = val;                                            // store in wals
        }

        unsigned long long hash = 0;                                   

        for(int i = 0; i < 5; ++i)                                       
        {
            hash += static_cast<unsigned long long>(rValues[i]) * wals[i]; 
        }

        return static_cast<HASH_INDEX_T>(hash);                                

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        if(letter >= 'A' && letter <= 'Z')                                // if uppercase
        {
            letter = static_cast<char>(letter - 'A' + 'a');               //convert to lower
        }

        if(letter >= 'a' && letter <= 'z')                                // if lower
        {
            return static_cast<HASH_INDEX_T>(letter - 'a');               
        }

        return static_cast<HASH_INDEX_T>((letter - '0') + 26);            
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
