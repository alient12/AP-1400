#ifndef Q2_H
#define Q2_H

#include<regex>
#include <fstream>

namespace q2
{
struct Patient
{
	std::string name;
	size_t age;
	size_t smokes;
	size_t area_q;
	size_t alkhol;
};

inline std::vector<Patient> read_file(std::string filename)
{
    std::vector<Patient> patients;
    // std::regex rx("(\\w+),(\\w+),(\\d+),(\\d+),(\\d+),(\\d+)");
    std::regex rx(R"((\w+)\s*,(\w+)\s*,(\d+),(\d+),(\d+),(\d+)\s*)");
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        std::smatch match;
        if (std::regex_match(line, match, rx))
        {
            Patient p;
            p.name = std::string(match[1]) + " " + std::string(match[2]);
            p.age = std::stoi(match[3]);
            p.smokes = std::stoi(match[4]);
            p.area_q = std::stoi(match[5]);
            p.alkhol = std::stoi(match[6]);
            patients.push_back(p);
        }
    }
    return patients;
}
}

#endif //Q2_H