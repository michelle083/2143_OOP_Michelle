/*****************************************************************************
*
*  Author:           Michelle Orru
*  Title:            Singly linked list vector implementation
*  Course:           2143
*  Semester:         Fall 2021
*
*  Description:
*        Uses a singly linked list as the backend for an STL like "vector"
*        class definition.
*
*****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>

#define INF = 1000000000

using namespace std;

// Node for our linked list
struct Node {
    int data;

    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};


/*
||   / / //   / /  //   ) ) /__  ___/ //   ) ) //   ) )       //   ) )  / /        // | |     //   ) ) //   ) )
||  / / //____    //          / /    //   / / //___/ /       //        / /        //__| |    ((       ((
|| / / / ____    //          / /    //   / / / ___ (        //        / /        / ___  |      \\       \\
||/ / //        //          / /    //   / / //   | |       //        / /        //    | |        ) )      ) )
|  / //____/ / ((____/ /   / /    ((___/ / //    | |      ((____/ / / /____/ / //     | | ((___ / /((___ / /
*/

class MyVector {
private:
    Node* head;  // base pointer of list
    Node* tail;
    int size;
    static ofstream fout;
    string infileName;
    bool sorted;

    /**
     * @brief Private version of inOrder push.
     *
     * @param x
     */
    void _inorderPush(int x) {
        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (curr->data > x) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
    }

public:
    /**
     * @brief Default constructor
     *
     */
    MyVector() {
        init();
    }

    /**
     * @brief Overloaded Constructor
     *
     * @param int   *A - pointer to array
     * @param int   aSize - size of array
     */
    MyVector(int A[], int aSize) {
        init();

        for (int i = 0; i < aSize; i++) {
            pushRear(A[i]);
        }
    }

    /**
     * @brief Overloaded Constructor
     *
     * @param string infileName - file to open and read
     *
     * Assumes infile will contain numbers only delimited by spaces or
     * new lines.
     */
    MyVector(string infileName) {
        init();

        ifstream infile;
        int x = 0;

        infile.open(infileName);
        while (!infile.eof()) {
            infile >> x;
            pushRear(x);
        }
    }

    /**
     * @brief Copy Constructor
     *
     * @param MyVector &other
     */
    MyVector(const MyVector& other) {
        init();

        Node* traverse = other.head;
        while (traverse) {		//while loop that traverses the whole list and pushes the data from the V2 to V1
            pushRear(traverse->data);
            traverse = traverse->next;
        }
    }

    /**
     * @brief - Initialize the data members so we don't
     *      have duplicate lines in each constructor.
     *
     */
    void init() {
        head = tail = NULL;
        infileName = " "; 
        size = 0;
        sorted = 0;
    }


    /**
     * @brief Public version of inOrder push.
     *
     * @param x
     */
    void inorderPush(int x) {
        if (!sorted) {
            sortList();
        }

        if (!head) {
            pushFront(x);  // call push front for empty list (or pushRear would work)
        }
        else if (x < head->data) {
            pushFront(x);  // call push front if x is less than head
        }
        else if (x > tail->data) {
            pushRear(x);  // call push rear if x > tail
        }
        else {
            _inorderPush(x);  // call private version of push in order
        }
    }

    /**
     * @brief Sort the current values in the linked list.
     *
     * @returns None
     */
    void sortList() {
        Node* newFront = head;

        while (newFront->next) {
            Node* smallest = newFront;
            Node* current = newFront;
            int   minimum = 1000000000;

            while (current) {
                if (current->data < minimum) {
                    smallest = current;
                    minimum = current->data;
                }
                current = current->next;
            }

            smallest->data = newFront->data;
            newFront->data = minimum;
            newFront = newFront->next;
        }

        sorted = true;
    }

    /**
     * @brief Add value to front of list.
     *
     * @param x
     */
    void pushFront(int x) {
        Node* tempPtr = new Node(x);

        // empty list make head and tail
        // point to new value
        if (!head) {
            head = tail = tempPtr; 
            // otherwise adjust head pointer
        }
        else {
            tempPtr->next = head; 
            head = tempPtr; 
        }

        size++;
    }

    /**
     * @brief This method loads values from 'other' list in 'this' list.
     *          It loads an array first so we can process the values in
     *          reverse so they end up on 'this' list in the proper order.
     *          If we didn't use the array, we would reverse the values
     *          from the 'other' list.
     *
     * @depends - Uses `pushFront(int)`
     * @param MyVector& other
     * @return None
     */
    void pushFront(const MyVector& other) {
        Node* otherPtr = other.head;           // get copy of other lists head
        int* tempData = new int[other.size];  // allocate memory to hold values

        // load other list into array
        int i = 0;
        while (otherPtr) {
            tempData[i] = otherPtr->data;
            otherPtr = otherPtr->next;
            ++i; 
        }

        // process list in reverse in order to keep them
        // in their original order.
        for (int i = other.size - 1; i >= 0; i--) {
            pushFront(tempData[i]); 
        }
    }

