//
// Created by caste on 11/16/2020.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "upsample.h"
#include "gtest/gtest.h"

//Test if the size of the reading image matches specifications
//Checks to make sure our csv read in works
TEST(checkSize, csvReadIN)
{
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
        //Test
        EXPECT_EQ(test.size(),256*256);
}

//Test what happens if if we divide 2 empty arrays
TEST(checkZero, L1distance)
{
    std::vector<int> test1(512*512);
    std::vector<int> test2(512*512);

    EXPECT_EQ(l1Distance(test1,test2) , 0);

}

//Test to make sure NNupsampling size changes correctly
TEST(checkUpSampling, NNupSampling)
{
    std::vector<int> data;
    for(int i = 0; i < 256*256; i++){
        data.push_back(i%256);
    }
    EXPECT_EQ(data.size(),256*256);
    std::vector<int> result = nnInterpolation(data);
    EXPECT_EQ(result.size(),512*512);
}
//Test to make sure BilinearUpSampling size changes correctly
TEST(checkUpSampling, BilinearUpSampling)
{
    std::vector<int> data;
    for(int i = 0; i < 256*256; i++){
    data.push_back(i%256);
    }
    EXPECT_EQ(data.size(),256*256);
    std::vector<int> result = resizeBilinearGray(data, 256, 256, 512, 512);
    EXPECT_EQ(result.size(),512*512);
}
//Make sure Ratio is same across original and modified
TEST(checkUpSampling, CheckingUpSamplingRatioNN){
        std::vector<int> data;
        for(int i = 0; i < 256*256; i++){
        data.push_back(i%256);
        }
        EXPECT_EQ(data.size(),256*256);
        std::vector<int> result = nnInterpolation(data);
        EXPECT_EQ(result.size(),512*512);


        int runningSumOriginal = 0;
        for(int i = 0 ; i < data.size(); i++){
            runningSumOriginal += data[i];
        }
        int runningSumModified = 0;
        for(int i = 0 ; i < result.size(); i++){
            runningSumModified += result[i];
        }

        float originalAverage = runningSumOriginal / (256*256);
        float modifiedAverage = runningSumModified / (512*512);

        // The modified average and the orignial average should remain the same in a correct interpolation
        EXPECT_EQ(modifiedAverage , originalAverage);


}

//Make sure Ratio is less than across original and modified
TEST(checkUpSampling, CheckingUpSamplingRatioBI){
    std::vector<int> data;
        for(int i = 0; i < 256*256; i++){
            data.push_back(i%256);
        }
        EXPECT_EQ(data.size(),256*256);
        std::vector<int> result = resizeBilinearGray(data,256,256,512,512);
        EXPECT_EQ(result.size(),512*512);

        int runningSumOriginal = 0;
        for(int i = 0 ; i < data.size(); i++){
             runningSumOriginal += data[i];
        }
        int runningSumModified = 0;
        for(int i = 0 ; i < result.size(); i++){
            runningSumModified += result[i];
        }

        float originalAverage = runningSumOriginal / (256*256);
        float modifiedAverage = runningSumModified / (512*512);

        // The modified average should be less than the original average (due to how we perform the interpolation)
        EXPECT_LT(modifiedAverage , originalAverage);


}
int main(int argc , char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

