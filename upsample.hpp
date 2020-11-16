//
// Created by caste on 11/16/2020.
//

#ifndef UPSAMPLE_UPSAMPLE_HPP
#define UPSAMPLE_UPSAMPLE_HPP


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
std::vector<int> resizeBilinearGray(std::vector<int> pixels, int w, int h, int w2, int h2) {
    std::vector<int> temp(512*512);
    int A, B, C, D, x, y, index, color ;
    float x_ratio = ((float)(w-1))/w2 ;
    float y_ratio = ((float)(h-1))/h2 ;
    float x_diff, y_diff;
    int offset = 0 ;
    for (int i=0;i<h2;i++) {
        for (int j=0;j<w2;j++) {
            x = (int)(x_ratio * j) ;
            y = (int)(y_ratio * i) ;
            x_diff = (x_ratio * j) - x ;
            y_diff = (y_ratio * i) - y ;
            index = y*w+x ;

            // range is 0 to 255 thus bitwise AND with 0xff
            A = pixels[index] & 0xff ;
            B = pixels[index+1] & 0xff ;
            C = pixels[index+w] & 0xff ;
            D = pixels[index+w+1] & 0xff ;

            // Y = A(1-w)(1-h) + B(w)(1-h) + C(h)(1-w) + Dwh
            color = (int)(
                    A*(1-x_diff)*(1-y_diff) +  B*(x_diff)*(1-y_diff) +
                    C*(y_diff)*(1-x_diff)   +  D*(x_diff*y_diff)
            ) ;

            temp[offset++] = color ;
        }
    }
    return temp ;
}


int l1Distance(std::vector<int> original , std::vector<int> modified  ){

    int distance = 0;
    for(int i = 0; i < 512*512; i++){
        distance += std::abs((original[i] - modified[i]));
    }
    return distance;
}

#endif //UPSAMPLE_UPSAMPLE_HPP
