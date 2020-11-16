#include <iostream>
#include <fstream>

#include <sstream>
#include <vector>
#include <string>
#include <cmath>

 std::vector<int> nnInterpolation(std::vector<int> data , int rowNums, int colNums, int newRowNums, int newColNums){
    std::vector<int> temp(newRowNums*newColNums );

    int x_ratio = (int) ((rowNums << 16) / newRowNums) +1 ;
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

int l1Distance(std::vector<int> original , std::vector<int> modified  ){

    int distance = 0;
    for(int i = 0; i < 512*512; i++){
            distance += std::abs((original[i] - modified[i]));
    }
    return distance;
}


int main(int argc , char **argv) {

    std::ifstream f;
    std::vector<int> holder;              //MAIN ARRAY HOLDING DATA

    //Read in csv to holder
    int x;
    char trash;
    for(int i = 0 ; i < 256; ++i) {
        for(int j = 0; i < 256*256; ++i) {
            std::cin >> x;
            holder.push_back(x);
            if(i < (256*256 -1))
                std::cin >> trash;
        }
    }

    int testOutput[512][512];
    int arrOutput[512][512];

    std::vector<int> outPut = nnInterpolation(holder,256, 256, 512, 512);


    std::ifstream f2 ("sample1_original_image.txt");

    std::vector<int> test;              //MAIN ARRAY CONFIRMED DATA
    std::string line2;
    while(getline(f2,line2)){
        std::istringstream iss(line2);
        std::string holder;
        while(getline(iss,holder,',')){
            test.push_back(std::stoi(holder));
        }
    }
    for(int i = 0 ; i < test.size() ; i++){
        std::cout << test[i] << " ";
    }


    std::cout << holder.size() << std::endl;
    std::cout << outPut.size() << std::endl;

    std::cout << l1Distance(test, outPut) << std::endl;


    std::ofstream outputFile;

    outputFile.open("output.txt");
    outputFile << "[ ";
    for(int i = 0; i < 512*512; i++){
       if(i % 512 == 0 && i != 0){
           outputFile << "\n";
       }
        outputFile << outPut[i] << ", ";
    }
    outputFile << " ]";
    outputFile.close();
    return 0;
}





