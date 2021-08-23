//============================================================================
// Name        : CS300Project2.cpp
// Author      : Salah Bedoui
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Course Planner
//============================================================================

#include <iostream>
#include <time.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept> 
#include <conio.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold course information
class Course {
private:
    string courseNumber = "";
    string courseName = "";
    vector<string> coursePrereq;
public:
    void setCourseNumber(string inputCourseNumber) {
        courseNumber = inputCourseNumber;
    }

    void setCourseName(string inputCourseName) {
        courseName = inputCourseName;
    }

    void setCoursePrerequisites(vector<string> inputCoursePrereq) {
        coursePrereq = inputCoursePrereq;
    }

    string getCourseNumber() {
        return courseNumber;
    }

    string getCourseName() {
        return courseName;
    }

    vector<string> getCoursePrerequisites() {
        return coursePrereq;
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    //default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    //initialize with a course
    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};


//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseNumber);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equal to null ptr
      // root is equal to new node course
    // else
      // add Node root and course
    
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNumber) {
    // set current node equal to root
    // keep looping downwards until bottom reached or matching courseNumber found
        // if match found, return current course
        // if course is smaller than current node then traverse left
        // else larger so traverse right
    Course course;

    Node* current = root;
    while (current != nullptr) {
        if (current->course.getCourseNumber().compare(courseNumber) == 0) {
            return current->course;
        }
        if (courseNumber.compare(current->course.getCourseNumber()) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
        // if no left node
            // this node becomes left
        // else recurse down the left node
    // else
        // if no right node
            // this node becomes right
        //else
            // recurse down the left node
    if (node->course.getCourseNumber().compare(course.getCourseNumber()) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}


void BinarySearchTree::inOrder(Node* node) {
      //if node is not equal to null ptr
      //InOrder not left
      //output course information
      //InOder right
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.getCourseNumber() << ", " << node->course.getCourseName() << endl;
        inOrder(node->right);
    }
}


/**
 * Load a text file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {

    ifstream inFS;     //input file stream
    Course course;
    vector<string> prereq{ "" };
    

    cout << "opening file " << csvPath << endl << endl;

    inFS.open(csvPath);
    if (!inFS.is_open()) {
        cout << "Could not open file " << csvPath << endl;
    }

    string line;
    while (!inFS.eof()) {
        while (getline(inFS, line)) {
            istringstream ss(line);
            string token;

            while (getline(ss, token, ',')) {
                course.setCourseNumber(token);
                while (getline(ss, token, ',')) {
                    course.setCourseName(token);
                    while (getline(ss, token, ',')) {
                        prereq.push_back(token);
                        course.setCoursePrerequisites(prereq);
                    }
                }
            }
            bst->Insert(course);
            prereq.clear();
        }

    }
}


/**
 * The one and only main() method
 */
int main() {

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst = nullptr;
    Course course;

    cout << "Welcome to the course planner." << endl;
    string csvPath = "ABCU_Advising_Program_Input.txt";
    char choice = '0';

    //while loop to display menu until user enters 4
    while (choice != '9') {
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: " << endl << endl;
        //exception handling constructs to handle any user input that is not 1, 2 or 3
        try {
            /* _getch() take user input without echo for a better user experience.
            Once the user enter a value they get directly to their menu choice without pressing 'enter'.
            _getch() has also the advantage over 'cin' to read non alphanumeric keys*/
            choice = _getch();
            //switch statement to handle the different menu options

            switch (choice) {

            case '1':
                bst = new BinarySearchTree();

                // method call to load the courses into the data structure
                loadCourses(csvPath, bst);
                break;

            case '2':
                cout << "Here is a sample schedule:" << endl;
                bst->InOrder();
                cout << endl;
                break;

            case '3':
            {
                string searchCourse = "";
                cout << "What course do you want to know about? ";
                cin >> searchCourse;
                transform(searchCourse.begin(), searchCourse.end(), searchCourse.begin(), ::toupper);
                course = bst->Search(searchCourse);
                if (!course.getCourseNumber().empty()) {
                    cout << course.getCourseNumber() << ", " << course.getCourseName() << endl;
                    cout << "Prerequisites: ";
                    for (int i = 0; i < course.getCoursePrerequisites().size(); ++i) {
                        cout << course.getCoursePrerequisites().at(i) << " ";
                    }
                }

                else {
                    cout << searchCourse << " not found";
                }

                cout << endl;

                break;
            }

            case '9':
                cout << "Thank you for using the course planner. Good bye." << endl;
                break;

            default:
                throw runtime_error("\n Invalid entry. Please enter 1, 2, 3 or 9 \n");
                break;
            }
        }

        //catch clause will execute if the user enter non(1,2,3,9) values
        catch (runtime_error& excpt) {
            // Prints the error message passed by throw statement
            cout << excpt.what() << endl;
        }
    }

    return 0;
}
