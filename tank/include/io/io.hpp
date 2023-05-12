#if !defined(_IO_HPP_)
#define _IO_HPP_

#include <string>

#include "element/map.hpp"
#include "element/tank.hpp"

class GameStage;

class IO
{
public:
    static void load(std::string path, GameStage *stage);
    static void save(std::string path, GameStage *stage);
    static void saveMap(FILE *f, Map *map);
    static void loadMap(FILE *f, GameStage *stage, int x, int y, int rows, int cols, STATUS status);
    static void saveTank(FILE *f, Tank *tank);
    static void loadTank(FILE *f, GameStage *stage, int x, int y, int rows, int cols, STATUS status);
};



#endif // _IO_HPP_
