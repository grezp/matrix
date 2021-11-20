#include "parse.h"
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

void PARSE::FileData::Print(const std::size_t &colWidth, const std::string &delim, std::ostream &out)
{
    // std::string headerName ("      FileDataDump      ");
    char commentType = '/';
    int minCommentSize = 2;
    char prevFill (std::cout.fill());
    std::vector<std::string>::const_iterator tIt;
    std::vector<std::vector<std::string> >::const_iterator lIt;
    std::vector<std::vector<std::string> >::const_iterator bIt(tokens.begin());

    // Display the header
    // out << std::setfill(commentType) << std::setw(headerName.size()+(minCommentSize*2)) << "" << std::endl;
    // out << std::setfill(commentType) << std::setw(minCommentSize) << "" << headerName << std::setfill(commentType) << std::setw(minCommentSize) << "" << std::endl;
    // out << std::setfill(commentType) << std::setw(headerName.size()+(minCommentSize*2)) << "" << std::endl;

    // reset fill stream
    out << std::setfill(prevFill);

    // dump the file contents
    for(lIt=tokens.begin(); lIt!=tokens.end(); lIt++)
    {
        out << "[" << lIt-bIt << "]:";
        for(tIt=lIt->begin(); tIt!=lIt->end(); tIt++)
            out << std::setw(colWidth) << std::right << *tIt << ",";
        out << std::endl;
    }

}

void PARSE::FileData::Clear()
{
    path="";
    name="";
    delim="";
    comment="";
    tokens.clear();
}

std::vector<std::string> PARSE::Tokenize(const std::string &str, const std::string &delim)
{
    std::string strCopy (str);
    std::vector<std::string> tokenizedString;

    strCopy = Trim(strCopy);
    strCopy = Reduce(strCopy);

    // Find the first instance of the delimiter
    std::size_t beginDelim = strCopy.find_first_of(delim);
    while (strCopy.size())
    {
        if (beginDelim == std::string::npos)
            beginDelim = strCopy.size();

        // create a substring based on the delimiter
        std::string token(strCopy, 0, beginDelim);

        // save the token
        token = Trim(token);
        if (token!="")
            tokenizedString.push_back(token);

        // erase the token from the original string
        strCopy.erase(0, beginDelim+1);
        beginDelim = strCopy.find_first_of(delim);
    }

    return tokenizedString;
} // end Tokenize

std::string PARSE::Trim(const std::string &str, const std::string &whitespace)
{
    const std::size_t strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const std::size_t strEnd = str.find_last_not_of(whitespace);
    const size_t strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string PARSE::Reduce(const std::string &str, const std::string &fill, const std::string &whitespace)
{
    std::string result (str);
    std::size_t beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const std::size_t endSpace = result.find_first_not_of(whitespace, beginSpace);
        const std::size_t range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const std::size_t newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

bool PARSE::ReadFile(FileData &fileData)
{
    // Local variables
    bool returnVar = true;
    std::size_t comLoc;
    std::string lineStr;
    std::vector<std::string> lineTokens;
    std::ifstream inFile((fileData.path + fileData.name).c_str(), std::ifstream::in);

    // Iterate through all rows until EOF is reached
    while(inFile.good())
    {
        // Get current line in the file
        std::getline(inFile, lineStr);

        // If the comment string is present find it and delete all following data
        comLoc=lineStr.find_first_of(fileData.comment);
        if (comLoc!=std::string::npos)
            lineStr.erase(comLoc);

        // Tokenize the line based on the delim
        lineTokens = Tokenize(lineStr, fileData.delim);

        // Save all the tokens present on the line
        if (lineTokens.size()!=0)
            fileData.tokens.push_back(lineTokens);
    }

    if (inFile.is_open())
    {
        inFile.close();
        // std::cout << "PARSE::ReadFile: The following file was succesfully read, \"" << fileData.path + fileData.name << "\"." << std ::endl;
    }
    else
    {
        std::cout << "PARSE::ReadFile: The following file could not be opened, \"" << fileData.path + fileData.name << "\"." << std ::endl;
        returnVar = false;
    }

    return returnVar;
}

int PARSE::UserInput(int minVal, int maxVal, bool negFlag)
{
    int userNum;
    bool isValid = false;
    std::string errMessage ("Invalid input. Please enter an integer between "
            + std::to_string(minVal) + " and " + std::to_string(maxVal));

    do {
        int isNumCount = 0;
        bool decimalFlag = false;
        std::string userNumStr;
        std::cin >> userNumStr;

        // accept negative numbers
        if (negFlag && userNumStr[0] == '-')
            isNumCount++;

        // iterate through str & check if valid #
        for (int i = 0; i < userNumStr.size(); i++) {
            if (isdigit(userNumStr[i]))
                isNumCount++;

            if (userNumStr[i] == '.')
                decimalFlag = true;
        }

        // check if decimal was added
        if (decimalFlag)
            isNumCount = 0;

        // check if str input size matches count
        // if valid, convert num
        if (isNumCount == userNumStr.size()) {
            std::stringstream strStream(userNumStr);
            strStream >> userNum;

            isValid = true;
        }
        else
            std::cout << errMessage << std::endl;

        // check for range before breaking
        if ( isValid && ((userNum < minVal) || (userNum > maxVal)) )
            std::cout << errMessage << std::endl;

        // clear cin error flag & ignore rest of the stream
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (!isValid);

    return userNum;
}

bool PARSE::isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
