#include <iostream>
#include <vector>
#include <cstdint>
#include <set>

#define BOMBNUMBER 9

namespace Minesweeper
{

    #define Coord std::pair<int, int>

    class Grid
    {
        public:
            static Grid* GetGridAsSize(int x);
            ~Grid();
            void print();
            void Initialize(const Coord& location);
            bool selectedCoord(const Coord& coord);
        
        private:
            Grid();
            Grid(int x);
            void setInitialNumbers(const Coord& location);
            void setGridNumberAtLocation(int number, Coord& location);
            void setGridNumberAtLocation(int number, int xloc, int yloc);
            void incrementGridNumberNotBomb(const Coord& bombLocation);
            std::vector<Coord> getNeighboursFromLocation(const Coord& bombLocation);
            bool isValidCoord(const Coord& coord);
            void incrementNumberAtCoords(std::vector<Coord> coords);
            int getGridNumberAt(const Coord& coord);

            std::vector<std::vector<int>>* grid; 
            std::vector<Coord>* m_bombs;
            std::set<Coord> m_showLocations;
            int xsize;
            int m_numberofBombs;
            int ysize;
    };


   /* struct Coord
    {
        int x;
        int y;

        Coord(int xcol, int ycol)
        {
            x = xcol;
            y = ycol;
        }
    };*/
}

