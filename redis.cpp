#include <iostream>
#include <algorithm>

#include "redis.h"
#include "parser.h"

Redis::Redis()
{
    this->init();

    file.open("DB/database.json");
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open database!");
    }
    
    std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    if (!jsonString.empty())
    {
        database = nlohmann::json::parse(jsonString);
    }

    file.close();
    if (file.is_open())
    {
        throw std::runtime_error("Unable to close database!");
    }


}

void Redis::init()
{
    commandMap["set"] = Command::SET;
    commandMap["get"] = Command::GET;
    commandMap["hset"] = Command::HSET;
    commandMap["hget"] = Command::HGET;
    commandMap["lrange"] = Command::LRANGE;

    exitMap["exit"] = Exit::EXIT;
    exitMap["quit"] = Exit::QUIT;

    functionMap[Command::SET] = &Redis::SET;
    functionMap[Command::GET] = &Redis::GET;
    functionMap[Command::HSET] = &Redis::HSET;
    functionMap[Command::HGET] = &Redis::HGET;
    functionMap[Command::LRANGE] = &Redis::LRANGE;
}

void Redis::run()
{
    std::string input;
    while (true)
    {
        try
        {
            getline(std::cin, input);
            if (static_cast<bool>(exitMap[input])) { return; }
            execute(input);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        
    }
}

void Redis::execute(const std::string& input)
{

    if (input.empty()) { return; }
    std::vector<std::string> parsed = parser(input, " ");
    auto command = parsed.begin();
    toLowercase(*command);
    if (!static_cast<bool>(commandMap[*command]))
    {
        throw std::invalid_argument("Invalid command!");
    }
    std::vector<std::string> datas(command + 1, parsed.end());
    (this->*functionMap[commandMap[*command]])(datas);
}

void Redis::SET(std::vector<std::string>& data)
{
    if (data.size() != SET_SIZE)
    {
        throw std::invalid_argument("Invalid syntax!");
    }
    auto keyIt = data.begin();
    auto valueIt = keyIt + 1;
    for (auto& it : database)
    {
        if (it.items().begin().key() == *keyIt)
        {
            it.begin().value() = *valueIt;
            return;
        }
    }
    nlohmann::json tmp;
    tmp[*keyIt] = *valueIt;
    database.push_back(tmp);
}

void Redis::GET(std::vector<std::string>& data)
{
    if (data.size() != GET_SIZE)
    {
        throw std::invalid_argument("Invalid syntax!");
    }
    auto keyIt = data.begin();
    for (auto& it : database)
    {
        if (it.items().begin().key() == *keyIt)
        {
            std::cout << it.items().begin().value() << std::endl;
            return;
        }
    }
    throw std::invalid_argument("nill");
}

void Redis::HSET(std::vector<std::string>& values)
{
    
}

void Redis::HGET(std::vector<std::string>& values)
{
    
}

void Redis::LRANGE(std::vector<std::string>& values)
{
    
}

Redis::~Redis()
{
    file.open("DB/database.json");
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open database!");
    }
    file << database.dump(4);
    file.close();
    if (file.is_open())
    {
        throw std::runtime_error("Unable to close database!");
    }
}