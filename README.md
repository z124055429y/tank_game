# TankGame

## 简述

- 采用cmake管理工程
- 采用GoogleTest作为单元测试框架
- 所有库中包括三个子目录
  - include：存放头文件
  - src：存放源代码
  - test：存放单元测试
- game工程依赖ncurses库、tank库
- game负责计时刷新和渲染元素
- tank库不依赖ncurses库，做到ui和游戏逻辑解耦
- tank库只暴露`engine.h`，标准化交互接口，方便动态库替换
- 算法优化，操作行为时间复杂度均小于等于`O(n)`
- 输入字符转化成指令，传递给引擎解析
- 子弹连发会出现后一个子弹追上前一个子弹的问题, 当前采用方案: 限制子弹发射频率大于子弹速度
- 碰撞处理: A比B层数高, 不产生碰撞; 否则产生碰撞

## 可优化

- 坦克画笔类 写死了方向和位图关系，坦克的绘制可采用矩阵乘法
- 对三个子弹同时碰撞情况的处理，同时销毁三个子弹，而不是两个销毁，另一个不影响
- 两个坦克长按按钮情况下操作, 只有一个在移动 (命令行如何在一个按键按下的同时，继续接收其他的按键输入的问题)
- 当前坦克只能被子弹销毁，思考如何让坦克碰撞也销毁
- 一些容器可以用set代替list, 进而降低删除的时间复杂度
