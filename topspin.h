#ifndef TOPSPIN_H
#define TOPSPIN_H

class TopSpin
{
    public:
        TopSpin(); 
        TopSpin(volatile TopSpin& ancestor);
        void rotate(char d, int r, bool pprint);
        void spin(bool pprint);
        void swap(int i, int j);
        int heuristicValue();
        int butterknifeValue();
        bool solved();
        void print();
    private:
        int l_ptr;
        int r_ptr;
        int seq [20];
};
#endif
