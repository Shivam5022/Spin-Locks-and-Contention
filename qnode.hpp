#pragma once

struct QNode {
    bool locked{false};
    QNode* next{nullptr};
    QNode(): locked(false), next(nullptr) {}
};