#ifndef LIST342_H_
#define LIST342_H_

// Libraries
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Struct Node definition
template <class T> 
struct Node
{
    T *data;
    Node *next;
};

//Class List342 definition
template <class T> 
class List342
{

public:
    // constructors
    List342();
    List342(std::string file_name);
    List342(List342<T> &list);
    List342(const List342<T> &source); // copy constructor
    ~List342();


    // Action/verbs functions
    bool BuildList(std::string file_name);
    bool Insert(T *obj);
    bool Remove(T target, T &result);
    bool Peek(T target, T &result) const;
    int Size() const;
    void DeleteList();
    bool Merge(List342<T> &list1);

    // assignment operator
    List342<T>& operator=(const List342<T> &source);

    // other overload operators
    List342<T> operator+(const List342<T> &list) const;
    List342<T> &operator+=(List342<T> &list);
    bool operator==(const List342<T> &list) const;
    bool operator!=(const List342<T> &list) const;    


    // input and output stream operator
    template <class U>
    friend::ostream &operator<<(std::ostream &stream, const List342<U> &rhs);
    
private:
    // data members
    Node<T> *head_;
};
#endif

// Default constructor implementation
template <class T>
List342<T>::List342()
{
    this -> head_ = nullptr;
}

// 
template <class T>
List342<T>::List342(List342 &list)
{
    head_ = nullptr;
    *this = list;
}

// copy constructor
template <class T>
List342<T>::List342(std::string file_name)
{
    BuildList(file_name);
}

// Copy constructor declaration
template <class T>
List342<T>::List342(const List342<T> &source)
{
    head_ = nullptr;
    *this = source;
}

// BuildList implementation
template <class T>
bool List342<T>::BuildList(std::string file_name) 
{
    ifstream in_file;
    T temp;

    in_file.open(file_name);

    if (in_file.fail()) {
        std::cerr << "Error: Unable to open the file " << file_name << std::endl;
        return false;
    }

    while (in_file >> temp) {
        if (!Insert(&temp)) {
            std::cerr << "Error: Failed to insert object into the list." << std::endl;
            in_file.close();
            return false;
        }
    }

    in_file.close();
    return true;
} 

// Insert function implementation
template< class T>
bool List342<T>::Insert(T *obj)
{
    if (obj == nullptr)
    {
        cout << "Error: Null pointer passed to Insert" << endl;
        return false;
    }

    Node<T>* new_node = new Node<T>();
    new_node->data = new T(*obj);

    if (head_ == nullptr || *new_node ->data < *head_ -> data) 
    {
        new_node -> next = head_;
        head_ = new_node;
        return  true;
    }

    Node<T> *curr = head_;
    Node<T> * prev = nullptr;

    while(curr != nullptr && *curr -> data < * new_node -> data)
    {
        prev = curr;
        curr = curr -> next;
    }
    
    if(curr != nullptr && *new_node -> data == *curr -> data)
    {
        delete  new_node -> data;
        delete new_node;
        return false;
    }

    new_node->next = curr;
    if (prev != nullptr)
    {
        prev->next = new_node;
    }
    else
    {
        head_ = new_node;
    }
    return true;
    
}

// Remove function implementation
template< class T>
bool List342<T>::Remove(T target, T &result)
{
    //  create two pointers for traversing the list
    Node<T> *curr =head_;
    Node<T> *prev =nullptr;

    while(curr != nullptr && curr -> data != nullptr && !(*curr -> data == target))
    {
        prev = curr;
        curr = curr ->next;
    }

    if(curr == nullptr)
    {
        return false;
    }
    if (curr != nullptr)
    {
        if (prev == nullptr)
        {
            head_ = curr -> next;
        }
        else
        {
            prev -> next = curr -> next;
        }

        result = *(curr -> data);

        delete curr -> data;
        delete curr;
    }

    return true;
}

// Peek function implementation
template< class T>
bool List342<T>::Peek(T target, T &result) const
{
    // assigning the curr to head node
    Node<T> *curr = head_;

    while(curr && curr->data && *curr -> data != target)
    {
        curr = curr->next;
    }

    if(curr == nullptr || curr->data == nullptr)
    {
        return false;
    }

    result = *curr -> data;

    return true;
}

// Size function implementation
template< class T>
int List342<T>::Size() const
{
    int count = 0;  // Initialize a counter

    // Traverse the list and count the nodes
    Node<T> *curr = head_;
    while (curr != nullptr)
    {
        count++;
        curr = curr->next;
    }

    return count;
}


