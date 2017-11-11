#include <iostream>

using namespace std;

template<typename Key, typename Value>
class sList {
    private:
        struct NodeData {
            Key key;
            Value value;
            bool operator==(const NodeData& other) const;
        };
        struct Node : NodeData {
            Node* next = NULL;
        };
        template<typename K, typename V>
        class Iterator : std::iterator<std::forward_iterator_tag, NodeData>{
            public:
                Iterator();
                Iterator(const Iterator&);
                bool operator==(const Iterator<K, V>& other) const;
                bool operator!=(const Iterator<K, V>& other) const;
                Iterator operator++(int);
                Iterator& operator++();
                Value& operator*() const; ///dereferencing end() results in undefined behavior
            private:
                friend class sList;
                Node* ptr;
                Iterator(const Node&);
                Iterator& operator=(const Node& toAssign);
        };
        Node* head;
        Node* tail;
        int listSize;
        void makeSentinel();
    public:
        sList();
        ~sList();
        sList(const sList<Key, Value>& toCopy);
        Iterator<Key, Value> begin() const;
        Iterator<Key, Value> end() const;
        void pushFront(Key key, Value val);
        void pushBack(Key key, Value val);
        void pushAfter(Key key, int pos = 1);
        void removeFront();
        void removeBack();
        void removeKey(Key key); ///Removes all key occurances
        void removeValue(Value val); ///Removes all key occurances
        void clear();
        void print() const;
        void printByKey(Key key) const; ///prints all key occurances
        void printByValue(Value value) const; ///prints all value occurances
        int size() const;
        sList& operator=(const sList<Key, Value>& toAssign);
        Key findKey(Value val, int pos = 1) const; ///returns key of n'th val appearance in sList, otherwise throws "No Key Found"
        Iterator<Key, Value> findByKey(Key key, int pos = 1) const;///returns n'th appearance of key in sList, otherwise returns end()
        bool keyExists(Key key) const;
        static void interleave(const sList<Key, Value>& first, int fcount, const sList<Key, Value>& second, int scount, sList<Key, Value>& result);
        ///clear result before copying
        ///merges fcount elements from first to result list, then scount elements from second to result list, repeats until result contains all elements from both
};

template<typename Key, typename Value>
bool sList<Key, Value>::NodeData::operator==(const NodeData& other) const  {
    return this == other;
}

template<typename Key, typename Value>
template<typename K, typename V>
sList<Key, Value>::Iterator<K, V>& sList<Key, Value>::Iterator<K, V>::operator=(const Node& toAssign) {
    ptr = const_cast<Node*>(&toAssign); return *this;
}

template<typename Key, typename Value>
template<typename K, typename V>
sList<Key, Value>::Iterator<K, V>::Iterator() {
    ptr = NULL;
}

template<typename Key, typename Value>
template<typename K, typename V>
sList<Key, Value>::Iterator<K, V>::Iterator(const Node& node) {
    ptr = const_cast<Node*>(&node);
}

template<typename Key, typename Value>
template<typename K, typename V>
sList<Key, Value>::Iterator<K, V>::Iterator(const Iterator& toCopy) {
    ptr = toCopy.ptr;
}

template<typename Key, typename Value>
template<typename K, typename V>
bool sList<Key, Value>::Iterator<K, V>::operator==(const Iterator<K, V>& other) const {
    return ptr == other.ptr;
}

template<typename Key, typename Value>
template<typename K, typename V>
bool sList<Key, Value>::Iterator<K, V>::operator!=(const Iterator<K, V>& other) const {
    return ptr != other.ptr;
}

template<typename Key, typename Value>
template<typename K, typename V>
sList<Key, Value>::Iterator<K, V> sList<Key, Value>::Iterator<K, V>::operator++(int) {
    if(this->ptr && this->ptr->next != NULL) this->ptr = ptr->next;
    return *this;
}

template<typename Key, typename Value>
template<typename K, typename V>
sList<Key, Value>::Iterator<K, V>& sList<Key, Value>::Iterator<K, V>::operator++() {
    if(this->ptr && this->ptr->next != NULL) this->ptr = ptr->next;
    return *this;
}

template<typename Key, typename Value>
template<typename K, typename V>
Value& sList<Key, Value>::Iterator<K, V>::operator*() const  {
    return ptr->value;
}

template<typename Key, typename Value>
void sList<Key, Value>::makeSentinel() {
    Node* sentinel = new Node();
    sentinel->next = NULL;
    if(!head) {
        head = sentinel;
        tail = sentinel;
    } else
        tail->next = sentinel;
}

template<typename Key, typename Value>
sList<Key, Value>::sList() : head(NULL), listSize(0) {
    makeSentinel();
}

