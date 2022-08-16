#include <iostream>
#include "Parameters.h"
#include "RdiffBuilder.h"

int main(int argc, const char * argv[]) try {
    ParametersUPtr p = std::make_unique<Parameters>(argc, argv);
    if(!p->valid()) {
        std::cerr << p->error() << "\n";
    } else {
        RdiffUPtr rdiff = RdiffBuilder::build(std::move(p));
        rdiff->execute();
    }
    return EXIT_SUCCESS;
} catch(const std::runtime_error& x) {
    std::cerr << "ERROR: " << x.what() << "\n";
    return EXIT_FAILURE;
}
