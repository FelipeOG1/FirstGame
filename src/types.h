#pragma once

struct Frame {
    int x, y, w, h;
};

enum class Action {
    IDLE,
    MOVE,
    ATTACK,
    HURT,
    JUMP,
    RUNSHOT
};
