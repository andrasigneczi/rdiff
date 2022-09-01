#ifndef __RDIFFBUILDER_H__
#define __RDIFFBUILDER_H__

#include "Rdiff.h"
#include "Parameters.h"

class RdiffBuilder final {
public:
    [[nodiscard]] static RdiffUPtr build(ParametersUPtr params);
    static void changeHashFunction(Rdiff* rdiff, uint8_t hashFunctionId);

private:
    static void setHashFunction(RdiffUPtr& rdiff, const ParametersUPtr& params);
};

#endif // __RDIFFBUILDER_H__