    /**
     * @brief -  Add 'other' list's values to end of 'this' list.
     * @note - Uses `pushRear(int)`
     * @param MyVector& other
     * @return None
     */
    void pushRear(const MyVector& other) {
        Node* otherPtr = other.head;  // get copy of other lists head

        while (otherPtr) {  // traverse and add
            pushRear(otherPtr->data);
            otherPtr = otherPtr->next;
        }
    }

    /**
     * @brief Push value onto list at soecified position, if it exists.
     *
     * @param int i - location index
     * @param inr x - value to add
     * @return bool - true add successful / false add failed
     */
    bool pushAt(int i, int x) {
        if (i >= size) {
            return false;
        }

        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (i > 0) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
            i--;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
        return true;
    }

    /**
     * @brief - Add value to rear of list
     *
     * @param int x - value to be added
     * @return None
     */
    void pushRear(int x) {
        Node* tempPtr = new Node(x);

        if (!head) {
            head = tail = tempPtr;

        }
        else {
            tail->next = tempPtr;
            tail = tempPtr;
        }
        size++;  // add to size of list
    }

    friend ostream& operator<<(ostream& os, const MyVector& rhs) {
        Node* temp = rhs.head;  // temp pointer copies head

        while (temp) {  // this loops until temp is NULL
            // same as `while(temp != NULL)`

            os << temp->data;  // print data from Node
            if (temp->next) {
                os << "->";
            }
            temp = temp->next;  // move to next Node
        }
        os << endl;
        return os;
    }

    /**
     * @brief Destroy the My Vector object
     *
     */
    ~MyVector() {
        Node* curr = head;
        Node* prev = head;

        while (curr) {
            prev = curr;
            curr = curr->next;
            cout << "deleting: " << prev->data << endl;
            delete prev;
        }
    }

    
    //START OF PROGRAM 2
    

    //Overload << (ostream) so that printing to std out is easy
    friend ofstream& operator<<(ofstream&, const MyVector&);

    //Overload << (ofstream) so that printing to out-file is easy.
    friend ofstream& operator>>(ofstream&, const MyVector&);

    //Overload [] so that your MyVector can be treated as an array
    //friend MyVector& operator[](const MyVector&, const MyVector&);

    //Overload + (addition)
    friend MyVector& operator+(const MyVector&, const MyVector&);

    //Overload - (subtraction)
    friend MyVector& operator-(const MyVector&, const MyVector&);

    //Overload * (multiplication)
    friend MyVector& operator*(const MyVector&, const MyVector&);

    //Overload / (division)
    friend MyVector& operator/(const MyVector&, const MyVector&);

    //Overload == (equality)
    friend bool operator==(const MyVector&, const MyVector&);

    //Overload = (assignment)
    //friend ofstream& opearator=(ofstream&, const MyVector&);
    
};

//Overload << (ostream) so that printing to std out is easy
ofstream& operator<<(ofstream& outfile, const MyVector& M) {
    Node* traverse = M.head;

    while (traverse != NULL) {					//goes through entire list and dispalays as it traverses
        outfile << traverse->data << " ";
        traverse = traverse->next;
    }

    return outfile;
}

//Overload >> (ofstream) so that printing to out-file is easy.
ofstream& operator>>(ofstream& os, const MyVector& M) {
    Node* traverse = M.head;

    while (traverse != NULL) {					//goes through entire list and dispalays as it traverses
        os << traverse->data << " ";
        traverse = traverse->next;
    }

    return os;
}

