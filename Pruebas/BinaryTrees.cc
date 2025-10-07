#include <iostream> 
#include <random>

using namespace std;

template <typename Type>
class BinaryTree{
    private:
        class Node{
            public:
                Node *left
                Node *right;
                Type data;
            
                Node() {
                    left = nullptr;
                    right = nullptr;
                    data = Type;
                }
        };

        Node *root;

        Node* insert(Node* root, Type val) {
            if (root == nullptr) { 
                Node *newNode = new Node(); 
                newNode->data = val;
                newNode -> right = newNode -> left = nullptr;
                return newNode;
            }
    
            if (val == root->data) {
                return root;
            } 
            else if (val > root->data) {
                root->right = insert(root->right, val); 
            } 
            else {
                root->left = insert(root->left, val); 
            }
    
            return root;
        }

        void inorder(Node* node) {
            if (node == nullptr) return;  
            inorder(node->left);         
            cout << node->data << " ";    
            inorder(node->right); 
        }
        

    public:
    
        BinaryTree(){
            root = nullptr;
        }

        void insert(Type val){
            root = insert(root, val);
        }

        void printTreeIO(){
            inorder(root);
            cout << endl;
        }
        
};

int main() {

    BinaryTree<int> tree;
    
    /* 
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);

    for (int i = 0; i <= 15; i++) {
        tree.insert(distrib(gen));
    }
    */

    tree.insert(55);
    tree.insert(47);
    tree.insert(48);
    tree.insert(23);
    tree.insert(15);
    tree.insert(34);
    tree.insert(33);
    tree.insert(16);
    tree.insert(10);
    tree.insert(22);
    tree.insert(43);
    tree.insert(0);
    tree.insert(24);
    tree.insert(51);
    tree.insert(66);
    tree.insert(65);
    tree.insert(71);
    tree.insert(70);
    tree.insert(86);
    tree.insert(69);
    tree.insert(84);
    tree.insert(97);
    tree.insert(81);
    tree.insert(85);
    tree.insert(88);
    tree.insert(87);
    tree.insert(96);

    tree.printTreeIO();

    return 0;
}
