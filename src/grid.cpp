#include "rand.h"
#include "grid.h"
#include <iomanip>

namespace Minesweeper
{
    Grid::Grid()
        : grid(nullptr)
    {
    }

    Grid::Grid(int x)
        : grid{new std::vector<std::vector<int>>(x, std::vector<int>(x, 0))}
    {
        this->print();
    }

    Grid::~Grid()
    {
        if (grid != nullptr)
        {
            delete grid;
        }
        if (m_bombs != nullptr)
        {
            delete m_bombs;
        }
    }

    Grid* Grid::GetGridAsSize(int x)     //find a way to populate xsize and ysize here
    {

        return new Grid(x);
    }

    void Grid::print()
    {
	int xindex = 0;
	int yindex = 0;
        if (grid != nullptr)
        {
            for (auto i : *grid)
            {
                for (int y : i)
                {
                    if (m_showLocations.find(std::make_pair(xindex, yindex)) != m_showLocations.end())
                    {
                        if (this->getGridNumberAt(std::make_pair(xindex, yindex)) == 9)
                        {
                            std::cout << "\033[31m";
                        }
                        else
                        {
                            std::cout << "\033[34m";
                        }
                        std::cout << y << " ";
                        std::cout << "\033[0m";
                    }
                    else
                    {
                        std::cout << "X ";
                    }
                    ++xindex;
                }
                std::cout << "* " << yindex << std::endl;
		        ++yindex;
                xindex = 0;
            }            
	    for (int i=0; i < 10; ++i)                    //improve this here very ugly formatiting
	    {
		    std::cout << "* ";
	    }
	    std::cout << std::endl;
	    for (int i=0; i < 10; ++i)
	    {
		    std::cout << xindex << " ";
		    ++xindex;
	    }
	    std::cout << std::endl;
        }
    }

    void Grid::Initialize(const Coord& location)
    {
        assert (location.first <= grid->size());         //improve this too
        assert (location.second <= (*grid)[0].size());
        m_showLocations.insert(location);
        std::vector<Coord> neighbours = getNeighboursFromLocation(location);
        for (auto neighbour : neighbours)
        {
            m_showLocations.insert(neighbour);
        }

        this->setInitialNumbers(location);
    }
    
    void Grid::setInitialNumbers(const Coord& location)
    {
        m_bombs = new std::vector<Coord>{};
        m_numberofBombs = 0;
        for (int i = 0; i < grid->size(); ++i)
        {
            for (int j = 0; j < (*grid)[i].size(); ++j)    //make massive improvements here
            {
                if (Randomsss::randoms::getRandom(20))
                {
                    Coord coord(i, j);
                    m_bombs->emplace_back(coord);
                    setGridNumberAtLocation(BOMBNUMBER, i , j);
		            ++m_numberofBombs;
                    incrementGridNumberNotBomb(coord);
                }
            }
        }
    }


    void Grid::setGridNumberAtLocation(int number, Coord& location)
    {
        assert (location.first <= grid->size());
        assert (location.second <= (*grid)[0].size());
        (*grid)[location.first][location.second] = number;
    }
    
    void Grid::setGridNumberAtLocation(int number, int xcol, int ycol)
    {
        assert (xcol <= grid->size());
        assert (ycol <= (*grid)[0].size());
        (*grid)[xcol][ycol] = number;
    }

    void Grid::incrementGridNumberNotBomb(const Coord& location)   //make this better find an algorithm or something, or make your own
    {
        std::vector<Coord> neighbours = getNeighboursFromLocation(location);
        incrementNumberAtCoords(neighbours);

    }

    std::vector<Coord> Grid::getNeighboursFromLocation(const Coord& location)
    {
        std::vector<Coord> neighbour{};
        std::vector<Coord> validNeighbour{};
        neighbour.emplace_back(Coord(location.first -1, location.second -1));
        neighbour.emplace_back(Coord(location.first -1, location.second));
        neighbour.emplace_back(Coord(location.first -1, location.second +1));
        neighbour.emplace_back(Coord(location.first +1, location.second -1));
        neighbour.emplace_back(Coord(location.first +1, location.second));
        neighbour.emplace_back(Coord(location.first +1, location.second +1));
        neighbour.emplace_back(Coord(location.first, location.second +1));
        neighbour.emplace_back(Coord(location.first, location.second -1));

        for (auto coord : neighbour)
        {
            if (isValidCoord(coord))
            {
                validNeighbour.emplace_back(coord);
            }
        }

        return validNeighbour;
    }

    bool Grid::isValidCoord(const Coord& coord)
    {
        return coord.first < grid->size() && coord.second < (*grid)[0].size() && coord.first >= 0 && coord.second >= 0;
    }

    void Grid::incrementNumberAtCoords(std::vector<Coord> coords)
    {
        for (auto coord : coords)
        {
            if ((*grid)[coord.first][coord.second] != 9)
            {
                ++((*grid)[coord.first][coord.second]);
            }
        }
    }

    bool Grid::selectedCoord(const Coord& selected)
    {
        m_showLocations.insert(selected);
        this->print();
        if (getGridNumberAt(selected) == 9)
        {
            std::cout << "Hit a bomb " << "😥" << std::endl;
            return true;
        }
        if (m_showLocations.size() + m_numberofBombs == this->xsize * this->ysize)
        {
            std::cout << "YAAAY you've won " << "😀" << std::endl;
            return true;
        }
        return false;
    }

    int Grid::getGridNumberAt(const Coord& selected)
    {
        return (*grid)[selected.second][selected.first];
    }

}
