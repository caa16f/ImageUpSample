//
// Created by caste on 11/16/2020.
//

#ifndef UPSAMPLE_UPSAMPLE_HPP
#define UPSAMPLE_UPSAMPLE_HPP



std::vector<int> nnInterpolation(std::vector<int> data){
    std::vector<int> temp(512*512 );

    int x_ratio = (int) ((256 << 16) / 512) +1 ;
    int y_ratio = (int) ((256 << 16) / 512) +1;

    int newidthX, newidthY;

    for(int i = 0; i < 512; i++){
        for(int j = 0; j < 512; j++){
            newidthX = ((j*x_ratio) >> 16);
            newidthY = ((i*y_ratio) >> 16);
            temp[(i*512) + j] = data[(newidthY*256)+newidthX];
        }
    }

    return temp;
}
std::vector<int> resizeBilinearGray(std::vector<int> pixels, int width, int height, int width2, int height2) {
    std::vector<int> temp(512*512);
    int A, B, C, D, x, y, index, color ;
    float x_ratio = ((float)(width-1))/width2 ;
    float y_ratio = ((float)(height-1))/height2 ;
    float x_diff, y_diff;
    int offset = 0 ;
    for (int i=0;i<height2;i++) {
        for (int j=0;j<width2;j++) {
            x = (int)(x_ratio * j) ;
            y = (int)(y_ratio * i) ;
            x_diff = (x_ratio * j) - x ;
            y_diff = (y_ratio * i) - y ;
            index = y*width+x ;

            // range is 0 to 255 thus bitwidthise AND widthith 0xff
            A = pixels[index] & 0xff ;
            B = pixels[index+1] & 0xff ;
            C = pixels[index+width] & 0xff ;
            D = pixels[index+width+1] & 0xff ;

            // Y = A(1-width)(1-height) + B(width)(1-height) + C(height)(1-width) + Dwidthh
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
        distance += std::abs((modified[i] - original[i]));
    }
    return distance;
}

#endif //UPSAMPLE_UPSAMPLE_HPP
