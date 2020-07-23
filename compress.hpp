#include <iostream>
#include <typeinfo>
#include "range.hpp"
using namespace std;
namespace itertools
{
    template <typename T, typename V>
    class compress
    {
        T container_1;
        V container_2;
        class iterator
        {
            typename T::iterator con_it;
            typename T::iterator con_end;
            typename V::iterator bool_it;
            void increment()
            {
                    ++bool_it;
                    ++con_it;
            }
            void skip_failures()
            {
                while (con_it != con_end && !*bool_it)
                {
                    increment();
                }
            }

        public:
            explicit iterator(typename T::iterator i1, typename T::iterator e, typename V::iterator i2)
                : con_it(i1), con_end(e), bool_it(i2) {skip_failures();}
            auto operator*()
            {
                if (!(*bool_it))
                {
                    ++(*this);
                }
                return *con_it;
            }
            iterator& operator++()
            {
                increment();
                skip_failures();
                return *this;
            }
            iterator &operator++(int)
            {
                iterator t = *this;
                ++(*this);
                return t;
            }
            iterator &operator=(const iterator &other)
            {
                if (*this != other)
                {
                    this->con_it = other.con_it;
                    this->con_end = other.con_end;
                    this->bool_it = other.bool_it;
                }
                return *this;
            }
            bool operator==(const iterator &other)
            {
                return this->con_it == other.con_it && bool_it == other.bool_it;
            }
            bool operator!=(const iterator &other)
            {
                return !(this->con_it == other.con_it) || !(this->bool_it == other.bool_it);
            }
        };

    public:
        explicit compress(T t, V v)
        {
            int s1 = 1, s2 = 1;
            for (auto i : v)
            {
                s2++;
            }
            for (auto j : t)
            {
                s1++;
            }
            if (s1 != s2)
            {
                std::cout << "s1 length= " << s1 << ", s2 length= " << s2 << std::endl;
                throw std::invalid_argument("invalid argument\n");
            }
            this->container_1 = t;
            this->container_2 = v;
        }
        iterator begin()
        {
            return iterator(container_1.begin(), container_1.end(), container_2.begin());
        }
        iterator end()
        {
            return iterator(container_1.end(), container_1.end(), container_2.end());
        }
    };

} // namespace itertools