#include "Parameters.h"
#include <iostream>

Parameters::Parameters(int argc, const char *argv[]) noexcept {
    for(int i = 1; i < argc; ) {
        if(std::string_view(argv[i]) == "-v") {
            verbose_ = true;
        } else if(std::string_view(argv[i]) == "-vv") {
            debug_ = true;
        } else if(std::string_view(argv[i]) == "-h") {
                displayHelp();
                return;
        } else if(std::string_view(argv[i]) == "-hash") {
            if(i + 1 == argc) {
                setError(ErrorCode::INVALID_PARAMETER_COUNT); // invalid parameter // argv[i]
                return;
            } else if(std::string_view(argv[i + 1]) != "1" && std::string_view(argv[i + 1]) != "2") {
                setError(ErrorCode::INVALID_HASH_FUNCTION); // invalid parameter // argv[i]
                return;
            }
            if(argv[i + 1][0] == '1') {
                hashFunction_ = HashFunction::POLYNOMIAL_ROLLING_HASH;
            } else {
                hashFunction_ = HashFunction::CYCLIC_POLYNOMIAL_ROLLING_HASH;
            }
            ++i;
        } else if(std::string_view(argv[i]) == "-s") {
            statistics_ = true;
        } else if(std::string_view(argv[i]) == "signature") {
            function_ = Function::SIGNATURE;
        } else if(std::string_view(argv[i]) == "delta") {
            function_ = Function::DELTA;
        } else if(std::string_view(argv[i]) == "patch") {
            function_ = Function::PATCH;
        } else if(function_ != Function::INVALID) {
            if(!setFileNames(argv, i)) return;
        } else {
            setError(ErrorCode::INVALID_FUNCTION); // argv[i]
            return;
        }
        ++i;
    }

    paramCountCheck();
}

bool Parameters::setFileNames(const char *argv[], int i) {
    switch(function_) {
    case Function::SIGNATURE:
        if(!oldFileName_.length()) {
            oldFileName_ = argv[i];
        } else if(!signatureFileName_.length()) {
            signatureFileName_ = argv[i];
        } else {
            setError(ErrorCode::INVALID_PARAMETER_COUNT); // invalid parameter // argv[i]
            return false;
        }
        break;
    case Function::DELTA:
        if(!signatureFileName_.length()) {
            signatureFileName_ = argv[i];
        } else if(!newFileName_.length()){
            newFileName_ = argv[i];
        } else if(!deltaFileName_.length()) {
            deltaFileName_ = argv[i];
        } else {
            setError(ErrorCode::INVALID_PARAMETER_COUNT); // invalid parameter // argv[i]
            return false;
        }
        break;
    case Function::PATCH:
        if(!oldFileName_.length()) {
            oldFileName_ = argv[i];
        } else if(!deltaFileName_.length()) {
            deltaFileName_ = argv[i];
        } else if(!newFileName_.length()){
            newFileName_ = argv[i];
        } else {
            setError(ErrorCode::INVALID_PARAMETER_COUNT); // invalid parameter // argv[i]
            return false;
        }
        break;
    case Function::INVALID: return false;
    }
    return true;
}

bool Parameters::valid() const noexcept {
    switch(function_) {
    case Function::SIGNATURE: return oldFileName_.length() && signatureFileName_.length() && !error_.length();
    case Function::DELTA: return signatureFileName_.length() && newFileName_.length() && deltaFileName_.length() && !error_.length();
    case Function::PATCH: return oldFileName_.length() && newFileName_.length() && deltaFileName_.length() && !error_.length();
    case Function::INVALID:
        return false;;
    }
    return false;
}

void Parameters::setError(ErrorCode code) noexcept {
    errorCode_ = code;
    switch(errorCode_) {
    case ErrorCode::INVALID_FUNCTION: error_ = "Invalid function"; break;
    case ErrorCode::INVALID_PARAMETER_COUNT: error_ = "Invalid parameter count"; break;
    case ErrorCode::INVALID_HASH_FUNCTION: error_ = "Invalid hash function"; break;
    case ErrorCode::OK: break;
    }
}

void Parameters::paramCountCheck() noexcept {
    if(function_ == Function::SIGNATURE && !error_.length() && (!oldFileName_.length() || !signatureFileName_.length())) {
        setError(ErrorCode::INVALID_PARAMETER_COUNT);
    } else if(function_ == Function::DELTA && !error_.length() && (!signatureFileName_.length() || !newFileName_.length() || !deltaFileName_.length())) {
        setError(ErrorCode::INVALID_PARAMETER_COUNT);
    } else if(function_ == Function::PATCH && !error_.length() && (!oldFileName_.length() || !newFileName_.length() || !deltaFileName_.length())) {
        setError(ErrorCode::INVALID_PARAMETER_COUNT);
    } else if(!error_.length() && !signatureFileName_.length() && !oldFileName_.length() && !newFileName_.length() && !deltaFileName_.length() &&
              function_ == Function::INVALID) {
        displayHelp();
    }
}

void Parameters::displayHelp() noexcept {
    std::cout << "Usage:\trdiff [-h]\n" <<
                 "\trdiff [OPTIONS] signature basis-file signature-file\n" <<
                 "\trdiff [OPTIONS] delta signature-file new-file delta-file\n" <<
                 "\trdiff [OPTIONS] patch basis-file delta-file new-file\n" <<
                 "\n" <<
                 "\t Options:\n" <<
                 "\t    -h           Show this help message\n" <<
                 "\t    -v           Trace internal processing\n" <<
                 "\t    -vv          Trace internal processing + some debug information\n" <<
                 "\t    -hash 1      Set hash function to Polynomial rolling hash\n" <<
                 "\t    -hash 2      Set hash function to Cyclic polynomial rolling hash (default)\n" <<
                 "\t                 The hash function is saved in the signature and delta files,\n" <<
                 "\t                 '-hash' parameter is ignored during delta and patch processes\n" <<
                 "\t    -s           Show performance statistics\n";
}
