#if !defined(_DIRECTION_HPP_)
#define _DIRECTION_HPP_

/// 定义行为
constexpr int MASK_DIRECTION    = 0x0f;
constexpr int MASK_ACTION       = 0xff;
constexpr int NONE              = 0;
constexpr int LEFT              = 1;
constexpr int DOWN              = 1 << 1;
constexpr int UP                = 1 << 2;
constexpr int RIGHT             = 1 << 3;
constexpr int FIRE              = 1 << 4;

// 定义坦克类型
constexpr int MASK_PLAYER_ID    = 0x0300;
constexpr int PLAYER_ID_1       = 1 << 8;
constexpr int PLAYER_ID_2       = 1 << 9;
constexpr int ENERMY_ID_1       = 1 << 10;
constexpr int ENERMY_ID_2       = 1 << 11;
constexpr int ENERMY_ID_3       = 1 << 12;

/// 方便后期替换类型
typedef int STATUS;

constexpr int MASK_LAYER = 0xff00;
constexpr int LAYER_1  = 1 << (0 + 8);
constexpr int LAYER_2  = 1 << (1 + 8);
constexpr int LAYER_3  = 1 << (2 + 8);
constexpr int LAYER_4  = 1 << (3 + 8);
constexpr int LAYER_5  = 1 << (4 + 8);
constexpr int LAYER_6  = 1 << (5 + 8);
constexpr int LAYER_7  = 1 << (6 + 8);
constexpr int LAYER_8  = 1 << (7 + 8);

#endif // _DIRECTION_HPP_
