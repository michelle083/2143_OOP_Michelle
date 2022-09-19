#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Node for the doubly linked list
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int d)
    {
        data = d;
        next = NULL;
        prev = NULL;
    }
};

/*
||   / / //   / /  //   ) ) /__  ___/ //   ) ) //   ) )       //   ) )  / /        // | |     //   ) ) //   ) )
||  / / //____    //          / /    //   / / //___/ /       //        / /        //__| |    ((       ((
|| / / / ____    //          / /    //   / / / ___ (        //        / /        / ___  |      \\       \\
||/ / //        //          / /    //   / / //   | |       //        / /        //    | |        ) )      ) )
|  / //____/ / ((____/ /   / /    ((___/ / //    | |      ((____/ / / /____/ / //     | | ((___ / /((___ / /
*/

class Vector {
private:
    Node* head;
    Node* tail;
    // int size;
    // string fileName;

public:

    /*

        /|    //| |     //   / / /__  ___/ //    / / //   ) ) //    ) ) //   ) )
       //|   // | |    //____      / /    //___ / / //   / / //    / / ((
      // |  //  | |   / ____      / /    / ___   / //   / / //    / /    \\
     //  | //   | |  //          / /    //    / / //   / / //    / /       ) )
    //   |//    | | //____/ /   / /    //    / / ((___/ / //____/ / ((___ / /
    */

    Vector() { //default constructor
        head = NULL;
        tail = NULL;
    }

    Vector(int A[], int size) //add each item from an array
    {
        head = NULL;
        tail = NULL;
        for (int i = 0; i < size; i++) {
            pushRear(A[i]);
        }
    }

    Vector(string Filename) //read until infile loads each value into the list
    {
        head = NULL;
        tail = NULL;
        ifstream infile;
        infile.open(Filename);
        int d = 0; //variable for data

        while (!infile.eof()) {
            infile >> d;
            pushRear(d);
        }

        infile.close();
    }

    Vector(const Vector& V1) {
        tail = head = NULL;
        Node* traverse = V1.head;
        while (traverse) {
            pushRear(traverse->data);
            traverse = traverse->next;
        }
    }

    int size() { //use this to see the size of the list
        int n = 0;
        Node* traverse = head;
        while (traverse != NULL) {
            n++;
            traverse = traverse->next;
        }
        return n;
    }

    void vPrint() {
        Node* traverse = head;
        while (traverse) {
            cout << traverse->data << " ";
            traverse = traverse->next;
        }
    }

    /*

        //   ) ) //   ) ) //   / /  //   ) )  // | |  /__  ___/ //   ) ) //   ) )  //   ) )
       //   / / //___/ / //____    //___/ /  //__| |    / /    //   / / //___/ /  ((
      //   / / / ____ / / ____    / ___ (   / ___  |   / /    //   / / / ___ (      \\
     //   / / //       //        //   | |  //    | |  / /    //   / / //   | |        ) )
    ((___/ / //       //____/ / //    | | //     | | / /    ((___/ / //    | | ((___ / /
    */

    void pushFront(int d) {
        Node* tempPtr = new Node(d);
        //pass in x into new node

        //adjust the head and tail pointers
        if (!head) {
            head = tail = tempPtr;
        }
        else {
            tempPtr->next = head;
            head = tempPtr;
        }
    }

    void pushFront(Vector V) {
        V.tail->next = head;
        head = V.head;
    }

    void pushRear(int d) {
        Node* tempPtr = new Node(d);

        if (!head) {
            head = tail = tempPtr;
        }
        else {
            tail->next = tempPtr;
            tail = tempPtr;
        }
    }

    void pushRear(Vector V) {
        tail->next = V.head;
        tail = V.tail;
    }

    // void pushAt(int d, int pos){

    // }

    // void inOrderPush(int d){

    // }

    int popFront() {
        int n = head->data;
        Node* temp = head;
        if (head == NULL) {
            cout << "nothing in the list";
            return -1;
        }
        else {
            head = head->next;
            delete temp;
            return n;
        }
    }

    int popRear() {
        int n = tail->data;
        Node* temp = tail;
        if (head == NULL) {
            cout << "nothing in the list";
            return -1;
        }
        else {
            tail = tail->prev;
            delete temp;
            tail->next = NULL;
            return n;
        }
    }

    int popAt(int loc) {
        int n;
        if (head == NULL) {
            cout << "nothing in the list";
            return -1;
        }
        else if (loc == 1) {
            return popFront();
        }
        else if (loc >= size()) {
            return popRear();
        }
        else {
            Node* traverse = head;
            for (int i = 0; i < loc - 1; i++) {
                traverse->next = traverse;
            }
            traverse->data = n;
            delete traverse;
            return n;
        }
    }

    int findItem(int d){
        Node* traverse = head;
        int n = 0;
        if (d == head->data) {
            return 1;
        }
        else if (d == tail->data) {
            return size();
        }
        else {
            if (traverse != NULL && traverse->data != d) {
                n++;
                traverse = traverse -> next;
            }
            else if (traverse == NULL) {
                cout << "Nothing there";
                return -1;
            }
            else {
                return n + 1;
            }
        }
    }

};

int main()
{
    // Vector V1("input.dat");
    // Vector V2("input2.dat");
    // Vector V3("input3.dat");

    cout << "Michelle Orru" << endl;
    cout << "September 15th, 2022" << endl;
    cout << "Fall 2143" << endl << endl;

    int d = 0;

    Vector V1;
    V1.pushFront(18);
    V1.pushFront(20);
    V1.pushFront(25);
    V1.pushRear(18);
    V1.pushRear(20);
    V1.pushRear(25);
    V1.vPrint();
    // [25, 20, 18, 18, 20, 25]
    cout << endl;

    int A[] = { 11,25,33,47,51 };
    Vector V2(A, 5);
    V2.vPrint();
    // [11, 25, 33, 47, 51]
    cout << endl;

    V2.pushFront(9);
    //v2.inOrderPush(27);
    V2.pushRear(63);
    V2.vPrint();
    // [9, 11, 25, 33, 47, 51, 63]
    cout << endl;

    V1.pushRear(V2);
    V1.vPrint();
    // [25, 20, 18, 18, 20, 25, 9, 11, 25, 33, 47, 51, 63]
    cout << endl;

    d = V1.popFront();
    d = V1.popFront();
    d = V1.popFront();
    V1.vPrint();
    // [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
    cout << endl << d << endl;
    // 18

    d = V1.popRear();
    d = V1.popRear();
    d = V1.popRear();
    V1.vPrint();
    // [18, 20, 25, 9, 11, 25, 27, 33]
    cout << endl << d << endl;
    // 47

    d = V2.popAt(3);
    V2.vPrint();
    // [9, 11, 25, 33, 47, 51, 63]
    cout << endl << d << endl;
    // 27

    d = V2.findItem(51);
    cout << d << endl;
    // 5

    d = V2.findItem(99);
    cout << d << endl;
    // -1

    Vector V3(V1);
    V3.vPrint();
    // [18, 20, 25, 9, 11, 25, 27, 33]

    V3.pushFront(V2);
    V3.vPrint();
    // [9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

    Vector V4("input.dat");
    V4.pushRear(V3);
    V4.vPrint();
    // [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

}
