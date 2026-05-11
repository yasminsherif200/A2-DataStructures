#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Book
{
    int id;
    string title;
    string author;
};

class BSTNode
{
public:
    Book book;
    BSTNode *left, *right;
    BSTNode(Book b)
    {
        book = b;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
public:
    BSTNode *root;
    BST()
    {
        root = nullptr;
    }

        // Insert a Book - Complexity: O(h)
        BSTNode* insert(BSTNode* root, Book b) {
            BSTNode* new_book = new BSTNode(b);
            if(root == nullptr) return new_book;
            BSTNode* temp = root;
            while(temp != nullptr){ // Traverse 
                if(new_book->book.id < temp->book.id && temp->left != nullptr){
                    temp = temp->left;
                }else if(new_book->book.id > temp->book.id && temp->right != nullptr){
                    temp = temp->right;
                }else break;
            } // Insert at the correct position
            if(new_book->book.id < temp->book.id){ 
                temp->left = new_book;
            }else if(new_book->book.id > temp->book.id){
                temp->right = new_book;
            }else{
                cout << "Book already Exists\n";
                delete new_book;
            }
            return root;
        }

    // To find Successor
    BSTNode *findMin(BSTNode *node)
    {
        while (node && node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // Delete a Book - Complexity: O(h)
    BSTNode *deleteBook(BSTNode *root, int id)
    {
        if (root == nullptr)
            return root;
        if (root->book.id > id)
            root->left = deleteBook(root->left, id);
        else if (root->book.id < id)
            root->right = deleteBook(root->right, id);
        else
        {
            // Zero childern
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }
            // Right child only
            else if (root->left == nullptr)
            {
                BSTNode *temp = root->right;
                delete root;
                return temp;
            }
            // Left child only
            else if (root->right == nullptr)
            {
                BSTNode *temp = root->left;
                delete root;
                return temp;
            }
            // Two childern
            else
            {
                BSTNode *temp_successor = findMin(root->right);
                root->book = temp_successor->book;
                root->right = deleteBook(root->right, temp_successor->book.id);
            }
        }
        return root;
    }

    // Search a Book by id - Complexity: O(h)
    bool search(BSTNode *root, int id)
    {
        int steps = 0;
        if (root == nullptr){
            cout << "Tree is empty\n";
            return false;
        }
        while (root != nullptr)
        {
            steps++;
            if (root->book.id == id){

                cout << "Book found in " << steps << " steps.\n";
                return true;
            }
            else if (root->book.id > id)
                root = root->left;
            else
                root = root->right;
        }
        cout << "Not found after " << steps << " steps\n";
        return false;
    }

        // DFS Inorder Traversal (LVR) - Complexity: O(n)
        void inOrder(BSTNode* root){
            if(root == nullptr) return;
            inOrder(root->left);
            cout << "Book ID: " << root->book.id << "\n";
            cout << "Book Title:  " << root->book.title << "\n";
            cout << "Book Author:  " << root->book.author << "\n";
            inOrder(root->right);
        }
        int getHeight(BSTNode* root) { 
            if(root == nullptr) return 0;
         return 1 + max(getHeight(root->left), getHeight(root->right)); 
        }
};
//===part 2 ===
// left (books with smaller id) | node(book) | rigth (books with larger id)
class AvlNode
{
public:
    Book book;
    AvlNode *left, *right;
    int height;
    AvlNode(Book b)
    {
        book = b;
        left = nullptr;
        right = nullptr;
        height = 1; // height of each node from root till the node
    }
};
class AVLTree
{
private:
    AvlNode *root; // top node of the tree.

    int getHeight(AvlNode *node)
    { // returns height of a node
        if (node == nullptr)
            return 0;        // If the node is nullptr height is 0.
        return node->height; // Otherwise return stored height
    }

    int getBalance(AvlNode *node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right); // Balance Factor = height of left subtree - height of right subtree
        // bf>1 right rotation , bf<-1 left rotation
    }

    void updateHeight(AvlNode *node)
    { // recalculate height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    AvlNode *rotateRight(AvlNode *y)
    {
        AvlNode *x = y->left;
        AvlNode *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x; // x is the new root
    }

    AvlNode *rotateLeft(AvlNode *x)
    {
        AvlNode *y = x->right;
        AvlNode *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y; // y is the new root
    }

    AvlNode *balance(AvlNode *node)
    {
        updateHeight(node);
        int bf = getBalance(node); // Calculate balance factor

        // Left-Left
        if (bf > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        // Right-Right
        if (bf < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        // Left-Right
        // First rotate the left child to the left, then rotate the node to the right
        if (bf > 1 && getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right-Left
        // First rotate the right child to the right, then rotate the node to the left
        if (bf < -1 && getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    AvlNode *insert(AvlNode *node, Book book)
    {
        if (node == nullptr) // if empty then create new node
            return new AvlNode(book);

        // Go left if new book's ID is smaller
        if (book.id < node->book.id)
            node->left = insert(node->left, book);

        // Go right if new book's ID is larger
        else if (book.id > node->book.id)
            node->right = insert(node->right, book);

        else
        {
            cout << "Book with ID " << book.id << " already exists.\n"; // duplicate
            return node;
        }
        return balance(node);
    }

    AvlNode *minNode(AvlNode *node)
    { // return left most node (smallest ID)
        while (node->left != nullptr)
            node = node->left; // keep going left
        return node;
    }

    AvlNode *deleteNode(AvlNode *node, int id)
    {
        if (node == nullptr)
        {
            cout << "Book with ID " << id << " not found.\n";
            return nullptr;
        }
        // searching for the node
        if (id < node->book.id)
            node->left = deleteNode(node->left, id);
        else if (id > node->book.id)
            node->right = deleteNode(node->right, id);

        else
        {
            // found the node
            // case 1 & 2: zero or one child
            if (node->left == nullptr || node->right == nullptr)
            {
                AvlNode *child = (node->left != nullptr) ? node->left : node->right;
                if (child == nullptr)
                {
                    delete node;
                    return nullptr;
                }
                else
                {
                    AvlNode *temp = node;
                    node = child;
                    delete temp;
                }
            }
            else
            {
                // case 3: Two children
                AvlNode *successor = minNode(node->right);
                node->book = successor->book;
                node->right = deleteNode(node->right, successor->book.id);
            }
        }

        if(node == nullptr)
            return node;

        return balance(node);
    }

    AvlNode *search(AvlNode *node, int id, int steps = 0)
    {
        if (node == nullptr){
            cout << "Not found after " << steps << " steps\n";
            return nullptr;
        }

        steps++;

        if (id == node->book.id){
            cout << "Book found in " << steps << " steps.\n";
            return node;
        }
        else if (id < node->book.id){
            return search(node->left, id, steps);
        }
        else{
            return search(node->right, id, steps);
        }
    }

    void inOrder(AvlNode *node)
    {
        if (node == nullptr)
            return;
        inOrder(node->left);
        cout << "[ID: " << node->book.id
             << "] " << node->book.title
             << " by " << node->book.author << "\n";
        inOrder(node->right);
    }

    void freeTree(AvlNode *node)
    {
        if (node == nullptr)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { freeTree(root); }

    void insert(Book book)
    {
        root = insert(root, book);
    }

    void deleteBook(int id)
    {
        AvlNode *found = search(root, id);
        if (!found)
        {
            cout << "Book with ID " << id << " not found.\n";
            return;
        }
        cout << "Deleting: [ID: " << found->book.id
             << "] \"" << found->book.title << "\"...\n";
        root = deleteNode(root, id);
        cout << "Done. New tree height: " << getHeight(root) << "\n";
    }

    void search(int id)
    {
        AvlNode *result = search(root, id);
        if (result)
            cout << "Found: [ID: " << result->book.id
                 << "] \"" << result->book.title
                 << "\" by " << result->book.author << "\n";

        else
            cout << "Book with ID " << id << " not found.\n";
    }

    void displayAll()
    {
        cout << "Books in order\n";
        inOrder(root);
    }

    int getHeight()
    {
        return getHeight(root);
    }

    void printRange(AvlNode *root, int low, int high)
    {
        if (root == nullptr)
            return;
        if (root->book.id > low)
        {
            printRange(root->left, low, high);
        }

        if (root->book.id >= low && root->book.id <= high)
        {
            cout << "[ID: " << root->book.id
                 << "] " << root->book.title
                 << " by " << root->book.author << "\n";
        }
        if (root->book.id < high)
        {
            printRange(root->right, low, high);
        }
    }
    void displayRange(int low, int high)
    {
        cout << "Books with IDs in range [" << low << ", " << high << "]\n";
        printRange(root, low, high);
    }
    void ClosestIDFunction(AvlNode *node, int target, int &closest)
    {
        if (node == nullptr)
            return;
        if (abs(node->book.id - target) < abs(closest - target))
            closest = node->book.id;
        if (target < node->book.id)
            ClosestIDFunction(node->left, target, closest);
        else
            ClosestIDFunction(node->right, target, closest);
    }
    void findClosestID(int target)
    {
        if (root == nullptr)
        {
            cout << "No books in the library.\n";
            return;
        }
        int closest = root->book.id;
        ClosestIDFunction(root, target, closest);
        cout << "Closest ID to " << target << " is: " << closest << "\n";
    }
};

int main()
{
    cout << "=== Random Insertions ===\n";
    BST bstRandom;
    AVLTree avlRandom;
            vector<Book> randomBooks = { {150, "Book1", "Author1"}, 
            {320, "Book2", "Author2"}, 
            {45, "Book3", "Author3"}, 
            {210, "Book4", "Author4"}, 
            {99, "Book5", "Author5"}, 
            {410, "Book6", "Author6"}, 
            {275, "Book7", "Author7"}, 
            {60, "Book8", "Author8"},
            {500, "Book9", "Author9"}, 
            {15, "Book10", "Author10"}, 
            {180, "Book11", "Author11"}, 
            {350, "Book12", "Author12"}, 
            {75, "Book13", "Author13"}, 
            {290, "Book14", "Author14"}, 
            {33, "Book15", "Author15"}, 
            {430, "Book16", "Author16"}, 
            {120, "Book17", "Author17"}, 
            {250, "Book18", "Author18"}, 
            {390, "Book19", "Author19"}, 
            {10, "Book20", "Author20"} 
        };
    for (Book &b : randomBooks)
    {
        bstRandom.root = bstRandom.insert(bstRandom.root, b);
        avlRandom.insert(b);
    }

    cout << "\nBST height:\n";
    cout << "Height: " << bstRandom.getHeight(bstRandom.root) << "\n";
    cout << "\nAVL height:\n";
    cout << "Height: " << avlRandom.getHeight() << "\n";
     cout << "BST Search:\n";   
    bstRandom.search(bstRandom.root, 99); // existing
    bstRandom.search(bstRandom.root, 999); // non  
        cout << "\nAVL Search:\n";
    avlRandom.search(99); // existing
    avlRandom.search(999); // non

    //---------------------------------------------------------------------
    cout << "\n=== Sorted Insertions ===\n";
    BST bstSorted;
    AVLTree avlSorted;
    vector<Book> sortedBooks = { {10, "Book1", "Author1"}, 
            {20, "Book2", "Author2"}, 
            {30, "Book3", "Author3"}, 
            {40, "Book4", "Author4"}, 
            {50, "Book5", "Author5"}, 
            {60, "Book6", "Author6"}, 
            {70, "Book7", "Author7"}, 
            {80, "Book8", "Author8"},
            {90, "Book9", "Author9"}, 
            {100, "Book10", "Author10"}, 
            {110, "Book11", "Author11"}, 
            {120, "Book12", "Author12"}, 
            {130, "Book13", "Author13"}, 
            {140, "Book14", "Author14"}, 
            {150, "Book15", "Author15"}, 
            {160, "Book16", "Author16"}, 
            {170, "Book17", "Author17"}, 
            {180, "Book18", "Author18"}, 
            {190, "Book19", "Author19"}, 
            {200, "Book20", "Author20"} 
        };
    for (Book &b : sortedBooks)
    {
        bstSorted.root = bstSorted.insert(bstSorted.root, b);
        avlSorted.insert(b);
    }

    cout << "\nBST height:\n";
    cout << "Height: " << bstSorted.getHeight(bstSorted.root) << "\n";
    cout << "\nAVL height:\n";
    cout << "Height: " << avlSorted.getHeight() << "\n";
     cout << "\nBST Search:\n";
    bstSorted.search(bstSorted.root, 100); // existing
    bstSorted.search(bstSorted.root, 999); // non 
        cout << "\nAVL Search:\n";  
    avlSorted.search(100); // existing
    avlSorted.search(999); // non

    return 0;
}