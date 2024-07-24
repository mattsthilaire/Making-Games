#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

std::set<std::pair<int, int>> read_level_file(std::string filename)
{
    std::ifstream file(filename);
    std::set<std::pair<int, int>> p;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string token;
        int first, second;

        if (std::getline(ss, token, ','))
        {
            first = std::stoi(token);
        }
        if (std::getline(ss, token, ','))
        {
            second = std::stoi(token);
        }

        p.insert(std::make_pair(first, second));
    }

    file.close();

    return p;
}