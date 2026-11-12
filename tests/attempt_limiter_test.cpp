#include <assert.h>
#include <stdint.h>
#include "../src/AttemptLimiter.h"

int main() {
    AttemptLimiter limiter(3, 30000U);
    assert(!limiter.isLocked(100U));
    limiter.recordFailure(100U);
    limiter.recordFailure(200U);
    assert(limiter.failures() == 2);
    assert(!limiter.isLocked(300U));
    limiter.recordFailure(300U);
    assert(limiter.isLocked(300U));
    limiter.recordFailure(400U);
    assert(limiter.failures() == 3);
    assert(limiter.isLocked(30299U));
    assert(!limiter.isLocked(30300U));
    assert(limiter.failures() == 0);

    limiter.recordFailure(0xFFFFFFF0U);
    limiter.recordFailure(0xFFFFFFF1U);
    limiter.recordFailure(0xFFFFFFF2U);
    assert(limiter.isLocked(0x00000010U));
    assert(limiter.isLocked(0x00007521U));
    assert(!limiter.isLocked(0x00007522U));

    limiter.recordFailure(123U);
    limiter.reset();
    assert(limiter.failures() == 0);
    assert(!limiter.isLocked(124U));
    return 0;
}
