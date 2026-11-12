#ifndef DOOR_LOCK_ATTEMPT_LIMITER_H
#define DOOR_LOCK_ATTEMPT_LIMITER_H

#include <stdint.h>
#include "LockTiming.h"

// A short cooldown after repeated failed PIN attempts. Uses unsigned millis()
// arithmetic so the cooldown survives the 32-bit counter rollover.
class AttemptLimiter {
public:
    AttemptLimiter(uint8_t maxFailures, uint32_t cooldownMs)
        : maxFailures_(maxFailures), cooldownMs_(cooldownMs),
          failures_(0), locked_(false), lockedAt_(0) {}

    bool isLocked(uint32_t now) {
        if (locked_ && lockTimeoutElapsed(now, lockedAt_, cooldownMs_)) {
            reset();
        }
        return locked_;
    }

    void recordFailure(uint32_t now) {
        if (isLocked(now)) {
            return;
        }
        if (maxFailures_ > 0 && ++failures_ >= maxFailures_) {
            locked_ = true;
            lockedAt_ = now;
        }
    }

    void reset() {
        failures_ = 0;
        locked_ = false;
        lockedAt_ = 0;
    }

    uint8_t failures() const { return failures_; }

private:
    uint8_t maxFailures_;
    uint32_t cooldownMs_;
    uint8_t failures_;
    bool locked_;
    uint32_t lockedAt_;
};

#endif
