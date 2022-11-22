#include <cstdlib>
#include <assert.h>
#include <iostream>
#include <ctime>
int seed = std::time(nullptr);
namespace Randomsss
{
    struct randoms
    {
        //static double[] = [0.2, 0];
        static bool getRandom(int percentage)
        {
            srand(seed);
            seed *= 7;
            assert (percentage < 100);
            int number = rand() % 100;
            return number < percentage;
        }
    };
}
