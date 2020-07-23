#include <iostream>
namespace itertools
{

    template <typename boolFunc, typename T>
    class filterfalse
    {
        boolFunc function;
        T container;

    public:
        explicit filterfalse(boolFunc f, T c)
            : container(c), function(f) {}
        class iterator
        {
            decltype(*(container.begin())) data;
            boolFunc function;
            typename T::iterator it;
            typename T::iterator _end;

        public:
            explicit iterator(typename T::iterator b, typename T::iterator e, boolFunc bf) : it(b), _end(e), function(bf), data(*b) {}
            bool operator==(const iterator &o)
            {
                return this->data == o.data;
            }
            bool operator!=(const iterator &o)
            {
                return !(this->it == o.it);
            }
            iterator operator++()
            {
                do
                {
                    ++(this->it);
                } while (it != _end && function(*it));
                return *this;
            }
            iterator operator++(int)
            {
                iterator t = (*this)++;
                return t;
            }
            auto operator*()
            {
                if (function(*it))
                {
                    do
                    {
                        ++(this->it);
                    } while (it != _end && function(*it));
                }
                return *(this->it);
            }
        };
        iterator begin()
        {
            return iterator(container.begin(), container.end(), function);
        }
        iterator end()
        {
            return iterator(container.end(), container.end(), function);
        }
    };

} 