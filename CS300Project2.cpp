/* CS300 Module 8 submission
* Code to sort and print out a list of the courses 
* in the Computer Science program in alphanumeric order
*/

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    inOrder(root);
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


            case '2':
                cout << "Here is a sample schedule:" << endl;
                bst->InOrder();
                cout << endl;
                break;

            
