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

std::vector<int> bilinearInterpolation(std::vector<int> data, int row, int col, int newRow, int newCol){
    std::vector<int> temp(512*512);

    int x_ratio = (row-1)/newRow;
    int y_ratio = (col-1)/newCol;

    int A , B , C , D;
    int x, y ,index;

    int x_dif, y_dif;



    int colorHolder;
    for(int i =0 ; i< newCol; i++){
        for(int j = 0 ; j < newRow; j++){
            x = (int)(x_ratio * j) ;
            y = (int)(y_ratio * i) ;
            x_dif = (x_ratio * j) - x ;
            y_dif = (y_ratio * i) - y ;
            index = y*row+x;


            A = data[index] & 0xff ;
            B = data[index+1] & 0xff ;
            C = data[index+row] & 0xff ;
            D = data[index+row+1] & 0xff ;


            colorHolder = (int)(A*(1-x_dif)*(1-y_dif) +  B*(x_dif)*(1-y_dif) +C*(y_dif)*(1-x_dif)   +  D*(x_dif*y_dif)
            ) ;

            temp.push_back(colorHolder);
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





