#include "ClockFactory.h"
#include "ClockReal.h"
#include "ClockDummy.h"

ClockInterfaceUPtr ClockFactory::create(std::string_view name) {
    switch(clockType_) {
    case ClockType::DUMMY:
        return ClockInterfaceUPtr(new ClockDummy());
    case ClockType::REAL:
        return ClockInterfaceUPtr(new ClockReal(name.data()));
    }
    return nullptr;
}
