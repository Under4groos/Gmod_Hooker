#pragma once
#ifndef HEADERS_H // Include guard to prevent multiple inclusions
#define HEADERS_H

#include <string>  // Include for std::string
#include <iostream> // Include for std::cout and std::endl

namespace Console {
    // Function declaration
    void WriteLog(std::string strM, std::string strI);
    void WriteLog(std::string strM);
}

#endif // HEADERS_H