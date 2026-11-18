#ifndef DOOR_LOCK_PASSWORD_INPUT_H
#define DOOR_LOCK_PASSWORD_INPUT_H

#include <stddef.h>
#include <string.h>

class PasswordInput {
public:
    enum { MAX_LENGTH = 4 };

    PasswordInput() : length_(0), overflowed_(false) {
        buffer_[0] = '\0';
    }

    bool appendDigit(char key) {
        if (key < '0' || key > '9') {
            return false;
        }
        if (length_ >= MAX_LENGTH || overflowed_) {
            overflowed_ = true;
            return false;
        }
        buffer_[length_++] = key;
        buffer_[length_] = '\0';
        return true;
    }

    bool matches(const char* expected) const {
        return !overflowed_ && expected != NULL
            && length_ == MAX_LENGTH
            && strlen(expected) == MAX_LENGTH
            && strcmp(buffer_, expected) == 0;
    }

    void clear() {
        length_ = 0;
        overflowed_ = false;
        buffer_[0] = '\0';
    }

    size_t length() const {
        return length_;
    }

private:
    char buffer_[MAX_LENGTH + 1];
    size_t length_;
    bool overflowed_;
};

#endif

