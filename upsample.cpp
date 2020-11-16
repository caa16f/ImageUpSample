#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

 std::vector<int> nnInterpolation(std::vector<int> data , int rowNums, int colNums, int newRowNums, int newColNums){
    std::vector<int> temp(newRowNums*newColNums );

    int x_ratio = (int) ((rowNums<<16)/newRowNums) +1 ;
    int y_ratio = (int) ((colNums << 16) / newColNums) +1;

    int newX, newY;

    for(int i = 0; i < newColNums; i++){
        for(int j = 0; j < newRowNums; j++){
            newX = ((j*x_ratio) >> 16);
            newY = ((i*y_ratio) >> 16);
            temp[(i*newRowNums) + j] = data[(newY*rowNums)+newX];
        }
    }

    return temp;
}


int main(int argc , char **argv) {

    std::ifstream f;
    std::string line, val;
    std::vector<int> holder;              //MAIN ARRAY HOLDING DATA

    if( argc > 1){
        f.open(argv[1]);
        if(!f.is_open()){
            std::cerr << "Error , file opening failed :" << argv[1] << ".\n";
            return 1;
        }
    }else{
        std::cerr << "Missing file input: File required for program to run";
        return 1;
    }


    while(std::getline(f,line)) {
        std::vector<int> v;         //Vector to hold the rows
        std::stringstream s(line);      //String stream s
        while (getline(s, val, ','))
            holder.push_back(std::stoi(val));
       // holder.push_back(v);
    }


    for (auto& row : holder) {
       //     std::cout << row << "  ";
    }
    std::cout << holder.size() << std::endl;


    std::vector<int> outPut = nnInterpolation(holder,256, 256, 512, 512);



    std::cout << outPut.size() << std::endl;


    return 0;
}





