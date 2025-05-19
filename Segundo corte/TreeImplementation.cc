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

        //  Orden methods
        void in_order(Node *nodo){
            if (nodo == nullptr) return;
            in_order(nodo->getleft());
            cout << nodo->getdata() << " ";
            in_order(nodo->getright());
        }

        void pre_order(Node *nodo){
            if (nodo == nullptr ) return;
            cout << nodo->getdata() << " ";
            pre_order(nodo->getleft());
            pre_order(nodo->getright());
        }

        
        void post_order(Node *nodo){
            if (nodo == nullptr) return;
            post_order(nodo->getleft());
            post_order(nodo->getright());
            cout << nodo->getdata() << " ";
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
            
            void remove(T value){

                if(empty()){
                    cout << "The tree is empty!";
                    return;
                }
    
                if(!BST(root, value)){
                    cout << "The data is not in the tree";
                    return;
                }
                
                Node *f = nullptr;
                Node *current = root;
                
                while(current != nullptr && current->getdata() != value){
                    f = current;
                    if(value < current->getdata()){
                        current = current -> getleft();
                    } else current = current->getright();
                }

                if(current->getleft() == nullptr && current->getright() == nullptr){

                    if(f -> getleft() == current){
                        f->setleft(nullptr);
                    } else f->setright(nullptr);
                
                    delete current;
                    size--;

                } else if(current->getleft() != nullptr || current->getright() != nullptr){

                    if(current->getleft() != nullptr){
                        if(f->getleft() == current){
                            f->setleft(current->getleft());
                        } else f -> setright(current->getleft());
                    } else if(current->getright() != nullptr){
                        if(f->getleft() == current){
                            f->setleft(current->getright());
                        } else f->setright(current->getright());
                    }
                    delete current;
                    size--;

                } else {

                    Node *h = nullptr;
                    Node *pred = current->getleft();
                    while (pred->getright() != nullptr) {
                        h = pred;
                        pred = pred->getright();
                    }

                    if (h->getleft() == pred){
                        h->setleft(pred->getleft());
                    } else h->setright(pred->getleft());

                    pred->setleft(current->getleft());
                    pred->setright(current->getright());

                    if(f->getleft() == current){
                        f->setleft(pred);
                    } else f->setright(pred);

                    delete current;
                    size--;
                    
                }
                
            }
            
            void printTreeIO(){
                inorder(root);
                cout << endl;
            }

};

int main(){

    BinaryTree<int> tree;
    
    /*random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);

    for (int i = 0; i <= 15; i++) {
        tree.insert(distrib(gen));
    }*/

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
    tree.remove(81);
    cout << endl;
    tree.printTreeIO();
    tree.remove(70);
    cout << endl;
    tree.printTreeIO();
    tree.remove(23);
    cout << endl;
    tree.printTreeIO();
    cout << endl;

    return 0;
}

//Ready 