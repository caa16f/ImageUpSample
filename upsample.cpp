#include <iostream>
#include <fstream>

#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "upsample.h"

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

    std::vector<int> outPut = nnInterpolation(holder);
    std::vector<int> outPut3= resizeBilinearGray(holder,256, 256, 512, 512);

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

    std::cout << l1Distance(test, outPut) << std::endl;
    std::cout << l1Distance(test, outPut3) << std::endl;

    std::ofstream outputFile;

    outputFile.open("output.txt");
    outputFile << "NN MATRIX :         "  << "\n";
    outputFile << "[ ";
    for(int i = 0; i < 512*512; i++){
       if(i % 512 == 0 && i != 0){
           outputFile << "\n";
       }
        outputFile << outPut[i] << ", ";
    }
    outputFile << " ]";
    outputFile << "L1 DISTANCE :" << l1Distance(test, outPut) << "\n";


    outputFile << "BILINEAR MATRIX :         "  << "\n";
    outputFile << "[ ";
    for(int i = 0; i < 512*512; i++){
        if(i % 512 == 0 && i != 0){
            outputFile << "\n";
        }
        outputFile << outPut3[i] << ", ";
    }
    outputFile << " ]";
    outputFile << "L1 DISTANCE :" << l1Distance(test, outPut3) << "\n";
    outputFile.close();
    return 0;
}