template<typename Key, typename Value>
sList<Key, Value>::~sList() {
    if(!listSize)
        return;
    Node* el = head;
    Node* prev = head;
    do{
        prev = el;
        el = el->next;
        delete prev;
    } while(el);
}

template<typename Key, typename Value>
sList<Key, Value>::sList(const sList<Key, Value>& toCopy) : head(NULL), listSize(0) {
    makeSentinel();
    for(sList<Key, Value>::Iterator<Key, Value> i = toCopy.begin(); i != toCopy.end(); ++i){
        pushBack(i.ptr->key, i.ptr->value);
    }
}

template<typename Key, typename Value>
sList<Key, Value>::Iterator<Key, Value> sList<Key, Value>::begin() const {
    Iterator<Key, Value> result;
    result = *head;
    return result;
}

template<typename Key, typename Value>
sList<Key, Value>::Iterator<Key, Value> sList<Key, Value>::end() const {
    Iterator<Key, Value> result;
    if(!listSize) {
        result = *tail;
    } else {
        result = *(tail->next);
    }
    return result;
}

template<typename Key, typename Value>
void sList<Key, Value>::pushFront(Key key, Value val) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->value = val;
    newNode->next = head;
    head = newNode;
    if(!listSize++) {
        tail = newNode;
    }
}

template<typename Key, typename Value>
void sList<Key, Value>::pushBack(Key key, Value val) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->value = val;
    if(!listSize++) {
        newNode->next = tail;
        head = newNode;
    } else {
        newNode->next = tail->next;
        tail->next = newNode;
    }
    tail = newNode;
}


template<typename Key, typename Value>
void sList<Key, Value>::pushAfter(Key key, int pos) {
    ///TODODODODO
}

template<typename Key, typename Value>
void sList<Key, Value>::removeFront() {
    if(!listSize) {
        return;
    } else {
        Node* ptr = head->next;
        if(listSize == 1) {
            tail = ptr;
        }
        delete head;
        head = ptr;
        --listSize;
    }
}

template<typename Key, typename Value>
void sList<Key, Value>::removeBack() {
    if(!listSize) {
        return;
    } else {
        Node* ptr = head;
        if(ptr != tail) {
            while(ptr->next != tail){
                ptr = ptr->next;
            }
            ptr->next = tail->next;
            delete tail;
            tail = ptr;
        } else {
            head = tail = ptr->next;
            delete ptr;
        }
        --listSize;
    }
}

template<typename Key, typename Value>
void sList<Key, Value>::removeKey(Key key) {
    for(sList<Key, Value>::Iterator<Key, Value> i = begin(), j = begin(); i != end(); ) {
        if(i.ptr->key == key) {
            if(i.ptr == head) {
                if(listSize == 1) {
                    head = head->next;
                    delete tail;
                    tail = head;
                    --listSize;
                    return;
                }
                head = i.ptr->next;
                delete i.ptr;
                --listSize;
                j = i = *head;
                continue;
            }
            if(i.ptr == tail) {
                tail = static_cast<Node*>(j.ptr);
            }
            j.ptr->next = i.ptr->next;
            delete i.ptr;
            --listSize;
            i = *j.ptr->next;
            continue;
        }
        j = i;
        i++;
    }
}

template<typename Key, typename Value>
void sList<Key, Value>::removeValue(Value val) {
    for(sList<Key, Value>::Iterator<Key, Value> i = begin(), j = begin(); i != end(); ) {
        if(i.ptr->value == val) {
            if(i.ptr == head) {
                if(listSize == 1) {
                    head = head->next;
                    delete tail;
                    tail = head;
                    --listSize;
                    return;
                }
                head = i.ptr->next;
                delete i.ptr;
                --listSize;
                j = i = *head;
                continue;
            }
            if(i.ptr == tail) {
                tail = static_cast<Node*>(j.ptr);
            }
            j.ptr->next = i.ptr->next;
            delete i.ptr;
            --listSize;
            i = *j.ptr->next;
            continue;
        }
        j = i;
        i++;
    }
}

template<typename Key, typename Value>
void sList<Key, Value>::clear() {
    if(!listSize)
        return;
    Node* el = head;
    Node* prev = head;
    do{
        prev = el;
        el = el->next;
        delete prev;
    } while(el);
    listSize = 0;
    makeSentinel();
}

template<typename Key, typename Value>
void sList<Key, Value>::print() const {
    for(sList<Key, Value>::Iterator<Key, Value> i = begin(); i != end(); ++i) {
        cout << "Key: " << i.ptr->key << " Value: " << i.ptr->value << endl;
    }
}

