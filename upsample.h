//
// Created by caste on 11/15/2020.
//

#ifndef UPSAMPLE_UPSAMPLE_H
#define UPSAMPLE_UPSAMPLE_H

namespace mynamespace{

    class Matrix{
    private :
        const int ROWS;
        const int COLS;

        inline int & at(int row, int col) const{
            return vals[COLS * row + col];
        }

        int *vals;

    public:
        inline int n_rows(void) const {return ROWS;}
        inline int n_cols(void) const {return COLS;}


        Matrix();
        Matrix( const int rows, const int columns);

        int getValueAt(int r , int c) const;
        void setValueAt(int value, int r, int c);
    };

#include "upsample.inl"
}
#endif //UPSAMPLE_UPSAMPLE_H
