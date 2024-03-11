#pragma once

class Lock {
    public:
        virtual void lock() = 0;
        virtual void unlock() = 0;
        virtual void type() = 0;
};