template<typename Key, typename Value>
void sList<Key, Value>::printByKey(Key key) const {
    for(sList<Key, Value>::Iterator<Key, Value> i = begin(); i != end(); ++i) {
        if(i.ptr->key == key) cout << "Key: " << i.ptr->key << " Value: " << i.ptr->value << endl;
    }
}

template<typename Key, typename Value>
void sList<Key, Value>::printByValue(Value value) const {
    for(sList<Key, Value>::Iterator<Key, Value> i = begin(); i != end(); ++i) {
        if(i->value == value) cout << "Key: " << i->key << " Value: " << i->value << endl;
    }
}

template<typename Key, typename Value>
int sList<Key, Value>::size() const {
    return listSize;
}

template<typename Key, typename Value>
sList<Key, Value>& sList<Key, Value>::operator=(const sList<Key, Value>& toAssign) {
    if(this == toAssign) return *this;
    clear();
    for(sList<Key, Value>::Iterator<Key, Value> i = toAssign.begin(); i != toAssign.end(); ++i){
        pushBack(i->key, i->value);
    }
    return *this;
}

template<typename Key, typename Value>
Key sList<Key, Value>::findKey(Value val, int pos) const {
    for(sList<Key, Value>::Iterator<Key, Value> i = begin(); i != end(); ++i) {
        if(i.ptr->value == val && !--pos) return i.ptr->key;
    }
    throw "No Key Found";
}

template<typename Key, typename Value>
sList<Key, Value>::Iterator<Key, Value> sList<Key, Value>::findByKey(Key key, int pos) const {
    for(sList<Key, Value>::Iterator<Key, Value> i = begin(); i != end(); ++i) {
        if(i.ptr->key == key && !--pos) return i;
    }
    return end();
}

template<typename Key, typename Value>
bool sList<Key, Value>::keyExists(Key key) const {
    for(sList<Key, Value>::Iterator<Key, Value> i = begin(); i != end(); ++i) {
        if(i->key == key) return true;
    }
    return false;
}

template<typename Key, typename Value>
void sList<Key, Value>::interleave(const sList<Key, Value>& first, int fcount,
                                   const sList<Key, Value>& second, int scount,
                                   sList<Key, Value>& result) {
    result.clear();
    sList<Key, Value>::Iterator<Key, Value> i = first.begin();
    sList<Key, Value>::Iterator<Key, Value> j = second.begin();
    bool turn = false;
    int counter = 0;
    if(!fcount) i = first.end();
    if(!scount) j = second.end();
    while(i != first.end() || j != second.end()) {
        if(i != first.end()) {
            if(!turn) {
                for(counter = fcount; counter > 0 && i != first.end(); --counter, ++i){
                    result.pushBack(i.ptr->key, i.ptr->value);
                }
            }
        }
        if(j != second.end()) {
            if(turn) {
                for(counter = scount; counter > 0 && j != second.end(); --counter, ++j){
                    result.pushBack(j.ptr->key, j.ptr->value);
                }
            }
        }
        turn = !turn;
    }
}

int main()
{
    sList<int, int> one;
    one.pushBack(5, 3);
    one.pushBack(2, 6);
    one.pushBack(2, 5);
    sList<int, int> two(one);
    sList<int, int> second;
    second.pushBack(51, 76);
    second.pushBack(34, 12);
    second.pushBack(78, 54);

    cout << "first\n";
    one.print();
    cout << "second\n";
    second.print();
    sList<int, int> inter;
    sList<int, int>::interleave(one, 2, second, 3, inter);
    cout << "Interleave!\n";
    inter.print();
    //cout << inter.keyExists(2) << endl;

    cout << "first: findBy test\n";
    one.pushBack(2, 9);
    one.pushBack(3, 3);
    one.print();
    cout << "findByKey(2): " << *one.findByKey(2) << endl;
    cout << "findByKey(2, 3): " << *one.findByKey(2, 3) << endl;
    cout << "findByKey(2, 4): " << *one.findByKey(2, 4) << " returns end()" << endl;
    cout << "dereferencing end(): " << *one.end() << endl;
    cout << "findKey(3): " << one.findKey(3) << endl;
    cout << "findKey(3): " << one.findKey(3, 2) << endl;
    try{
        cout << "findKey(2): " << one.findKey(2) << endl;
    } catch(const char* a) {
        cout << a << endl;
    }
    cout << "first\n";
    one.print();
    cout << "first removeKey\n";
    one.removeKey(5);
    one.print();
    cout << "first removeValue\n";
    one.removeValue(5);
    one.print();
    cout << "trying:\n";
    int a = 5;
    int b = 43;
    sList<int, int*> tri;
    tri.pushBack(0, &a);
    tri.pushBack(1, &b);
    for(const auto& i : tri) {
        cout << *i << endl;
    }
    return 0;
}
