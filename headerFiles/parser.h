#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

void toLowercase(std::string&);
std::vector<std::string> parser(const std::string&, const std::string&);
std::string toString(std::vector<std::string>&);

#endif // PARSER_H