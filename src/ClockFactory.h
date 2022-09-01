#ifndef __CLOCKFACTORY_H__
#define __CLOCKFACTORY_H__

#include "ClockInterface.h"
#include <string>

class ClockFactory final {
    friend class RdiffBuilder;
    enum class ClockType {
        DUMMY,
        REAL
    };

    ClockFactory(ClockType clockType) : clockType_(clockType) {}

public:
    [[nodiscard]] ClockInterfaceUPtr create(std::string_view name);

private:
    ClockType clockType_;
};

#endif // __CLOCKFACTORY_H__
