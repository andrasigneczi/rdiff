#ifndef __PARAMERTERS_H__
#define __PARAMERTERS_H__
#include <string>
#include <memory>

class Parameters final {
public:
    enum class Function {
        SIGNATURE,
        DELTA,
        PATCH,
        INVALID
    };

    enum class ErrorCode {
        INVALID_FUNCTION,
        INVALID_PARAMETER_COUNT,
        INVALID_HASH_FUNCTION,
        OK
    };

    enum class HashFunction {
        POLYNOMIAL_ROLLING_HASH,
        CYCLIC_POLYNOMIAL_ROLLING_HASH,
    };

    Parameters(int argc, const char *argv[]) noexcept;

    [[nodiscard]]bool verbose() const noexcept {return verbose_;}
    [[nodiscard]]Function function() const noexcept {return function_;}
    [[nodiscard]]const std::string& oldFileName() const noexcept {return oldFileName_;}
    [[nodiscard]]const std::string& newFileName() const noexcept {return newFileName_;}
    [[nodiscard]]const std::string& signatureFileName() const noexcept {return signatureFileName_;}
    [[nodiscard]]const std::string& deltaFileName() const noexcept {return deltaFileName_;}
    [[nodiscard]]bool valid() const noexcept;
    [[nodiscard]]const std::string& error() const noexcept {return error_;}
    [[nodiscard]]ErrorCode errorCode() const noexcept {return errorCode_;}
    [[nodiscard]]HashFunction hashFunction() const noexcept {return hashFunction_;}
    [[nodiscard]]bool statistics() const noexcept {return statistics_;}
    [[nodiscard]]bool debug() const noexcept {return debug_;}

private:
    void setError(ErrorCode code) noexcept;
    void paramCountCheck() noexcept;
    static void displayHelp() noexcept;
    bool setFileNames(const char *argv[], int i);

    bool verbose_{};
    Function function_{Function::INVALID};
    std::string oldFileName_;
    std::string newFileName_;
    std::string signatureFileName_;
    std::string deltaFileName_;
    std::string error_;
    ErrorCode errorCode_{ErrorCode::OK};
    HashFunction hashFunction_{HashFunction::CYCLIC_POLYNOMIAL_ROLLING_HASH};
    bool statistics_{};
    bool debug_{};
};

using ParametersUPtr = std::unique_ptr<Parameters>;

#endif
