#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
class Person
{
public:
    void setPos(int x, int y);
    int getPosX()
    {
        return col;
    }
    int getPosY()
    {
        return row;
    }

private:
    int col = -1;
    int row = -1;
};

void Person::setPos(int x, int y)
{
    col = x;
    row = y;
}

class Maze
{
public:
    Maze(int width, int height, std::ifstream &input);
    void start(std::ifstream &input);
    void printMaze();
    void setExitAndPlayer(std::ifstream &input);
    std::vector< std::vector<char> > grid;

private:
    int w = -1;
    int h = -1;
    int exitRow = -1;
    int exitCol = -1;
    std::vector<char> actions;
    Person player;
    void setActions(std::ifstream &input);
    void setPerson(Person &p, std::ifstream &input);
    void performActions(std::vector<char> directions);
    void setInput(int width, int height, std::ifstream &input);
    void resizeGrid();
};

Maze::Maze(int width, int height, std::ifstream &input)
{
    w = width;
    h = height;

    resizeGrid();
    setInput(width, height, input);
}
void Maze::resizeGrid()
{
    grid.resize(h);
    for (int i = 0; i < h; i++)
    {
        grid.at(i).resize(w);
    }
}
void Maze::printMaze()
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid.at(0).size(); j++)
        {
            std::cout << grid.at(i).at(j);
        }
        std::cout << std::endl;
    }
}
void Maze::setInput(int width, int height, std::ifstream &input)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            char a;
            input >> a;
            if (a == 'l' || a == '.' && !input.fail())
            {
                grid.at(i).at(j) = a;
            }
            else
            {
                throw std::runtime_error("an error occurred: could not read maze layout");
            }
        }
    }
}
void Maze::start(std::ifstream &input)
{
    try
    {
        setActions(input);
    }
    catch (const std::runtime_error &excpt)
    {
        std::cout << excpt.what() << std::endl;
        return;
    }
    printMaze();
    grid.at(player.getPosY()).at(player.getPosX()) = '.';
    std::cout << std::endl;
    performActions(actions);
}
void Maze::setActions(std::ifstream &input)
{   

    while (!input.eof())
    {
        char action;
        input >> action;
        if (action != 'u' && action != 'd' && action != 'l' && action != 'r')
        {
            throw std::runtime_error("an error occurred: invalid move");
        }
        actions.push_back(action);
    }
    actions.pop_back();
    input.close();
}

void Maze::performActions(std::vector<char> directions)
{
    try
    {
        for (int i = 0; i < directions.size(); i++)
        {
            switch (directions.at(i))
            {
            case 'u':
                if (grid.at(player.getPosY() - 1).at(player.getPosX()) != 'l')
                {
                    player.setPos(player.getPosX(), player.getPosY() - 1);
                }
                else
                {
                    throw std::runtime_error("an error occurred: player outside maze or off the path");
                }

                break;
            case 'd':

                if (grid.at(player.getPosY() + 1).at(player.getPosX()) != 'l')
                {
                    player.setPos(player.getPosX(), player.getPosY() + 1);
                }
                else
                {
                    throw std::runtime_error("an error occurred: player outside maze or off the path");
                }

                break;
            case 'l':
                if (grid.at(player.getPosY()).at(player.getPosX() - 1) != 'l')
                {
                    player.setPos(player.getPosX() - 1, player.getPosY());
                }
                else
                {
                    throw std::runtime_error("an error occurred: player outside maze or off the path");
                }

                break;
            case 'r':

                if (grid.at(player.getPosY()).at(player.getPosX() + 1) != 'l')
                {
                    player.setPos(player.getPosX() + 1, player.getPosY());
                }
                else
                {
                    throw std::runtime_error("an error occurred: player outside maze or off the path");
                }

                break;
            default:
                throw std::runtime_error("an error occurred: invalid move");
            }
        }
    }
    catch (const std::runtime_error &excpt)
    {
        std::cout << excpt.what() << std::endl;
        return;
    }
    grid.at(player.getPosY()).at(player.getPosX()) = 'P';
    this->printMaze();
    if (player.getPosX() == exitCol && player.getPosY() == exitRow)
    {
        std::cout << std::endl;
        std::cout << "The player reached the exit!" << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "The player did not reach the exit." << std::endl;
    }
}

void Maze::setPerson(Person &p, std::ifstream &input)
{

    int row;
    int col;
    input >> row;
    input >> col;
    p.setPos(col, row);

    if (row > grid.size() || col > grid.at(0).size() || row < 0 || col < 0 || grid.at(row).at(col) == 'l')
    {
        throw std::runtime_error("an error occurred: player outside maze or off the path");
    }
    grid.at(p.getPosY()).at(p.getPosX()) = 'P';
}
void Maze::setExitAndPlayer(std::ifstream &input)
{
    input >> exitRow;
    input >> exitCol;
    if (!input.fail())
    {
    }
    else
    {
        throw std::runtime_error("an error occurred: could not read coordinates");
    }

    if (exitRow > grid.size() || exitCol > grid.at(0).size() || exitRow < 0 || exitCol < 0 || grid.at(exitRow).at(exitCol) == 'l')
    {
        throw std::runtime_error("an error occurred: exit outside maze or off the path");
    }

    grid.at(exitRow).at(exitCol) = 'x';
    setPerson(player, input);
}
int main(int argc, char *argv[])
{
    int width;
    int height;

    std::ifstream inputFile;
    try
    {
        if (argc <= 1)
        {
            throw std::runtime_error("an error occurred: no input file name given");
        }

        inputFile.open(argv[1]);

        if (!inputFile.is_open())
        {
            std::string filename = argv[1];
            std::string cantOpenMessage = "an error occurred: could not open input file " + filename;
            throw std::runtime_error(cantOpenMessage);
        }

        inputFile >> height;
        inputFile >> width;

        if (inputFile.fail())
        {
            throw std::runtime_error("an error occurred: could not read height and width of the maze");
        }

        Maze maze1(width, height, inputFile);
        maze1.setExitAndPlayer(inputFile);
        maze1.start(inputFile);
    }
    catch (const std::runtime_error &excpt)
    {
        std::cout << excpt.what() << std::endl;
        return 0;
    }

    return 0;
}
