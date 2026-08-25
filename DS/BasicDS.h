#include <stdexcept>
#include <memory>
#include <string.h>

namespace MyDses{
/*
    Operation	Time Complexity	Notes
    Constructor	        O(n)	Allocates n elements
    operator[]	        O(1)	Direct access
    size()	            O(1)	Returns capacity
    first()	            O(1)	Direct access
    last()	            O(1)	Direct access
    operator= (copy)	O(n)	Copies all elements
    Copy Constructor	O(n)	Copies all elements
    swap()	            O(1)	Exchanges pointers only
    empty()	            O(1)	Checks if size is 0
    Space Complexity: O(n) 
*/
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
            bool empty()const{return size == 0;}

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

    /*
    DArray<T> (Dynamic Array with Circular Buffer)
    Operation	Average Case	Worst Case	Amortized	Notes
    add_back()	        O(1)	O(n)	O(1)	Amortized O(1) due to geometric growth
    add_front()	        O(1)	O(n)	O(1)	Amortized O(1) due to geometric growth
    pop_back()	        O(1)	O(1)	O(1)	No shifting needed
    pop_front()	        O(1)	O(1)	O(1)	Only moves start pointer
    operator[]	        O(1)	O(1)	O(1)	Direct access with wrap-around
    size()	            O(1)	O(1)	O(1)	Returns element count
    first()	            O(1)	O(1)	O(1)	Direct access
    last()	            O(1)	O(1)	O(1)	Direct access with wrap-around
    empty()	            O(1)	O(1)    O(1)    Checks if size is 0
    Space Complexity: O(n)
*/
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

            void pop_at(size_t index){
                if(index >= _curIndex) throw std::out_of_range("Out of range");
                if(index == 0) return pop_front();
                if(index == _curIndex - 1) return pop_back();

                size_t phys = (_startIndex + index) % array.size();
                array[phys].~T();

                for(size_t i = index + 1;i < _curIndex;++i){
                    size_t src = (_startIndex + i) % array.size();
                    size_t dst = (_startIndex + i - 1) % array.size();
                    array[dst] = std::move(array[src]);
                }

                array[(_startIndex + _curIndex - 1) % array.size()].~T();

                _curIndex--;
            }

            size_t size() const { return _curIndex; }
            T& first() {return array[_startIndex];}
            T& last(){return array[(_startIndex + _curIndex - 1) % array.size()];}
            bool empty()const {return size() == 0;}

            T& operator [](size_t index){
                if (index >= _curIndex)throw std::out_of_range("Out of range");

                return array[(_startIndex + index) % array.size()];
            }
    };

    /*
    Operation	Time Complexity	Notes
    push()	    O(1)            amortized	Delegates to DArray::add_back()
    pop()	    O(1)	        Delegates to DArray::pop_back()
    top()	    O(1)	        Delegates to DArray::last()
    size()	    O(1)	        Returns size
    empty()	    O(1)	Checks if size is 0
    Space Complexity: O(n)
*/
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

        size_t size() const{return _stack.size();}
        bool empty()const {return size() == 0;}
    };

/*
    Operation	Time    Complexity	Notes
    push_back()	O(1)    amortized	Delegates to DArray::add_back()
    pop_front()	O(1)	Delegates to DArray::pop_front()
    peek()	    O(1)	Delegates to DArray::first()
    size()	    O(1)	Returns size
    empty()	    O(1)	Checks if size is 0
    Space Complexity: O(n)
*/

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
        size_t size() const{return _queue.size();}
        bool empty()const {return size() == 0;}
    };
