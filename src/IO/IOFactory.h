#ifndef __IOFACTORY_H__
#define __IOFACTORY_H__

#include "InputInterface.h"
#include "OutputInterface.h"
#include <string>

class IOFactory {
public:
    [[nodiscard]] static InputInterfaceUPtr createInput(std::string URI);
    [[nodiscard]] static OutputInterfaceUPtr createOutput(std::string URI);
};

#endif // __IOFACTORY_H__
