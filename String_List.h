// Student ID: 20446043

#ifndef String_List_h
#define String_List_h

#include <iostream>
#include <sstream>

// Important implementation note: With the exception of to_string(),
// and clear(), all list methods below should operate in a constant amount
// of time regardless of the size of the String_List instance.
//
// The semantics of _prev_to_current is such that it always points to the
// node *BEFORE* the current one. This makes the manipulations easy because
// we can only look forward (and not back) in singly linked lists.
//
// I've included some method header comments below where there's likely to
// be confusion.
//
class String_List {
private:

    struct Node {
        std::string data;
        Node *next;
        Node(std::string s = "") : data(s), next(nullptr) {}
    };
    
    Node *_head, *_tail, *_prev_to_current;
    size_t _size;

public:

    String_List() {
    
        Node* newNode = new Node();
        newNode->data = "_SENTINEL_";
        newNode->next = nullptr;

        _head = newNode;
        _tail = newNode;
        _prev_to_current = newNode;
        _size = 0;

    }

    ~String_List() {
    
        delete _head;

    }

    String_List *insert_at_current(std::string s) {
    
        Node* newNode = new Node();

        if (_size == 0 || _prev_to_current == _tail) {

            _tail = newNode;

        }

        newNode->data = s;
        newNode->next = _prev_to_current->next;
        _prev_to_current->next = newNode;

        _size++;

        return this;

    }

    String_List *push_back(std::string s) {
    
        Node* temp = _prev_to_current;
        insert_at_current(s);
        _prev_to_current = temp;

        //Node* newNode = new Node();
        //newNode->data = s;
        //newNode->next = nullptr;
        //_prev_to_current->next = newNode;
        //_tail = newNode;

        //_prev_to_current = temp;

        //_size++;

        return this;

    }

    String_List *push_front(std::string s) {
    
        //Node* temp = _prev_to_current;
        //_head->next = temp;
        //insert_at_current(s);
        //_prev_to_current = temp;

        Node* newNode = new Node();
        newNode->data = s;
        newNode->next = _head->next;
        _head->next = newNode;
        _size++;

        return this;

    }

    String_List *advance_current() {
    
        if (_prev_to_current == _tail) {

            return nullptr;

        }

        _prev_to_current = _prev_to_current->next;
        return this;

    }
    
    std::string get_current() const {
    
        if (_prev_to_current != nullptr) {

            return _prev_to_current->data;

        }

        return "_SENTINEL_";

    }

    String_List *remove_at_current() {
    
        if (_prev_to_current == _tail) {
        
            return this;

        }
        else if (_prev_to_current->next != _tail) {

            Node* temp = _prev_to_current->next;
            _prev_to_current->next = _prev_to_current->next->next;
            delete temp;

        }
        else if (_prev_to_current->next == _tail) {

            Node* temp = _tail;
            _tail = _prev_to_current;
            delete temp;

        }
        
        _size--;

        return this;

    }

    size_t get_size() const {
    
        return _size;

    }

    String_List *rewind() {
    
        _prev_to_current = _head;
        return this;

    }

    void clear() {
    
        while(_head->next != nullptr) {

            Node* temp = _head->next->next;
            delete _head->next;
            _head->next = temp;

        }

        _prev_to_current = _head;
        _tail = _head;

        _head->next = nullptr;

    }

    // Find a specific item. Does NOT change cursor.
    //
    // The following returns a reference to the target string if found. But what will
    // you do if you didn't find the requested string? Using sentinel markers is
    // one way to handle that situation. Usually there's only one copy of the
    // sentinel that's global. We will use a local one so it's cleaner with a
    // little more risk (what's the risk?)
    //
    std::string& find_item(std::string s) const {
    
        return _prev_to_current->data;

    }

    // Print up to max_lines lines starting at _prev_to_current->next. If the caller
    // wants to print from the beginning of the list, they should rewind() it first.
    //
    std::string to_string() const {

        std::string list = "# String_List - " + std::to_string(_size) + " entries total. Starting at cursor:\n";

        /*int count = 0;
        while (count < 25 || count < _size) {

            list += _prev_to_current->next->data + "\n";

        }

        if (_size > 25) {

            list += "...\n";

        }*/

        return list;

    }

    friend class Tests; // Don't remove this line

};
#endif
