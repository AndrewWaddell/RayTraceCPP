#ifndef BOOLARRAY_H
#define BOOLARRAY_H

#include <vector>

class BoolArray {
    private:
        std::vector<bool> vals;
        bool found; // temporary variable used in anyfalse
    public:
        bool anyFalse(); // returns true if any of the items are false
        void generate(int size); // like a constructor
        bool get(int i); // return output at index i
        void insert(int i,bool val); // insert bool at index i
};

#endif