/*
    Operation	Time Complexity	Notes
    Constructor	        O(1)	Creates empty list
    push_front()	    O(1)	Inserts at head
    pop_front()	        O(1)	Removes from head
    front()	            O(1)	Direct access to head
    size()	            O(1)	Returns cached size
    empty()	            O(1)	Checks if size is 0
    Traversal/Iteration	O(n)	Must follow next pointers
    Destructor	        O(n)	Recursively destroys nodes
    Space Complexity: O(n)
*/
    template <class T>
    class MLinkedList {
        struct Node {
            T data;
            std::unique_ptr<Node> next;
            
            Node(const T& data) : data(data), next(nullptr) {}
        };
        
        std::unique_ptr<Node> head;
        size_t _size;

    public:
        MLinkedList() : head(nullptr), _size(0) {}
        
        void push_front(const T& data) {
            std::unique_ptr<Node> new_node = std::make_unique<Node>(data);
            new_node->next = std::move(head);
            head = std::move(new_node);
            ++_size;
        }
        
        T& front() {
            if (!head) throw std::out_of_range("Empty list");
            return head->data;
        }
        
        void pop_front() {
            if (!head) return;
            head = std::move(head->next);
            --_size;
        }
        
        size_t size() const { return _size; }
        bool empty() const { return _size == 0; }
    };

/*
    Operation	Average Case	Worst Case	Amortized
    add()	    O(1)	        O(n)	    O(1)
    operator[]	O(1)	        O(n)	    O(1)
    contains()	O(1)	        O(n)	    O(1)
    resize()	O(n)	        O(n)	    O(1) amortized
    size()	    O(1)	        O(1)	    O(1)
    Space Complexity: O(n)
*/
    template <class T>
    class MHashTable{
        //index = hash % table_size
        size_t _capacity;
        size_t _elementCount;
        Array<DArray<std::pair<int, T>>> _hashtable; 


        void resize() {
            size_t newCapacity = _capacity * 2;
            Array<DArray<std::pair<int, T>>> newTable(newCapacity);
            
            // Rehash every element
            for (size_t i = 0; i < _capacity; i++) {
                for (size_t j = 0; j < _hashtable[i].size(); j++) {
                    auto& pair = _hashtable[i][j];
                    size_t newIndex = pair.first % newCapacity;  // New hash!
                    newTable[newIndex].push_back(pair);
                }
            }
            
            _hashtable.swap(newTable);
            _capacity = newCapacity;
        }

        void checkResize(){
            float loadFactor = (float)_elementCount / _capacity;
            if (loadFactor > 0.7) {
                resize(); 
            }
        }

        public:
            MHashTable():_capacity(10), _elementCount(0), _hashtable(10){
            }

            void add(const int& key, const T& elem){
                int keyIndex = key % _capacity;

                for(size_t i = 0;i < _hashtable[keyIndex].size();++i){
                    if(key == _hashtable[keyIndex][i].first){
                        _hashtable[keyIndex][i].second = elem;
                        return;
                    }
                }

                _hashtable[key % _capacity].push_back({key, elem});
                _elementCount++;
                checkResize();
            }

            T& operator[](const int& key){
                int keyIndex = key % _capacity;
                
                //found return it
                for(size_t i = 0;i < _hashtable[keyIndex].size();++i){
                    if(key == _hashtable[keyIndex][i].first){
                        return _hashtable[keyIndex][i].second;
                    }
                }

                //not found create it
                _hashtable[keyIndex].push_back({key, T{}});
                _elementCount++;
                checkResize();
                return _hashtable[keyIndex].last().second;
            }

            bool contains(const int& key)const {
                int keyIndex = key % _capacity;
                for(size_t i = 0;i < _hashtable[keyIndex].size();++i){
                    if(key == _hashtable[keyIndex][i].first){
                        return true;
                    }
                }

                return false;
            }

            bool remove(const int& key){
                int keyIndex = key % _capacity;
                for(size_t i = 0;i < _hashtable[keyIndex].size();++i){
                    if(key == _hashtable[keyIndex][i].first){
                        std::swap(_hashtable[keyIndex][i].first, _hashtable[keyIndex].last);
                        _hashtable[keyIndex].pop_back();
                        --_elementCount;

                        return true;
                    }
                }

                return false;
            }

            size_t size()const {
                return _elementCount;
            }
    };
}
