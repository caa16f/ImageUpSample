//
// Created by caste on 11/16/2020.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "upsample.hpp"
#include "gtest/gtest.h"

//TEST TEST
TEST(Addition, csvReadIN)
{
std::ifstream f("sample1_input_image.txt");;


std::vector<int> holder;
int x;
char trash;
    for(int i = 0 ; i < 256; ++i) {
        ASSERT_LT(i,256);
         for(int j = 0; i < 256*256; ++i) {
          std::cin >> x;
          holder.push_back(x);
              if(i < (256*256 -1))
              std::cin >> trash;
        }
    }


std::ifstream f2 ("sample1_input_image.txt");

    std::vector<int> test;              //MAIN ARRAY CONFIRMED DATA
    std::string line2;
        while(getline(f2,line2)){
        std::istringstream iss(line2);
        std::string holder2;
            while(getline(iss,holder2,',')){
            test.push_back(std::stoi(holder2));
            }
    }

        for(int i = 0; i < 256*256; i++){
            EXPECT_EQ(test[i],holder[i]);
        }

}

int main(int argc , char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

