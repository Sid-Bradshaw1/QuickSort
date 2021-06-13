//
// Created by Sid Bradshaw on 2/10/21.
//

#ifndef ITERATOR_LIST_H
#define ITERATOR_LIST_H
#include <iostream>
#include "interface.h"
#include <string>
#include <sstream>
using namespace std;

template<typename T>
class list : public LinkedListInterface<T> {

private:
    struct node {
        T data;
        node* next;
        node(const T& d, node* n) : data(d), next(n) {}
        ~node() = default;
    };
    node* head = NULL;
    int counterVar = 0;

public:
    list() : head(NULL) {}
    ~list() {clear();}



    node* find(const T& item){
        node* node_ptr = head;
        while (node_ptr != NULL){
            if (node_ptr->data == item) break;
            node_ptr = node_ptr->next;
        }
    }

    friend ostream& operator<< (std::ostream& os, list<T>& list){
        os << list.toString();
        return os;
    }

    class Iterator {
    private:
        node* iNode;
        //list<T>* parent;

    public:
        Iterator(node* head) : iNode(head) { }
        ~Iterator() = default;
        friend class list<T>;

        bool operator!=(const Iterator& rhs) const {
            //cout << " Iterator::operator!=() ";
            return this->iNode != rhs.iNode;
        }

        bool operator==(const Iterator& rhs) const {
            //cout << " Iterator::operator!=() ";
            return this->iNode == rhs.iNode;
        }

        Iterator& operator++() {

            iNode = iNode->next;
            return *this;
        }

        T& operator*() const {

            return iNode->data;
        }

        node* getiNode(){
            return iNode;
        }
        void setiNode(node* parameter){
            iNode = parameter;

        }
        string toString() const {
            ostringstream out;
            out << iNode->data;
            return out.str();
        }
        friend ostream& operator<< (std::ostream& os, const Iterator& iter){
            os << iter.toString();
            return os;
        }

    };

    /** Return iterator pointing to the first value in linked list */
    Iterator begin(void){
        return list<T>::Iterator(head);
    }

    /** Return iterator pointing to something not in linked list */
    Iterator end(void){
        return list<T>::Iterator(NULL);
    }

    /** Return iterator pointing found value in linked list */
    Iterator find(Iterator first, Iterator last, const T& value){
        node *node_ptr = head;
        while (1){
            if (first == last) {
                return last;
            }
            else if (node_ptr->data == value){
                return first;
            }
            else{
                ++first;
                node_ptr = node_ptr->next;
            }

        }
    }

    /** Return iterator pointing to inserted value in linked list */
    Iterator insert(Iterator position, const T& value){
        node* node_ptr = position.getiNode();
        node* node_Prev = head;
        while(node_Prev->next != node_ptr){
            node_Prev = node_Prev->next;
        }
        node* nodeVar = new node(value, node_Prev->next);
        node_Prev->next = nodeVar;
        position.setiNode(nodeVar);

        return position;
    }

    /** Return iterator pointing to inserted value in linked list */
    Iterator insert_after(Iterator position, const T& value){
        node* node_ptr = position.getiNode();
        node* nextNode = node_ptr->next;
        node* nodeVar = new node(value, nextNode);
        node_ptr->next = nodeVar;

        return ++position;
    }

    /** Return iterator pointing to next item after deleted node linked list */
    Iterator erase(Iterator position){
        node* node_ptr = position.getiNode();
        if(node_ptr == NULL){
            return position;
        }
        if(node_ptr->next == NULL){
            remove(node_ptr->data);
            return position;
        }
        remove(node_ptr->data);

        return position;
    }

    /** Replace first found old_value(s) with new_value */
    void replace(Iterator first, Iterator last, const T& old_value, const T& new_value){
        node *node_ptr = head;
        while (node_ptr != NULL){
            if (first == last){
                break;
            }
            else if (node_ptr->data == old_value){
                node_ptr->data = new_value;
                node_ptr = node_ptr->next;
            }
            else{
                ++first;
                node_ptr = node_ptr->next;
            }

        }
    }




    /** Insert Node(value) at beginning of linked list */
    void push_front(const T& value){
        head = new node(value, head);
        counterVar++;
    }

    /** Remove Node at beginning of linked list */
    void pop_front(void){
        if(counterVar == 0){
            return;
        }

        node* node_ptr = head;
        head = head->next;
        delete node_ptr;
    }

    /** Return reference to value of Node at beginning of linked list */
    T& front(void){
        return head->data;
    }

    /** Return true if linked list size == 0 */
    bool empty(void) const{
        if(counterVar > 0){
            return false;
        }
        else {
            return true;
        }

    }

    /** Remove all Nodes with value from linked list */
    void remove(const T& value){
        node* node_ptr = head;
        while(node_ptr != NULL) {
            if(counterVar == 0){
                break;
            }

            if(head->data == value){
                head = head->next;
                delete node_ptr;
                node_ptr = head;
                counterVar--;
                break;
            }
            else if(node_ptr->next == NULL){
                break;
            }

            else if(node_ptr->next->data == value){
                node* delete_ptr = node_ptr->next;
                node_ptr->next = node_ptr->next->next;
                delete_ptr->next = NULL;
                delete delete_ptr;
                counterVar--;
                break;
            }


            else {
                node_ptr = node_ptr->next;

            }


        }


    }


    /** Remove all Nodes from linked list */
    void clear(void){
        if(counterVar == 0){
            return;
        }
        node* node_ptr = head;
        while (node_ptr != NULL){
            node* saved_ptr = node_ptr->next;
            delete node_ptr;
            node_ptr = saved_ptr;
        }
        head = NULL;
        counterVar = 0;
        return;
    }

    /** Reverse Nodes in linked list */
    void reverse(void){
        node* node_ptr = head;
        node* prevItem = NULL;
        node* next = NULL;
        while (node_ptr != NULL){
            next = node_ptr->next;
            node_ptr->next = prevItem;
            prevItem = node_ptr;
            node_ptr = next;
        }
        head = prevItem;
    }


    /** Return the number of nodes in the linked list */
    size_t size(void) const{
        return counterVar;
    }

    /** Return contents of Linked List as a string */
    string toString() const{
        stringstream out;
        node* node_ptr = head;
        while (node_ptr != NULL) {
            out << node_ptr->data << (node_ptr->next != NULL ? " " : "");
            node_ptr = node_ptr->next;
        }
        if (head == NULL){
            out << "Empty!";
        }
        return out.str();
    }


};

#endif //LINKEDLIST_LIST_H
