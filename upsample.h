//
// Created by caste on 11/15/2020.
//

#ifndef UPSAMPLE_UPSAMPLE_H
#define UPSAMPLE_UPSAMPLE_H


    std::vector<int> nnInterpolation(std::vector<int> data);
    std::vector<int> resizeBilinearGray(std::vector<int> pixels, int w, int h, int w2, int h2);
    int l1Distance(std::vector<int> original , std::vector<int> modified  );
#include "upsample.hpp"
#endif //UPSAMPLE_UPSAMPLE_H
