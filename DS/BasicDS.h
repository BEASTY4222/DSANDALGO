#include <stdexcept>
#include <memory>

namespace MyDses{
    template <class T>
    class Array{
        std::unique_ptr<T[]> _pArray;

        public:
            size_t capacity;
            Array(size_t capacity) : capacity(capacity) , _pArray(std::make_unique<T[]>(capacity)){}

            T& operator [](size_t index){
                if(index >= capacity || index < 0)throw std::out_of_range("Out of range");

                return _pArray[index];
            }

            size_t size() const { return capacity; }
            T& first() {return _pArray[0];}
            T& last(){return _pArray[capacity-1];}

            Array& operator=(const Array& other) {
                //Compare addresses
                if(this != &other){
                    std::unique_ptr<T[]> pNewArr = std::make_unique<T[]>(other.capacity);

                    for(size_t i = 0;i < other.capacity;++i)
                        pNewArr[i] = other._pArray[i]; 

                    _pArray = pNewArr;
                    this->capacity = other.capacity;

                    return *this;
                }

                return *this;
            }

            Array(const Array& other) : capacity(other.capacity), _pArray(std::make_unique<T[]>(other.capacity)) {
                for(size_t i = 0; i < capacity; ++i)
                    _pArray[i] = other._pArray[i];
            }

            void swap(Array& other) {
                // Exchange capacities
                std::swap(this->capacity, other.capacity);
                
                // Exchange unique pointers
                // This swaps ownership - no data is copied!
                this->_pArray.swap(other._pArray);
            }
    };

    template <class T>
    class DArray {
        size_t _curIndex;
        Array<T> array; 

        public:
            DArray(size_t capacity) : array(capacity), _curIndex(0){}
            DArray() : array(0), _curIndex(0){}

            //o(1)
            void add_back(const T& elem){
                if(_curIndex >= array.size() || array.size() <= 0){ 
                    //capacity + _curIndex/2 = newCapacity 
                    Array<T> newArr(array.size() + _curIndex/2);

                    for(size_t i = 0;i < array.size();++i)
                        newArr[i] = array[i];

                    array.swap(newArr);
                }

                array[_curIndex] = elem;
                _curIndex++;
            }
            
            //o(n)
            void add_front(const T& elem){
                if(_curIndex >= array.size()){ 
                    //capacity + _curIndex/2 = newCapacity 
                    Array<T> newArr(array.size() + _curIndex /2);

                    for(size_t i = 0; i < array.size(); ++i)
                        newArr[i + 1] = array[i];

                    array.swap(newArr);

                    
                }else{
                    // There's room - shift elements right
                    for (size_t i = _curIndex; i > 0; --i) {
                        array[i] = array[i - 1];
                    }
                }

                array[0] = elem;
                _curIndex++;
            }

            void pop_back() {
                if (_curIndex > 0) {
                    --_curIndex;
                    array[_curIndex - 1].~T();
                    //this does nothing for primitive types but we can always expect them to be primitive
                }
            }

            size_t size() const { return array.size(); }
            T& first() {return array[0];}
            T& last(){return array[array.size()-1];}

            T& operator [](size_t index){
                if(index >= array.size() || index < 0)throw std::out_of_range("Out of range");

                return array[index];
            }
    };


    template <class T>
    class Stack{
        size_t _capacity;
        size_t _curIndex;
        DArray<T> _stack;

        public:

        Stack(size_t capacity) : _capacity(capacity), _curIndex(0), _stack(capacity){}
        Stack() : _capacity(0), _curIndex(0), _stack(){}

        void push(const T& element){
            _stack.add_back(element);
        }
        T& top() const{
            return _stack.last();
        }
        void pop(){
            _stack.pop_back();
        }

        size_t size() const{return _capacity;}


    };
}