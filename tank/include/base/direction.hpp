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

#endif // _DIRECTION_HPP_
