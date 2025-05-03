#include <iostream> 
#include <random>
#include <ctime>
#include <cmath>      
#include <algorithm> 

template<typename KeyType, typename ValueType> 
class Treap {
private:
    class TreapNode {
    public:
        KeyType key;
        ValueType value;
        double priority;
        TreapNode* left;
        TreapNode* right;

        TreapNode(KeyType k, ValueType v, double p)
            : key(k), value(v), priority(p), left(nullptr), right(nullptr) {}
    };

    TreapNode* root;
    std::mt19937 rng;
    std::uniform_real_distribution<double> priority_dist;

    // Priority generator
    double generatePriority() {
        return priority_dist(rng);
    }

    // Rotations
    TreapNode* rotateRight(TreapNode* y) {
        TreapNode* x = y->left;
        TreapNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        return x;
    }

    TreapNode* rotateLeft(TreapNode* x) {
        TreapNode* y = x->right;
        TreapNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        return y;
    }

    // Insertion
    TreapNode* insert(TreapNode* node, KeyType key, ValueType value) {
        if (!node)
            return new TreapNode(key, value, generatePriority());

        if (key < node->key) {
            node->left = insert(node->left, key, value);
            if (node->left->priority > node->priority)
                node = rotateRight(node);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
            if (node->right->priority > node->priority)
                node = rotateLeft(node);
        } else {
            node->value = value;
        }

        return node;
    }

    // Deletion
    TreapNode* deleteNode(TreapNode* node, KeyType key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            if (!node->left) {
                TreapNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreapNode* temp = node->left;
                delete node;
                return temp;
            } else {
                if (node->left->priority > node->right->priority) {
                    node = rotateRight(node);
                    node->right = deleteNode(node->right, key);
                } else {
                    node = rotateLeft(node);
                    node->left = deleteNode(node->left, key);
                }
            }
        }

        return node;
    }

    // Basic search
    TreapNode* search(TreapNode* node, KeyType key) {
        if (!node) return nullptr;
        if (key == node->key) return node;
        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    // Inorder traversal
    void inorder(TreapNode* node) {
        if (node) {
            inorder(node->left);
            std::cout << "Key: " << node->key
                      << " | Value: " << node->value
                      << " | Priority: " << node->priority << "\n";
            inorder(node->right);
        }
    }

    // Height of the treap
    int computeHeight(TreapNode* node) {
        if (!node) return 0;
        return 1 + std::max(computeHeight(node->left), computeHeight(node->right));
    }

    // Count nodes
    int countNodes(TreapNode* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    // Smart search helper
    TreapNode* smartSearchUtil(TreapNode* node, KeyType key, ValueType& result, bool& found) {
        if (!node) return nullptr;

        if (key == node->key) {
            result = node->value;
            found = true;

            double newPriority = generatePriority();
            if (newPriority > node->priority) {
                node->priority = newPriority;
                node = bubbleUp(node, key);
            }

            return node;
        }

        if (key < node->key) {
            node->left = smartSearchUtil(node->left, key, result, found);
            if (node->left && node->left->priority > node->priority)
                node = rotateRight(node);
        } else {
            node->right = smartSearchUtil(node->right, key, result, found);
            if (node->right && node->right->priority > node->priority)
                node = rotateLeft(node);
        }

        return node;
    }

    // Bubble up helper
    TreapNode* bubbleUp(TreapNode* node, KeyType key) {
        if (!node) return nullptr;

        if (node->left && node->left->key == key && node->left->priority > node->priority)
            return rotateRight(node);
        if (node->right && node->right->key == key && node->right->priority > node->priority)
            return rotateLeft(node);

        if (key < node->key)
            node->left = bubbleUp(node->left, key);
        else if (key > node->key)
            node->right = bubbleUp(node->right, key);

        return node;
    }

public:
    Treap()
        : root(nullptr),
          rng(static_cast<unsigned int>(std::time(nullptr))),
          priority_dist(0.0, 1.0) {}

    void insert(KeyType key, ValueType value) {
        root = insert(root, key, value);
    }

    void deleteKey(KeyType key) {
        root = deleteNode(root, key);
    }

    bool search(KeyType key, ValueType& result) {
        TreapNode* node = search(root, key);
        if (node) {
            result = node->value;
            return true;
        }
        return false;
    }

    bool smart_search(KeyType key, ValueType& result) {
        bool found = false;
        root = smartSearchUtil(root, key, result, found);
        return found;
    }

    void printInorder() {
        std::cout << "\nInorder traversal of Treap:\n";
        inorder(root);
    }

    int height() {
        return computeHeight(root);
    }

    void stats() {
        int count = countNodes(root);
        int h = computeHeight(root);
        double optimalHeight = count > 0 ? std::log(count) : 0.0;

        std::cout << "\n--- Treap Stats ---\n";
        std::cout << "Size: " << count << "\n";
        std::cout << "Height: " << h << "\n";
        std::cout << "Optimal Height (log(n)): " << optimalHeight << "\n";
    }
};


int main() {
    Treap<int, std::string> treap;

    treap.insert(30, "thirty");
    treap.insert(20, "twenty");
    treap.insert(40, "forty");
    treap.insert(10, "ten");

    treap.printInorder();
    treap.stats();

    std::string result;
    if (treap.smart_search(20, result)) {
        std::cout << "\n[Smart Search] Found key 20 with value: " << result << "\n";
    }

    treap.printInorder();
    treap.stats();

    return 0;
}
