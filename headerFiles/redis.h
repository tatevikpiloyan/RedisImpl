#ifndef REDIS_H
#define REDIS_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "enum.h"

class Redis
{
public:
    Redis();
    ~Redis();

public:
    void run();
    void execute(const std::string&);
    void SET(std::vector<std::string>&);
    void GET(std::vector<std::string>&);
    void HSET(std::vector<std::string>&);
    void HGET(std::vector<std::string>&);
    void LRANGE(std::vector<std::string>&);

private:
    void init();

private:
    using FuncPointer = void (Redis::*)(std::vector<std::string>&);
    std::map<std::string, Command> commandMap;
    std::map<std::string, Exit> exitMap;
    std::map<Command, FuncPointer> functionMap;
    std::fstream file;
    nlohmann::json database;

private:
    static const int SET_SIZE = 2;
    static const int GET_SIZE = 1;

};


#endif // REDIS_H