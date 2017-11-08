#include <iostream>

using namespace std;

template<typename Key, typename Value>
class sList {
    public:
        sList();
        ~sList();
        sList(const sList<Key, Value>& toCopy);
        void pushFront(Key key, Value val);
        void pushBack(Key key, Value val);
        void addAfter(Key key, int pos = 1);
        void removeFront();
        void removeBack();
        void removeKey(Key key); ///Removes all key occurances
        void clear();
        void print();
        void print(Key key); ///prints all key occurances
        int size();
        sList& operator=(const sList<Key, Value>& toAssign);
        Key& findKey(Value val);
        bool keyExists(Key key);
        void interleave(const sList<Key, Value>& first, int fcount, const sList<Key, Value>& second, int scount, sList<Key, Value>& result);
        ///clear result before copying
        ///merges fcount elements from first to result list, then scount elements from second to result list, repeats until result contains all elements from both
    protected:
    private:
        struct Node {
            Key key;
            Value value;
            Node* next;
        };
        class Iterator {
            Node* ptr;
            public:
                Node& operator->() {};
                Node* operator->() const {};
        };
        const Iterator head;

};

template<typename Key, typename Value>
sList::sList() : head(NULL) {

}


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
