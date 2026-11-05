#ifndef DOOR_LOCK_PASSWORD_INPUT_H
#define DOOR_LOCK_PASSWORD_INPUT_H

#include <stddef.h>
#include <string.h>

class PasswordInput {
public:
    enum { MAX_LENGTH = 4 };

    PasswordInput() : length_(0) {
        buffer_[0] = '\0';
    }

    bool appendDigit(char key) {
        if (key < '0' || key > '9' || length_ >= MAX_LENGTH) {
            return false;
        }
        buffer_[length_++] = key;
        buffer_[length_] = '\0';
        return true;
    }

    bool matches(const char* expected) const {
        return expected != NULL
            && length_ == strlen(expected)
            && strcmp(buffer_, expected) == 0;
    }

    void clear() {
        length_ = 0;
        buffer_[0] = '\0';
    }

    size_t length() const {
        return length_;
    }

private:
    char buffer_[MAX_LENGTH + 1];
    size_t length_;
};

#endif
