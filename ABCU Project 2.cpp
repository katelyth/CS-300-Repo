// ABCU Project 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

#include "CSVParser.h"


//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
};

// define a structure to hold class information
struct Course {
    string courseId; // unique identifier
    string courseName;
    string prerequisite;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course acourse) :
        Node() {
        course = acourse;
    }
};

class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
};


/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // Fixed (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    // if root is not equal null
    if (root != nullptr) {
        // delete the left node
        delete(root->left);
        // delete the right node
        delete(root->right);
        // delete the root
        delete (root);
        //set root to nullptr
        root = nullptr;
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // Fixed (2): In order root
    // call inOrder fuction and pass root
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // Fixed (3): Post order root
    // call postOrder function and pass root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // Fixed (4): Pre order root
    // call preOrder and pass root
    preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
    // Fixed (5) Implement inserting a bid into the tree
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(course);
    }
    // else
    else {
        // add Node root and bid
        this->addNode(root, course);
    }
}

Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    // if the node = null
    if (node == nullptr) {
        // return it
        return node;
    }
    //else if, compare the bidID to the root and returns a value < 0 
    else if (courseId.compare(node->course.courseId) < 0) {
        // remove the left node
        node->left = removeNode(node->left, courseId);
    }
    // else if, compare the bidId to the root and return a value > 0
    else if (courseId.compare(node->course.courseId) > 0) {
        // remove the right node
        node->right = removeNode(node->right, courseId);
    }
    else {
        // if the match point is found
        if (node->left == nullptr && node->right == nullptr) {
            // delete the node
            delete node;
        }
        // else if the left node is not null
        else if (node->left != nullptr && node->right == nullptr) {
            // set a temp node to equal node
            Node* temp = node;
            // set the node to equal the left node
            node = node->left;
            // delete teh temp node
            delete temp;
            // set temp to null
            temp = nullptr;
        }
        // else if the right node is not null
        else if (node->right != nullptr && node->left == nullptr) {
            // set a temp node to equal the node
            Node* temp = node;
            // set the node to equal the right node
            node = node->right;
            // delete the temp node
            delete temp;
            // set temp to null
            temp = nullptr;
        }
        else {
            // Find the minimum of the right subtree node
            Node* temp = node->right;
            //while the left temp node is null
            while (temp->left != nullptr) {
                // temp is equal to the left temp node
                temp = temp->left;
            }
            // set the node to equal the temp node
            node->course = temp->course;
            // remove the right node
            node->right = removeNode(node->right, temp->course.courseId);
        }
    }
    // return the node
    return node;
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string courseId) {
    // Fixed (6) Implement removing a bid from the tree
    // remove node root bidID
    this->removeNode(root, courseId);
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseId) {
    // Fixed (7) Implement searching the tree for a bid
    // set current node equal to root
    Node* cur = root;

    // keep looping downwards until bottom reached or matching bidId found
    while (cur != nullptr) {
        // if match found, return current bid
        if (cur->course.courseId.compare(courseId) == 0) {
            return cur->course;
        }
        // if bid is smaller than current node then traverse left
        else if (courseId.compare(cur->course.courseId) < 0) {
            cur = cur->left;
        }
        // else larger so traverse right
        else {
            cur = cur->right;
        }
    }

    Course course;
    return course;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // Fixed (8) Implement inserting a bid into the tree
    // if node is larger then add to left
    if (node != nullptr && node->course.courseId.compare(course.courseId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
            return;
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    // if no right node
    else if (node != nullptr && node->course.courseId.compare(course.courseId) < 0) {
        if (node->right == nullptr) {
            // this node becomes left
            node->right = new Node(course);
            return;
        }
        // else recurse down the right node
        else {
            this->addNode(node->right, course);
        }
    }


}
void BinarySearchTree::inOrder(Node* node) {
    // Fixed (9): In order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        inOrder(node->left);
        //output bidID, title, amount, fund
        cout << node->course.courseId << ": " << node->course.courseName << " | " << node->course.prerequisite << endl;
        //InOder right
        inOrder(node->right);
    }

}
void BinarySearchTree::postOrder(Node* node) {
    // Fixed (10): Post order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output bidID, title, amount, fund
        cout << node->course.courseId << ": " << node->course.courseName << " | " << node->course.prerequisite << endl;
    }

}

void BinarySearchTree::preOrder(Node* node) {
    // Fixed (11): Pre order root
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output bidID, title, amount, fund
        cout << node->course.courseId << ": " << node->course.courseName << " | " << node->course.prerequisite << endl;
        //preOrder left
        preOrder(node->left);
        //preOrder right
        preOrder(node->right);
    }
}

void seeCourses(Course course) {
    cout << course.courseId << ": " << course.courseName << " | " << course.prerequisite << endl;
    return;
}


void LoadData(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Course course;
            course.courseId = file[i][1];
            course.courseName = file[i][0];
            course.prerequisite = file[i][8];

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}


string SeeCourses() {
    string courses;
    return courses;
}

//string FindCourse(string courseId) {
//    cout << course.courseId << ": " << course.courseName << " | " << course.prerequisite << " | " << endl;
//}


void printMenu() {
    int userInput = 0;
    string courseId = "";

    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;
    while (userInput != 9) {
    cout << "Welcome to the course planner!" << endl;
    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cin >> userInput;
    /*cin >> csvPath;*/
    string csvPath = "C:/Users/Elyse/source/repos/ABCU Project 2/SNHUCourses.csv";

        switch (userInput) {
            case 1:
                LoadData(csvPath, bst);
                break;
            case 2:
                bst->InOrder();
                break;
            case 3:
                cout << "enter course ID you would like to find" << endl;
                cin >> courseId;
                course = bst->Search(courseId);

                if (!course.courseId.empty()) {
                    seeCourses(course);
                }
                else {
                    cout << "Bid Id " << courseId << " not found." << endl;
                }
                break;
            case 9:
                break;
        }
    }

}

int main()
{
    

    printMenu();
}

