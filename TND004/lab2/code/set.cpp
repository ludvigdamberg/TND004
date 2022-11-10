#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

// Used for debug purposes -- static member function
// Return number of existing nodes
int Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

// Default constructor
Set::Set() : counter{0} {
    // IMPLEMENT before Lab1 HA

    head = new Node();
    tail = new Node();

    head->next = tail;
    tail->prev = head;
}

// Conversion constructor
Set::Set(int n) : Set{} {  // create an empty list
    // IMPLEMENT before Lab1 HA

    insert_node(tail, n);

}

// Constructor to create a Set from a sorted vector v
Set::Set(const std::vector<int>& v) : Set{} {  // create an empty list
                                               // IMPLEMENT before Lab1 HA

    for (long unsigned i = 0; i < v.size(); i++) { //Loop with i<v.size() and i++, O(n)
        insert_node(tail, v[i]); //Insert at tail, O(1)
    }
}

// Make the set empty
void Set::make_empty() {
    // IMPLEMENT before Lab1 HA

    Node* temp = head->next;

    while (temp != tail) { //Go trough the set O(n)
        Node* p = temp;
        temp = temp->next;
        remove_node(p); //delete the first node in set, O(1)
    }

    //Point to eachother as the default empty set
    head->next = tail;
    tail->prev = head;
}

// Destructor
Set::~Set() {
    // Member function make_empty() can be used to implement the destructor
    // IMPLEMENT before Lab1 HA

    make_empty(); //O(n)
    delete head;
    delete tail;
}

// Copy constructor
Set::Set(const Set& source) : Set{} {  // create an empty list
    // IMPLEMENT before Lab1 HA


    Node* p = source.head->next;

    while (p != source.tail) {
        insert_node(tail, p->value);

        p = p->next;


    }

}


// Copy-and-swap assignment operator

//The swap functyion is constant and should give the time commplexity O(3)
//Using the head and tail so that we dont have to search through the entire set. 
Set& Set::operator=(Set source) {
    // IMPLEMENT before Lab1 HA


    std::swap(counter, source.counter);

    std::swap(head, source.head);
    std::swap(tail, source.tail);


    return *this;
}

// Test set membership
bool Set::is_member(int val) const {
    // IMPLEMENT before Lab1 HA

    Node* p = head->next;

    while ((p != tail) && (p->value != val)) {

        p = p->next;

      
    }
    if (p == tail) {
        return false;
    }
    else {
        return true;
    }

    
}

// Test whether a set is empty
bool Set::is_empty() const {
    return (counter == 0);
}

// Return number of elements in the set
size_t Set::cardinality() const {
    return counter;
}

// Return true, if the set is a subset of b, otherwise false
// a <= b iff every member of a is a member of b
bool Set::less_than(const Set& b) const {
    // IMPLEMENT

    Node* p1 = b.head->next; //pointer to S2s head->next
    Node* p2 = head->next; //pointer to "this" head->next

    if (b.counter < counter) //If the wanted subset (S1) has more nodes than S2, return false
    {
        return false;
    }

    while (p2 != tail && p1 != b.tail) //As long as both sets has nodes to go trough
    {
        if (p2->value < p1->value) //If *this value is smaller than S2, return false (Sorted order)
        {
            return false;
        }
        else if (p2->value > p1->value) //If *this value are bigger than S2, continue to the next node in S2
        {
            p1 = p1->next;
        }
        else //Continue in both sets
        {
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return true;


}

// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {
    // IMPLEMENT
    Node* p1 = S.head->next;
    Node* p2 =  head->next;

    while (p1 != S.tail && p2 != tail) {

        if (p1->value < p2->value) {
            insert_node(p2, p1->value);
            p1 = p1->next;
        }
        else if (p1->value > p2->value) {
            
            p2 = p2->next;
        }
        else {

            p1 = p1->next;
            p2 = p2->next;
        }

    }

    while (p1 != S.tail) { //O(n1) add the rest of S's values into the end at *this
        insert_node(p2, p1->value); //O(1)
        p1 = p1->next;
        p2 = p2->next;
    }


    return *this;
}

// This operator looks for matching values in both sets. Through the if:s we check if values are matching,
// if they dont match we remove p2 and go to next until p2 is smaller than p1. If p1 is empty before we erase
//the excess numbers in p2. 
Set& Set::operator*=(const Set& S) {
    // IMPLEMENT


    Node* p1 = S.head->next;
    Node* p2 = head->next;

    while (p1 != S.tail && p2 != tail) {

        if (p1->value > p2->value) { //if S's value is bigger than *this value, remove the value from *this
            p2 = p2->next;
            remove_node(p2->prev);
        }

        else if (p1->value < p2->value) { //if S's value is smaller than *this value, value does not exist in *this, (sorted)
            p1 = p1->next;
        }

        else { // if the values are ==
            p1 = p1->next;
            p2 = p2->next;
        }

    }
    while (p2 != tail) {

        p2 = p2->next;

        remove_node(p2->prev);

    }



    return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {
    // IMPLEMENT
    Node* p1 = S.head->next;
    Node* p2 = head->next;

    while (p1 != S.tail && p2 != tail) { //O(n1+n2) As long as set S and *this has values
        if (p1->value > p2->value) { //if S's value is bigger than *this
            p2 = p2->next;

        }
        else if (p1->value < p2->value) { //if S's value is smaller than *this value, value does not exist in *this, (sorted)
            p1 = p1->next;
        }

        else { //If they are equal remove it from *this
            p1 = p1->next;
            p2 = p2->next;
            remove_node(p2->prev);
        }
    }
    return *this;
}

/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

// If you add any private member functions to class Set then write the implementation here


void Set::write_to_stream(std::ostream& os) const {
    if (is_empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp{head->next};

        os << "{ ";
        while (temp != tail) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
}


// Insert a new Node storing val after the Node pointed by p
void Set::insert_node(Node* p, int val) {
    // IMPLEMENT before Lab1 HA
    Node* newNode = new Node(val, p, p->prev); // Create new node with the value val, the pointer to right and the pointer to left
    p->prev = p->prev->next = newNode; //re-point the next nodes prev pointer and the previous nodes next pointer to the new node
    counter++;

}

// Remove the Node pointed by p
void Set::remove_node(Node* p) {
    // IMPLEMENT before Lab1 HA
   
        p->next->prev = p->prev;


        p->prev->next = p->next;

    delete p;
    counter--;

}
