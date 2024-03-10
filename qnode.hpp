#pragma once

struct QNode {
    bool locked{false};
    QNode* next{nullptr};
};