//Overload + (addition)
MyVector& operator+(const MyVector& a, const MyVector& b) {
        MyVector M;

        Node* traverse1 = a.head;
        Node* traverse2 = b.head;

        int aSize = 0;
        int bSize = 0;

        //  getting the sizes of the vectors that will be added 
        while (traverse1) {
            aSize++;
            traverse1 = traverse1->next;
        }
        while (traverse2) {
            bSize++;
            traverse2 = traverse2->next;
        }

        // repointing traverse to heads
        traverse1 = a.head;
        traverse2 = b.head;
        // checks if the first vector is larger that the other 
        if (aSize > bSize) {
            // adds the elements of both vectors and pushes to the rear 
            for (int i = 0; i != bSize; i++) {
                M.pushRear(traverse1->data + traverse2->data);
                traverse1 = traverse1->next;
                traverse2 = traverse2->next;
            }
            // pushes the remaining elements of the first vector
            while (traverse1) {
                M.pushRear(traverse1->data);
                traverse1 = traverse1->next;
            }
            delete traverse1;
            delete traverse2;
            return M;
        }

        // checks if the second vector is larger than the other 
        else if (bSize > aSize) {
            // adds the elements and pushes to new vector
            for (int i = 0; i != aSize; i++) {
                M.pushRear(traverse1->data + traverse2->data);
                traverse1 = traverse1->next;
                traverse2 = traverse2->next;
            }
            //pushes the remaining elements in the second vector 
            while (traverse2) {
                M.pushRear(traverse2->data);
                traverse2 = traverse2->next;
            }
            delete traverse1;
            delete traverse2;
            return M;
        }

        else {
            // adds the elements and pushes them to the new vector
            while (traverse1) {
                M.pushRear(traverse1->data + traverse2->data);
                traverse1 = traverse1->next;
                traverse2 = traverse2->next;
            }
            delete traverse1;
            delete traverse2;
            return M;
        }

}

