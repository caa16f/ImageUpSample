#include <iostream>


namespace mynamespace{
    template<class T>
    class Matrix{
    private :
        int n_rows;
        int n_cols;

        T** n_data;

    public:
        Matrix();
        Matrix( const int rows, const int columns);
        Matrix(const int rows, const int columns , const T** data);

        T** getData() const;
    };
}

using namespace  mynamespace;

void readMatrix(std::fstream & in, const std::string & fileName, Matrix& matrixInput);

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


void readMatrix( std::fstream& fin, const std::string& strFilename, Matrix& mat ) {
    // Do Work Here To Populate Matrix Object
} // readMatrix