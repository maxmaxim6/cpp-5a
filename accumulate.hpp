namespace itertools
{
    typedef struct
    {
        template <typename V>
        V operator()(V a, V b) const
        {
            return a + b;
        }
    } plus;

    template <typename T, typename accumulateFunc = plus>
    class accumulate
    {
        T container;
        accumulateFunc function;
        // typedef typename T::value_type value_type;
    public:
        explicit accumulate(T c, accumulateFunc f = plus())
            : container(c), function(f) {}

        class iterator
        {

            typename T::value_type data;
            typename T::iterator start;
            typename T::iterator _end;
            accumulateFunc function;

        public:
            explicit iterator(typename T::iterator i, typename T::iterator end, accumulateFunc func)
                : start(i), _end(end), function(func){if (start != _end)data = *start;};
            iterator(const iterator& o) = default;
            iterator &operator=(const iterator &o) //i used Erel`s example to overload operator =
            {
                if (this != &o)
                {
                    this->data = o.data;
                    this->start = o.start;
                    this->_end = o._end;
                    this->function = o.function;
                }
                return *this;
            };
            iterator &operator++()
            {
                this->start++;
                if (this->start != this->_end)
                    this->data = function(this->data, *(this->start));
                return *this;
            }
            iterator operator++(int)
            {
                typename T::iterator i = *this;
                (*this)++;
                return i;
            }
            bool operator==(const iterator &other)
            {
                return this->start == other.start;
            }
            bool operator!=(const iterator &other)
            {
                return !(start == other.start);
            }

            auto operator*()
            {
                return this->data;
            }
        };

        iterator begin()
        {
            return iterator(container.begin(), container.end(), this->function);
        }
        iterator end()
        {
            return iterator(container.end(), container.end(), this->function);
        }
    };
} 
