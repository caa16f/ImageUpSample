

Matrix::Matrix(int rows, int cols) : ROWS(rows) , COLS(cols){
        vals = new int[ROWS * COLS];
}

Matrix::Matrix() : ROWS (256) , COLS(256){
    vals = new int[65536];
}

int Matrix::getValueAt(int r, int c) const{
    if(r < 0 or r >= ROWS or c < 0 or c >= COLS){
        //Invalid value access point
    }else{
        return at(r,c);
    }
}

void Matrix::setValueAt(int value, int r , int c){
    if(r < 0 or r >= ROWS or c < 0 or c>= COLS){

    }else{
        at(r,c) = value;
    }
}
