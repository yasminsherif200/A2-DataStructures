#include <bits/stdc++.h>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
};

class BSTNode {
    public:
        Book book;
        BSTNode *left, *right;
        BSTNode(Book b) {
            book = b;
            left = nullptr;
            right = nullptr;
        }
};

class BST {
    public:
        BSTNode* root;
        BST() {
            root = nullptr;
        }

        // Insert a Book - Complexity: O(h)
        BSTNode* insert(BSTNode* root, Book b) {
            BSTNode* new_book = new BSTNode(b);
            if(root == nullptr) return new_book;
            BSTNode* temp = root;
            while(temp != nullptr){
                if(new_book->book.id < temp->book.id && temp->left != nullptr){
                    temp = temp->left;
                }else if(new_book->book.id > temp->book.id && temp->right != nullptr){
                    temp = temp->right;
                }else break;
            }
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
        BSTNode* findMin(BSTNode* node){
            while(node && node->left != nullptr){
                node = node->left;
            }
            return node;
        }

        // Delete a Book - Complexity: O(h)
        BSTNode* deleteBook(BSTNode* root, int id){
            if(root == nullptr) return root;
            if(root->book.id > id) root->left = deleteBook(root->left, id);
            else if(root->book.id < id) root->right = deleteBook(root->right, id);
            else{
                // Zero childern
                if(root->left == nullptr && root->right == nullptr){
                    delete root;
                    return nullptr;
                }
                // Right child only 
                else if(root->left == nullptr){
                    BSTNode* temp = root->right;
                    delete root;
                    return temp;
                }
                // Left child only
                else if(root->right == nullptr){
                    BSTNode* temp = root->left;
                    delete root;
                    return temp;
                }
                // Two childern
                else{
                    BSTNode* temp_successor = findMin(root->right);
                    root->book = temp_successor->book;
                    root->right = deleteBook(root->right, temp_successor->book.id);
                }
            }
            return root;
        }

        // Search a Book by id - Complexity: O(h)
        bool search(BSTNode* root, int id) {
            if(root == nullptr) return false;
            while(root != nullptr){
                if(root->book.id == id) return true;
                else if(root->book.id > id) root= root->left;
                else root = root->right;
            }
            return false;
        }

        // DFS Inorder Traversal (LVR) - Complexity: O(n)
        void inOrder(BSTNode* root){
            if(root == nullptr) cout << "No Books Found\n";
            inOrder(root->left);
            cout << "Book ID: " << root->book.id << "\n";
            cout << "Book Title:  " << root->book.title << "\n";
            cout << "Book Author:  " << root->book.author << "\n";
            inOrder(root->right);
        }
};

int main(){

    return 0;
}