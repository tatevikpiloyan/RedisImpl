#include <algorithm>

#include "headerFiles/parser.h"

void toLowercase(std::string& str)
{
    int size = str.size();
    for (int i = 0; i < size; ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] += 32;
        }
    }
}

std::vector<std::string> parser(const std::string& str, const std::string& spliter)
{
    std::vector<std::string> nstr;
	std::string tstr;
	for (int i = 0; i < str.size(); ++i)
    {
		if (spliter.find(str[i]) != std::string::npos)
        {   
            if (!tstr.empty())
            {
			    nstr.push_back(tstr);
			    tstr.clear();
			    continue;
            }
            continue;
		}
		tstr.push_back(str[i]);
	}
    if (!tstr.empty())
    {
	    nstr.push_back(tstr);
    }
	return nstr;
}

std::string toString(std::vector<std::string>& vec)
{
    std::string tmp;
    for (auto& it : vec)
    {
        tmp += it;
    }
    return tmp;
}