#pragma once

#include <iostream>
#include <vector>

namespace PARSE
{

struct FileData
{
    std::string path;
    std::string name;
    std::string delim;
    std::string comment;
    std::vector<std::vector<std::string> > tokens;

    void Print(const std::size_t &colWidth=10,  const std::string &delim=",", std::ostream &out=std::cout);
    void Clear();
};

std::vector<std::string> Tokenize(const std::string &str, const std::string &delim=" \t");
std::string Trim(const std::string &str, const std::string &whitespace=" \t");
std::string Reduce(const std::string &str, const std::string &fill=" ", const std::string &whitespace=" \t");
bool ReadFile(FileData &fileData);
int UserInput(int minVal, int maxVal, bool negFlag=false);
bool isNumber(const std::string& s);

}
