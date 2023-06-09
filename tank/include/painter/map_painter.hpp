#if !defined(_MAP_PAINTER_HPP_)
#define _MAP_PAINTER_HPP_

#include "element/map.hpp"

/**
 * 地图画笔
*/
class MapPainter
{
private:
    
public:
    /// @brief 绘制地图
    void draw(Map *map) {
        if (map == nullptr) return;
        Map &m = *map;

        int rows, cols;
        int **bitmap = map->getBitmap(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                switch (m[i][j] & MASK_LAND)
                {
                    case LAND_BORDER:       bitmap[i][j] = '#'; break;
                    case LAND_IRON_WALL:    bitmap[i][j] = '#'; break;
                    case LAND_GRASS:        bitmap[i][j] = 'Y'; break;
                    case LAND_RIVER:        bitmap[i][j] = '~'; break;
                    case LAND_MUD_WALL:     bitmap[i][j] = '^'; break;
                    default:                bitmap[i][j] = ' '; break;
                }
            }
        }
    }
};


#endif // _MAP_PAINTER_HPP_
