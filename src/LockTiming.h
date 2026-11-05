#ifndef DOOR_LOCK_TIMING_H
#define DOOR_LOCK_TIMING_H

#include <stdint.h>

// Unsigned subtraction keeps the timeout correct across the 32-bit millis()
// counter rollover used by Arduino boards.
inline bool lockTimeoutElapsed(uint32_t now, uint32_t unlockedAt, uint32_t timeoutMs) {
    return static_cast<uint32_t>(now - unlockedAt) >= timeoutMs;
}

#endif
