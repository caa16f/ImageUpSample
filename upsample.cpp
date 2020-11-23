#include <iostream>
#include <fstream>

#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "upsample.h"
#include "upsample.hpp"
//1
int main(int argc , char **argv) {





    std::vector<int> holder;              //MAIN ARRAY HOLDING DATA

    //Testing L1 metric
    if(argv[1] != NULL) {
        std::ifstream f(argv[1]);


        std::vector<int> test;              //MAIN ARRAY CONFIRMED DATA
        std::string line2;
        while (getline(f, line2)) {
            std::istringstream iss(line2);
            std::string holder1;
            while (getline(iss, holder1, ',')) {
                test.push_back(std::stoi(holder1));
            }
        }


        int testOutput[512][512];
        int arrOutput[512][512];

        //Generate interpolation
        if (argv[2] != NULL) {
            std::vector<int> outPut = nnInterpolation(test);

            std::vector<int> outPut3 = resizeBilinearGray(test, 256, 256, 512, 512);



            //Testing L1 metric
            std::ifstream f2("sample1_original_image.txt");

            std::vector<int> test2;              //MAIN ARRAY CONFIRMED DATA
            std::string line3;
            while (getline(f2, line3)) {
                std::istringstream iss(line3);
                std::string holder;
                while (getline(iss, holder, ',')) {
                    test2.push_back(std::stoi(holder));
                }
            }

            std::cout << l1Distance(test2, outPut) << std::endl;
            std::cout << l1Distance(test2, outPut3) << std::endl;


            std::ofstream outputFile(argv[2]);
            outputFile << "NN MATRIX :         " << "\n";
            outputFile << "[ ";
            for (int i = 0; i < 512 * 512; i++) {
                if (i % 512 == 0 && i != 0) {
                    outputFile << "\n";
                }
                outputFile << outPut[i] << ", ";
            }
            outputFile << " ]";
            outputFile << "L1 DISTANCE :" << l1Distance(test2, outPut) << "\n";
        } else {

        }
    } else{
        std::cout << "NULL" << std::endl;
    }
    return 0;
}





