#ifndef RANGE
#define RANGE
#include <iostream>
namespace itertools
{
    class range
    {
    private:
        int _start, _end;

    public:
    typedef int value_type;
        class iterator
        {
            int value;

        public:
            iterator(int n) : value(n){};
            iterator() = default;
            bool operator==(const iterator &other)
            {
                return this->value == other.value;
            }
            bool operator!=(const iterator &other)
            {
                return !(*this == other);
            }
            iterator operator++()
            {
                this->value++;
                return *this;
            }
            iterator operator++(int)
            {
                iterator i = *this;
                this->value++;
                return i;
            }
            int operator*()
            {
                return this->value;
            }
        };
        // public:
        range(int b, int e) : _start(b), _end(e) { if(b > e)throw std::invalid_argument("left number must be smaller then right number!\n");}
        range(){};

        iterator begin()
        {
            return iterator(_start);
        }
        iterator end()
        {
            return iterator(_end);
        }
    };

} 
#endif