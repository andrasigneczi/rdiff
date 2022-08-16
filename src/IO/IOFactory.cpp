#include "IOFactory.h"
#include "FileInput.h"
#include "FastFileInput.h"
#include "FileOutput.h"
#include "FastFileOutput.h"
#include <iostream>

// file://host/path
// file:///foo.txt
InputInterfaceUPtr IOFactory::createInput(std::string URI) {
    bool isURI = URI.find("://") != std::string::npos;
    bool isLocalFile = false;

    if(isURI) {
        bool fileURI = URI.starts_with("file:///");
        if(fileURI) {
            URI = URI.substr(7);
            //std::cout << URI << "\n";
            isLocalFile = true;
        } else {

        }
    } else {
        isLocalFile = true;
    }

    if(isLocalFile) {
        return InputInterfaceUPtr(new FastFileInput(URI));
    }
    throw std::runtime_error("Illegal input format");
}

OutputInterfaceUPtr IOFactory::createOutput(std::string URI) {
    bool isURI = URI.find("://") != std::string::npos;
    bool isLocalFile = false;

    if(isURI) {
        bool fileURI = URI.starts_with("file:///");
        if(fileURI) {
            URI = URI.substr(7);
            isLocalFile = true;
        } else {

        }
    } else {
        isLocalFile = true;
    }

    if(isLocalFile) {
        return OutputInterfaceUPtr(new FastFileOutput(URI));
    }
    throw std::runtime_error("Illegal output format");
}
