#include <iostream>
using namespace std;

template<typename T>
class BST{
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

                Node *getleft(){
                    return left;
                }

                Node *getright(){
                    return right;
                }

                T getdata(){
                    return data;
                }

                void setleft(Node *node){
                    left = node;
                }

                void setright(Node *nodo){
                    right = node;
                }

                void setdata(const T value){
                    data = value;
                }

        };

        Node *root;
        unsigned int size_;

        insert(Node *nodo, const T value){
            if(node == nullptr){
                Node newnodo = new Node(value);
                newnodo->setleft(nullptr);
                newnodo->setright(nullptr);
                size++;
                return newnodo;
            }

            if(value == nodo->getdata()){
                return node;
            } else if(value < nodo->getdata()){
                node->setleft(insert(nodo->getleft(), value));
            } else {
                node->setright(insert(nodo->getright(), value));
            }

            return node;
        }

        void inorder(Node *nodo){
            if(node == nullptr) return;
            inorder(nodo->getleft());
            cout << nodo->getdata() << " ";
            inorder(nodo->getright());
        }

        bool search(Node *node, const T value){
            if(node == nullptr){
                return false;
            }

            if(node->getdata == value){
                return true;
            } else if(value < node->getdata()){
                return search(node->getleft(), value);
            } else {
                return search(node->getright(), value);
            }

        } 

        public:

            BST(){
                root = nullptr;
                size_ = 0;
            }

            unsigned int size_(){
                return size_;
            }

            bool empty(){
                return size == 0;
            }

            void insert(const T value){
                root = insert(root, value);
            }

            void search(const T value){
                if(search(root, value)){
                    cout << "The data is found";
                } else cout << "The data isn't found";
            }

            void print(){
                inorder(root);
                cout << endl;
            }


};

//Faltaa 