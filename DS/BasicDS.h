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
        size_t _startIndex;
        size_t _curIndex;
        Array<T> array; 

        public:
            DArray(size_t capacity) : array(capacity), _curIndex(0), _startIndex(0){}
            DArray() : array(0), _curIndex(0), _startIndex(0){}

            //o(1) ,o(n) when needing space
            void add_back(const T& elem){
                if(_curIndex >= array.size()){ 
                    //capacity + _curIndex/2 = newCapacity 
                    size_t new_capacity = array.size() + _curIndex/2;

                    if (new_capacity == 0) new_capacity = 1;  // Minimum capacity

                    Array<T> newArr(new_capacity);

                    for(size_t i = 0;i < _curIndex;++i)
                        newArr[i] = array[(_startIndex + i) % array.size()];

                    array.swap(newArr);
                }

                array[(_startIndex + _curIndex) % array.size()] = elem;
                _curIndex++;
            }
            
            //o(1) ,o(n) when needing space
            void add_front(const T& elem){
                if(_curIndex >= array.size()){ 
                    //capacity + _curIndex/2 = newCapacity 
                    size_t new_capacity = array.size() + _curIndex/2;

                    if (new_capacity == 0) new_capacity = 1;  // Minimum capacity

                    Array<T> newArr(new_capacity);

                    for(size_t i = 0; i < _curIndex; ++i)
                        newArr[i] = array[(_startIndex + i) % array.size()];
                    
                    _startIndex = 0;

                    array.swap(newArr);                   
                }

                array[(_startIndex - 1 + array.size()) % array.size()] = elem;
                _curIndex++;        
                _startIndex = (_startIndex - 1 + array.size()) % array.size();
            }
            
            //o(1)
            void pop_back() {
                if (_curIndex > 0) {
                    array[(_startIndex + _curIndex - 1) % array.size()].~T();
                    --_curIndex;
                    //this does nothing for primitive types but we cant always expect them to be primitive
                }
            }

            //o(1)
            void pop_front(){
                if (_curIndex > 0) {
                    array[_startIndex].~T();
                    _startIndex = (_startIndex + 1) % array.size();  // Just move the start pointer!
                    --_curIndex;
                }
            }

            size_t size() const { return _curIndex; }
            T& first() {return array[_startIndex];}
            T& last(){return array[(_startIndex + _curIndex - 1) % array.size()];}

            T& operator [](size_t index){
                if (index >= _curIndex)throw std::out_of_range("Out of range");

                return array[(_startIndex + index) % array.size()];
            }
    };

    //LIFO
    template <class T>
    class MStack{
        size_t _capacity;
        size_t _curIndex;
        DArray<T> _stack;

        public:

        MStack<T>(size_t capacity) : _capacity(capacity), _curIndex(0), _stack(capacity){}
        MStack<T>() : _capacity(0), _curIndex(0), _stack(){}

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
    //FIFO
    template <class T>
    class MQueue{
        size_t _capacity;
        size_t _curIndex;
        DArray<T> _queue;

        public:

        MQueue(size_t capacity) : _capacity(capacity), _curIndex(0), _queue(capacity){}
        MQueue() : _capacity(0), _curIndex(0), _queue(){}
        
        void push_back(const T& elem){
            _queue.push_back(elem);
        }

        T& peek(){
            return _queue.first();
        }

        void pop_front(){
            _queue.pop_front();
        }
        size_t size() const{return _capacity;}
    };

    template <class T>
    class MLinkedList{
        public:
            T data;
            std::unique_ptr<MLinkedList> next;

            MLinkedList(const T& data, MLinkedList next){
                this->data = data;
                this->next = std::make_unique<MLinkedList>(next);
            }

            MLinkedList(const T& data){
                this->data = data;
                this->next = nullptr;
            }
        
            MLinkedList& operator =(const MLinkedList& other){
                if(this != &other){
                    this->data = other.data;
                    this->next = other.next;
                    

                    return *this;
                }

                return *this;
            }
            
        
    };

}