//Overload - (subtraction)
MyVector& operator-(const MyVector& a, const MyVector& b) {
    MyVector M;

    Node* traverse1 = a.head;
    Node* traverse2 = b.head;

    int aSize = 0;
    int bSize = 0;

    //  getting the sizes of the vectors that will be added 
    while (traverse1) {
        aSize++;
        traverse1 = traverse1->next;
    }
    while (traverse2) {
        bSize++;
        traverse2 = traverse2->next;
    }

    // repointing traverse to heads
    traverse1 = a.head;
    traverse2 = b.head;
    // checks if the first vector is larger that the other 
    if (aSize > bSize) {
        // adds the elements of both vectors and pushes to the rear 
        for (int i = 0; i != bSize; i++) {
            M.pushRear(traverse1->data - traverse2->data);
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        // pushes the remaining elements of the first vector
        while (traverse1) {
            M.pushRear(traverse1->data);
            traverse1 = traverse1->next;
        }
        delete traverse1;
        delete traverse2;
        return M;
    }

    // checks if the second vector is larger than the other 
    else if (bSize > aSize) {
        // adds the elements and pushes to new vector
        for (int i = 0; i != aSize; i++) {
            M.pushRear(traverse1->data - traverse2->data);
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        //pushes the remaining elements in the second vector 
        while (traverse2) {
            M.pushRear(traverse2->data);
            traverse2 = traverse2->next;
        }
        delete traverse1;
        delete traverse2;
        return M;
    }

    else {
        // adds the elements and pushes them to the new vector
        while (traverse1) {
            M.pushRear(traverse1->data - traverse2->data);
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        delete traverse1;
        delete traverse2;
        return M;
    }
}

//Overload * (multiplication)
MyVector& operator*(const MyVector& a, const MyVector& b) {
    MyVector M;

    Node* traverse1 = a.head;
    Node* traverse2 = b.head;

    int aSize = 0;
    int bSize = 0;

    //  getting the sizes of the vectors that will be added 
    while (traverse1) {
        aSize++;
        traverse1 = traverse1->next;
    }
    while (traverse2) {
        bSize++;
        traverse2 = traverse2->next;
    }

    // repointing traverse to heads
    traverse1 = a.head;
    traverse2 = b.head;
    // checks if the first vector is larger that the other 
    if (aSize > bSize) {
        // adds the elements of both vectors and pushes to the rear 
        for (int i = 0; i != bSize; i++) {
            M.pushRear(traverse1->data * traverse2->data);
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        // pushes the remaining elements of the first vector
        while (traverse1) {
            M.pushRear(traverse1->data);
            traverse1 = traverse1->next;
        }
        delete traverse1;
        delete traverse2;
        return M;
    }

    // checks if the second vector is larger than the other 
    else if (bSize > aSize) {
        // adds the elements and pushes to new vector
        for (int i = 0; i != aSize; i++) {
            M.pushRear(traverse1->data * traverse2->data);
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        //pushes the remaining elements in the second vector 
        while (traverse2) {
            M.pushRear(traverse2->data);
            traverse2 = traverse2->next;
        }
        delete traverse1;
        delete traverse2;
        return M;
    }

    else {
        // adds the elements and pushes them to the new vector
        while (traverse1) {
            M.pushRear(traverse1->data * traverse2->data);
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        delete traverse1;
        delete traverse2;
        return M;
    }
}

//Overload / (division)
MyVector& operator/(const MyVector& a, const MyVector& b) {
    MyVector M;

    Node* traverse1 = a.head;
    Node* traverse2 = b.head;

    int aSize = 0;
    int bSize = 0;

    //  getting the sizes of the vectors that will be added 
    while (traverse1) {
        aSize++;
        traverse1 = traverse1->next;
    }
    while (traverse2) {
        bSize++;
        traverse2 = traverse2->next;
    }

    // repointing traverse to heads
    traverse1 = a.head;
    traverse2 = b.head;
    // checks if the first vector is larger that the other 
    if (aSize > bSize) {
        // adds the elements of both vectors and pushes to the rear 
        for (int i = 0; i != bSize; i++) {
            M.pushRear(traverse1->data / traverse2->data);
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        // pushes the remaining elements of the first vector
        while (traverse1) {
            M.pushRear(traverse1->data);
            traverse1 = traverse1->next;
        }
        delete traverse1;
        delete traverse2;
        return M;
    }

    // checks if the second vector is larger than the other 
    else if (bSize > aSize) {
        // adds the elements and pushes to new vector
        for (int i = 0; i != aSize; i++) {
            M.pushRear(traverse1->data / traverse2->data);
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        //pushes the remaining elements in the second vector 
        while (traverse2) {
            M.pushRear(traverse2->data);
            traverse2 = traverse2->next;
        }
        delete traverse1;
        delete traverse2;
        return M;
    }

    else {
        // adds the elements and pushes them to the new vector
        while (traverse1) {
            M.pushRear(traverse1->data / traverse2->data);
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        delete traverse1;
        delete traverse2;
        return M;
    }
}

//Overload == (equality)
bool operator==(const MyVector& a, const MyVector& b) {
    Node* traverse1 = a.head;
    Node* traverse2 = b.head;

    int aSize = 0;
    int bSize = 0;
    int total = 0;

    //  getting the sizes of the vectors that will be added 
    while (traverse1) {
        aSize++;
        traverse1 = traverse1->next;
    }
    while (traverse2) {
        bSize++;
        traverse2 = traverse2->next;
    }

    // repointing traverse to heads
    traverse1 = a.head;
    traverse2 = b.head;
    // checks if the first vector is larger that the other 
    if (aSize > bSize) {
        return false;
    }

    // checks if the second vector is larger than the other 
    else if (bSize > aSize) {
        return false;
    }

    else {
        // adds the elements and pushes them to the new vector
        while (traverse1) {
            if (traverse1->data == traverse2->data) {
                // increment count every time the elements are equal
                total++;
            }
            traverse1 = traverse1->next;
            traverse2 = traverse2->next;
        }
        delete traverse1;
        delete traverse2;

        if (total == aSize) {
            return true;
        }
        else {
            return false;
        }
    }
}

ofstream MyVector::fout;


int main() {
    MyVector V1;

    V1.pushFront(56);
    V1.pushFront(42);
    V1.pushFront(30);
    V1.pushFront(48);

    V1.pushFront(V1);

    cout << V1 << endl;

    V1.sortList();
    cout << V1 << endl;

    V1.pushAt(3, 88);
    cout << V1 << endl;
    V1.sortList();
    cout << V1 << endl;

    //main for program 2

    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 20, 30 };

    MyVector V3(a1, 5);
    MyVector V4(a2, 3);
    

    ofstream outfile;
    outfile.open("output.txt");
     
    //cout << v1[2] << endl;
    // writes out 3

    //v1[4] = 9;
    // v1 now = [1,2,3,4,9]

    cout << V3 << endl;
    // writes out [1,2,3,4,9] to console.

    outfile << V3 << endl;
    // writes out [1,2,3,4,9] to your output file.

    MyVector V5 = V3 + V4;
    cout << V5 << endl;
    // writes out [11,22,33,4,9] to console.

    V5 = V3 - V4;
    cout << V5 << endl;
    // writes out [-9,-18,-27,4,9] to console.

    V5 = V3 - V4;
    cout << V5 << endl;
    // writes out [9,18,27,4,9] to console.

    V5 = V3 * V4;
    cout << V5 << endl;
    // writes out [10,40,90,4,9] to console.

    V5 = V3 * V4;
    cout << V5 << endl;
    // writes out [10,40,90,4,9] to console.['

    V5 = V3 / V4;
    cout << V5 << endl;
    // writes out [0,0,0,4,9] to console.

    V5 = V4 / V3;
    cout << V5 << endl;
    // writes out [10,10,10,4,9] to console.

    cout << (V4 == V3) << endl;
    // writes 0 to console (false) .

    MyVector V6 = V3;
    cout << (V6 == V3) << endl;
    // writes 1 to console (true) . 
    
    outfile.close();
}
