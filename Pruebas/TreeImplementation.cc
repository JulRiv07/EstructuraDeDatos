#include <iostream> 
#include <random>

using namespace std;

template <typename T>
class BinaryTree{
    private:
        class Node{
            private:
                Node *left;
                Node *right;
                T data;
            public:
                Node(){
                    left = nullptr;
                    right = nullptr;
                    data = T();
                } 

                Node(const T value){
                    left = nullptr;
                    right = nullptr;
                    data = value;
                }

                T getdata() const {
                    return data;
                }

                Node *getleft(){
                    return left;
                }

                Node *getright(){
                    return right;
                }

                void setleft(Node *nodo){
                    left = nodo;
                }

                void setright(Node *nodo){
                    right = nodo;
                }

                void setdata(const T value){
                    data = value;
                }
        };

        Node *root;
        unsigned int size;

        Node *insert(Node *root, T data){
            if(root == nullptr){
                Node *newnodo = new Node(data);
                newnodo->setleft(nullptr);
                newnodo->setright(nullptr);
                size++;
                return newnodo;
            }

            if(data == root->getdata()){
                return root;
            } else if (data < root->getdata()){
                root->setleft(insert(root->getleft(), data));
            }else if (data > root->getdata()){
                root->setright(insert(root->getright(), data));
            }    
            
            return root;

        }

        void inorder(Node* node) {
            if (node == nullptr) return;  
            inorder(node->getleft());         
            cout << node->getdata() << " ";    
            inorder(node->getright()); 
        }

        bool BST(Node *root, T const value) {
            if (root == nullptr) {
                return false;
            }
        
            if (value == root->getdata()) {
                return true;
            } else if (value < root->getdata()) {
                return BST(root->getleft(), value);
            } else {
                return BST(root->getright(), value); 
            }
        }

        void remove(Node *root, T value){

            if(BST(root, value)){
                cout << "The data is not in the tree";
            }
            
            

        }

        public:
            
            BinaryTree(){
                root = nullptr;
                size = 0;
            }

            bool empty(){
                return size == 0;
            }

            unsigned int size_(){
                return size;
            }

            void insert(const T data){
                root = insert(root, data);
            }

            void search(const T value){
                if(BST(root, value)){
                    cout << "The data is in the tree!";
                } else cout << "The data is not in the tree!";
            }

            void printTreeIO(){
                inorder(root);
                cout << endl;
            }
};

int main(){

    BinaryTree<int> tree;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);

    for (int i = 0; i <= 15; i++) {
        tree.insert(distrib(gen));
    }

    cout << endl;
    tree.printTreeIO();

    return 0;
}