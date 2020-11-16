#include <iostream>
#include <fstream>

#include <sstream>
#include <vector>
#include <string>
#include <cmath>

 std::vector<int> nnInterpolation(std::vector<int> data){
    std::vector<int> temp(512*512 );

    int x_ratio = (int) ((256 << 16) / 512) +1 ;
    int y_ratio = (int) ((256 << 16) / 512) +1;

    int newX, newY;

    for(int i = 0; i < 512; i++){
        for(int j = 0; j < 512; j++){
            newX = ((j*x_ratio) >> 16);
            newY = ((i*y_ratio) >> 16);
            temp[(i*512) + j] = data[(newY*256)+newX];
        }
    }

    return temp;
}

float biHelper1(float a, float b, float c){
    return(a+(b-a)*c);
}
float performBiLerp(float q00 ,float q10 ,float q01 ,float q11 , float transX, float transY ){
    return biHelper1(biHelper1(q00,q10,transX),biHelper1(q01,q11,transX), transY);
}

std::vector<int> bilinearInterpolation(std::vector<int> data, int row, int col, int newRow, int newCol){
    std::vector<int> temp(512*512);
    int x , y;
    for( x ,y = 0; y < newCol; x++ ){
        if(x > newRow){
            x= 0;
            y++;
        }

    float x_ratio = x / (float)(newRow) * (row-1);
    float y_ratio = y / (float)(newCol) * (col-1);

    int int_x_ratio = (int)x_ratio;
    int int_y_ratio = (int)y_ratio;

        std::uint32_t  result = 0;

    int q00 = data[(int_y_ratio*row) +int_x_ratio];
    int q10 = data[(int_y_ratio*row) +int_x_ratio+1];
    int q01 = data[(((int_y_ratio)+1)*row) +int_x_ratio];
    int q11 = data[(((int_y_ratio)+1)*row) +int_x_ratio+1];
std::uint8_t i;
        for( i = 0; i < 4; i++ ){
        result |= ( std::uint8_t)performBiLerp(q00 >> (i*8) &0xFF,q10>> (i*8) &0xFF,q01>> (i*8) &0xFF,q11>> (i*8) &0xFF,x_ratio -int_x_ratio,y_ratio - int_y_ratio ) <<(8*i);
         }
    temp[(y*row)+x] = result;
    }
    std::cout << temp.size() << "\n";

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

    std::vector<int> outPut = nnInterpolation(holder);
    std::vector<int> outPut2 = bilinearInterpolation(holder,256, 256, 512, 512);

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
    std::cout << l1Distance(test, outPut2) << std::endl;


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
    outputFile.close();
    return 0;
}





