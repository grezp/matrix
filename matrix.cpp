#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <sstream>

const int MAX_VAL =  46340;
const int MIN_VAL = -46340;

bool Matrix::ConvertFromStrings(const std::vector<std::vector<std::string>>& strings)
{
    bool isValid = true;
    bool debug = false;

    if (!strings.empty()) {

        m_mSize = strings.size();
        m_nSize = strings[0].size();
        data.resize(m_mSize, std::vector<int>(m_nSize));

        #pragma omp parallel for
        for (std::size_t i=0; isValid && i<strings.size(); i++) {
            for (std::size_t j=0; isValid && j<strings[i].size(); j++) {

                // check if valid size
                if (m_nSize != strings[i].size()) {
                    std::cout << "Warning! Does not match N size.\n\n";
                    return false;
                }

                // convert str to int
                if ( PARSE::isNumber(strings[i][j]) ) {

                    std::stringstream strStream (strings[i][j]);
                    strStream >> data[i][j];

                    // check if range constraint are met
                    if (data[i][j]<MIN_VAL || data[i][j]>MAX_VAL) {
                        std::cout << "Warning! " << strings[i][j] << " is out of range.\n";
                        std::cout << "Valid range is between [" << MIN_VAL << ", " << MAX_VAL << "]\n\n";
                        return false;
                    }
                }
                else {
                    std::cout << "Warning! " << strings[i][j] << " is not a valid integer.\n\n";
                    return false;
                }
            }
        }
        if (debug) {
            std::cout << m_mSize << "x" << m_nSize << "matrix: \n";
            for (std::size_t i=0; i<m_mSize; i++) {
                for (std::size_t j=0; j<m_nSize; j++) {
                    std::cout << std::setw(10) << data[i][j];
                }
                std::cout << "\n\n";
            }
        }

        return true;
    }
    
    return false;
}

void Matrix::Print(const std::size_t &colWidth)
{
    if (!data.empty()) {
        for (std::size_t i=0; i<data.size(); i++) {
            for (std::size_t j=0; j<data[0].size(); j++) {
                std::cout << std::setw(colWidth) << data[i][j];
            }
            std::cout << "\n";
        }
    }
    else {
        std::cout << "Unable to print. Data is empty\n" << std::endl;
    }
}

Matrix Matrix::Transpose()
{
    std::vector<std::vector<int>> mat(data[0].size(), std::vector<int>(data.size(), 0));

    #pragma omp parallel for
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size(); j++) {
			mat[j][i] = data[i][j];
		}
	}
    return Matrix(mat, m_nSize, m_mSize);
}

Matrix Matrix::Multiply(const Matrix& mat2)
{
    std::size_t iSize = m_mSize;
    std::size_t jSize = mat2.GetNSize();
    std::size_t kSize  = m_nSize;
    std::vector<std::vector<int>> data3(iSize, std::vector<int>(jSize, 0));

    // make sure it's a valid operation first
    if (m_nSize == mat2.GetMSize()) {

        #pragma omp parallel for
        for (std::size_t i=0; i<iSize; i++) {
            for (std::size_t j=0; j<jSize; j++) {
                for (std::size_t k=0; k<kSize; k++){
                    data3[i][j] += data[i][k] * mat2.data[k][j];
                }
            }
        }

    }
    else {
        std::cout << "Error! M1 and N2 do not match in size. Unable to multiply.\n";
        return Matrix();
    }
    
    return Matrix(data3, iSize, jSize);
}
