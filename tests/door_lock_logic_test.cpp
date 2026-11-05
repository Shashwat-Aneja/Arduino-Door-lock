#include <assert.h>
#include <stdint.h>
#include "../src/PasswordInput.h"
#include "../src/LockTiming.h"

int main() {
    PasswordInput input;
    assert(input.length() == 0);
    assert(!input.matches("1234"));

    assert(input.appendDigit('1'));
    assert(input.appendDigit('2'));
    assert(input.appendDigit('3'));
    assert(input.appendDigit('4'));
    assert(input.length() == 4);
    assert(input.matches("1234"));
    assert(!input.appendDigit('5'));
    assert(!input.appendDigit('A'));
    assert(!input.appendDigit('*'));

    input.clear();
    assert(input.length() == 0);
    assert(!input.matches("1234"));
    assert(input.appendDigit('1'));
    assert(!input.matches("1234"));

    assert(!lockTimeoutElapsed(109U, 100U, 10U));
    assert(lockTimeoutElapsed(110U, 100U, 10U));
    assert(!lockTimeoutElapsed(0x000026FFU, 0xFFFFFFF0U, 10000U));
    assert(lockTimeoutElapsed(0x00002700U, 0xFFFFFFF0U, 10000U));

    return 0;
}
