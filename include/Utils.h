// Purpose: Shared string helpers used by every module (trimming, case-insensitive
//          comparison, splitting records on '|', reading user input).
// Author:  Shared work (all members)
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace utils {

// Removes spaces, tabs, \r and \n from both ends; internal spaces are kept.
std::string trim(const std::string& s);

// Returns a lowercase / uppercase copy (ASCII letters only).
std::string toLower(const std::string& s);
std::string toUpper(const std::string& s);

// Case-insensitive equality of two strings (no trimming).
bool equalsIgnoreCase(const std::string& a, const std::string& b);

// Splits a line on '|' and trims every field.
std::vector<std::string> splitFields(const std::string& line);

// True if the line is blank or its first non-whitespace character is '#'.
bool isBlankOrComment(const std::string& line);

// Prints a prompt and reads one full line from std::cin (trimmed).
// Returns false on end of input.
bool readLine(const std::string& prompt, std::string& out);

// Parses a whole string as a non-negative integer; false if it is not one.
bool parseInt(const std::string& s, int& out);

} // namespace utils

#endif
