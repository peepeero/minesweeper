#include "grid.h"
#include <limits>

using namespace std;
int main()
{
    Minesweeper::Grid* myGrid = Minesweeper::Grid::GetGridAsSize(10);
    int a, b;
    std::cout << "Enter initial coordinates to get started, i.e 3 and 7. The grid is 10x10 only for now!" << std::endl;
    while (true)
    {
        std::cin >> a >> b;
        std::cout << a << " then " << b <<std::endl;
	    if (std::cin.fail())
	    {
		    std::cin.clear();
		    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    std::cout << "Input 2 numbers only" << std::endl;
	    }
	    else if (a < 0 || a > 10 || a < 0 || a > 10)
        {
	        std::cout << "you must input numbers that work" << std::endl;
        }
	    else
	    {
            break;
	    }
    }

    Coord coord(a,b);
    myGrid->Initialize(coord);
    myGrid->print();
    bool isGameOver  = false;
    while (!isGameOver)
    {
        while (true)
        {
            std::cout << "Add your next coordinates" << std::endl;
            std::cin >> a >> b;
            std::system("clear");
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                std::cout << "Input 2 numbers only" << std::endl;
            }
            else if (a < 0 || a > 10 || a < 0 || a > 10)
            {
                std::cout << "you must input numbers that work" << std::endl;
            }
            else
            {
                break;
            }
        }
        isGameOver = myGrid->selectedCoord(std::make_pair(a, b));
    }
    delete myGrid;
}
