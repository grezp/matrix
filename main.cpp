#include "parse.h"
#include "matrix.h"

bool ReadFromCsv(PARSE::FileData& file)
{
    file.path="../";    //debug
    // file.name="a1.csv"; //debug
    file.delim=",";

    std::cout << "Enter file name to read: \n";
    std::getline(std::cin, file.name);

    bool isFile = PARSE::ReadFile(file);

    if (isFile) {
        std::cout << file.name << ":\n";
        file.Print();
        std::cout << "\n";
    }
}

int main()
{
    bool isRunning = true;

    while(isRunning) {
        std::cout << "What would you like to do?\nEnter:"
                  << "\t'0' ---- to close\n"
                  << "\t'1' ---- to multiply matrices\n"
                  << "\t'2' ---- to transpose matrices\n";
    
        int userCmd = PARSE::UserInput(0, 2);
        std::cout << "\n";
        
        switch (userCmd) {
            case 0 :
                // exit application
                isRunning = false;
                break;
            case 1 : {
                // multiply matrices
                PARSE::FileData fileData1, fileData2;
                if (ReadFromCsv(fileData1) && ReadFromCsv(fileData2)) {
                    Matrix a1, a2, a3;
                    if (a1.ConvertFromStrings(fileData1.tokens)
                    &&  a2.ConvertFromStrings(fileData2.tokens)) {
                        a3 = a1.Multiply(a2);
                        std::cout << "Result: \n";
                        a3.Print();
                        std::cout << "\n";
                    }
                }
                break;
            }
            case 2 : {
                // transpose matrix
                PARSE::FileData fileData;
                if (ReadFromCsv(fileData)) {
                    Matrix a1, a2;
                    if (a1.ConvertFromStrings(fileData.tokens)) {
                        a2 = a1.Transpose();
                        std::cout << "Result: \n";
                        a2.Print();
                        std::cout << "\n";
                    }
                }
                break;
            }
        }
    }

    return 0;
}