// DeleteList function implementation
template <class T>
void List342<T>::DeleteList() 
{
    // creating two nodes to traverse the list
    Node<T> *curr = head_;
    Node<T> *next_node = nullptr;

    while (curr != nullptr) 
    {
        next_node = curr->next; 
        if (curr->data != nullptr)
        {
            delete curr->data;
        }     
        delete curr;           
        curr = next_node;       
    }

    head_ = nullptr;
}

// Merge function implementation
template <class T>
bool List342<T>::Merge(List342<T> &list1)
{
    if (this == &list1 || list1.head_ == nullptr || head_ == nullptr)
    {
        return false;
    }

    Node<T> *curr1 = list1.head_;
    Node<T> *curr2 = this->head_;
    Node<T> *prev2 = nullptr;

    while (curr1 != nullptr && curr2 != nullptr)
    {
        if (*curr1->data < *curr2->data)
        {
            Node<T> *temp = curr1->next;
            curr1->next = curr2;

            if (prev2 == nullptr)
            {
                this->head_ = curr1;
            }
            else
            {
                prev2->next = curr1;
            }

            curr2 = curr1;
            curr1 = temp;
        }
        else if (*curr1->data == *curr2->data)
        {
            curr1 = curr1->next;
        }
        else
        {
            prev2 = curr2;
            curr2 = curr2->next;
        }
    }

    if (curr1 != nullptr)
    {
        if (prev2 != nullptr)
        {
            prev2->next = curr1;
        }
        else
        {
            this->head_ = curr1;
        }

        list1.head_ = nullptr;

        return true;
    }

    return false;
}

// Assignment operator implementation
template <class T>
List342<T> &List342<T>::operator=(const List342<T> &source)
{
    if (this != &source)
    {
        DeleteList();

        if (source.head_ != nullptr)
        {
            Node<T> *s_curr = source.head_;
            Node<T> *new_node = new Node<T>();
            if (s_curr->data != nullptr)
            {
                new_node->data = new T(*s_curr->data);
            }
            else
            {
                new_node->data = nullptr;
            }
            head_ = new_node;

            Node<T> *current = head_;

            while (s_curr->next != nullptr)
            {
                s_curr = s_curr->next;
                new_node = new Node<T>();
                if (s_curr->data != nullptr)
                {
                    new_node->data = new T(*s_curr->data);
                }
                else
                {
                    new_node->data = nullptr;
                }
                current->next = new_node;
                current = new_node;
            }
        }
    }
    return *this;
}

// plus operator function implementation
template< class T>    
List342<T> List342<T>::operator+(const List342<T> &list) const
{
    List342<T> result(*this);
    result += list;
    return result;
}

// += operator function implementation
template <class T>
List342<T> &List342<T>::operator+=(List342<T> &list)
{
    if (this == &list || list.head_ == nullptr)
    {
        return *this;
    }

    if (head_ == nullptr)
    {
        head_ = list.head_;
    }
    else
    {
        Node<T> *curr1 = list.head_;
        Node<T> *prev2 = nullptr;
        Node<T> *curr2 = head_;

        while (curr1 != nullptr && curr2 != nullptr)
        {
            if (*curr1->data < *curr2->data)
            {
                Node<T> *temp = curr1->next;
                curr1->next = curr2;

                if (prev2 == nullptr)
                {
                    head_ = curr1;
                }
                else
                {
                    prev2->next = curr1;
                }

                curr2 = curr1;
                curr1 = temp;
            }
            else if (*curr1->data == *curr2->data)
            {
                curr1 = curr1->next;
            }
            else
            {
                prev2 = curr2;
                curr2 = curr2->next;
            }
        }

        if (curr1 != nullptr)
        {
            if (prev2 != nullptr)
            {
                prev2->next = curr1;
            }
            else
            {
                head_ = curr1;
            }
        }
    }

    list.head_ = nullptr;

    return *this;
}

//  Equal operator fucntion implementation
template< class T>
bool List342<T>::operator==(const List342<T> &list) const
{
    Node<T> *curr1 = head_;
    Node<T> *curr2 = list.head_;

    while (curr1 != nullptr && curr2 != nullptr) 
    {
        if (*curr1->data != *curr2->data) 
        {
            return false;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return (curr1 == nullptr && curr2 == nullptr);
}

// not equal operator implementation
template< class T>
bool List342<T>::operator!=(const List342<T> &list) const
{
    return !(*this == list);
}    

// Output stream function implementation
template< class T>    
std::ostream &operator<<(std::ostream &stream, const List342<T> &rhs)
{
    // creating a node to traverse and print the datas of the nodes using while loop. 
    Node<T> *curr = rhs.head_;
    while (curr != nullptr) 
    {
        stream << *curr -> data;
        curr = curr -> next;
    }
    return stream;
}

// Destructor implementation
template <class T>
List342<T>::~List342()
{
    // deallocating memory for potential memory leak
    DeleteList();
}