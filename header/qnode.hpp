#pragma once

struct QNode {
    bool locked{false};
    std::shared_ptr<QNode> next{nullptr};
    QNode(): locked(false), next(nullptr) {}
};