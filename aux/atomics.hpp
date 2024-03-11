#pragma once

template <typename T>
static inline T get(T *ptr) {
    T ret;
    __asm__ __volatile__("ldaxr %0, [%1]\n"
                         : "=&r"(ret)
                         : "r"(ptr)
                         : "memory");
    return ret;
}


template <typename T>
int compareAndSet(T *ptr, T *oldValPtr, T *newValPtr) {
    int ret;
    int res;
    T oldVal = *oldValPtr;
    T newVal = *newValPtr;
    __asm__ __volatile__("1:\n"
                         "ldaxr %w0, [%2]\n"
                         "mov %w1, %w0\n"
                         "cmp %w0, %w3\n"
                         "b.ne 2f\n"
                         "mov %w0, %w4\n"
                         "stlxr %w1, %w0, [%2]\n"
                         "cbnz %w1, 1b\n"
                         "2:\n"
                         : "=&r"(ret), "=&r"(res), "+r"(ptr)
                         : "r"(oldVal), "r"(newVal)
                         : "cc", "memory");
    return ret;
}

template <typename T>
T getAndSet(T *ptr, T *newValPtr) {
    T ret;
    int res;
    T newVal = *newValPtr;
    __asm__ __volatile__("1:\n"
                         "ldaxr %0, [%2]\n"
                         "stlxr %w1, %w3, [%2]\n"
                         "cbnz %w1, 1b\n"
                         : "=&r"(ret), "=&r"(res), "+r"(ptr)
                         : "r"(newVal)
                         : "cc", "memory");
    return ret;
}

template <typename T>
T getAndIncrement(T *ptr) {
    T ret;
    int res;
    T newVal;
    __asm__ __volatile__("1:\n"
                         "ldaxr %0, [%3]\n"
                         "add %w1, %w0, #1\n"
                         "stlxr %w2, %w1, [%3]\n"
                         "cbnz %w2, 1b\n"
                         : "=&r"(ret), "=&r"(newVal), "=&r"(res), "+r"(ptr)
                         :
                         : "cc", "memory");
    return ret;
}

