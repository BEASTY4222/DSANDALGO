#include <stdexcept>
#include <memory>

namespace MyDses{
    template <class T>

    class Array{
        size_t _capacity;
        std::unique_ptr<T[]> _pArray;

        public:
            Array(size_t capacity) : _capacity(capacity) , _pArray(std::make_unique<T[]>(capacity))
            {}

            T& operator [](size_t index){
                if(index >= _capacity || index < 0)throw std::out_of_range("Out of range");

                return _pArray[index];
            }

            size_t size()const {return _capacity;}

            T& first() { 
                return _pArray[0];
            }

            T& last(){
                return _pArray[_capacity-1];
            }

            void operator =(*this cur, T& other){
                
            }
    };

    template <class T>
    class DArray : public Array<T>{
        size_t _curIndex;

        public:
            DArray(size_t capacity) : Array<T>(capacity), _curIndex(0)
            {}

            void add(T& elem){
                if(_curIndex >= _capacity){ 
                    //_capacity + _curIndex/2 = newCapacity 
                    std::unique_ptr<T[]> pNewArr = std::make_unique<T[]>(_capacity + _curIndex/2);

                }



                _pArray[_curIndex] = elem;
                _curIndex++;
            }

    };
}