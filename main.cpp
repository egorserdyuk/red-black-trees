#include <iostream>
#include <string>

using namespace std;

struct node {
    int data;
    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;
    string color = "NULL";
};

class RB_TREE {

    node *root;

public:
    RB_TREE() : root(nullptr) {}

    node *GetRoot() { return root; }

    void InsertNode(int stuff) {
        if (root == nullptr) {
            root = new node();
            root->data = stuff;
            root->parent = nullptr;
            root->color = "BLACK";
            cout << "Element inserted.\n";
        } else {
            auto linker = GetRoot();
            node *newnode = new node();
            newnode->data = stuff;

            while (linker != nullptr) {
                if (linker->data > stuff) {
                    if (linker->left == nullptr) {
                        linker->left = newnode;
                        newnode->color = "RED";
                        newnode->parent = linker;
                        cout << "Element inserted.\n";
                        break;
                    } else { linker = linker->left; }
                } else {
                    if (linker->right == nullptr) {
                        linker->right = newnode;
                        newnode->color = "RED";
                        newnode->parent = linker;
                        cout << "Element inserted.\n";
                        break;
                    } else { linker = linker->right; }
                }
            }
            RB_Insert_Fixup(newnode);
        }
    }


    void RB_Insert_Fixup(node *&z) {
        while (z->parent->color == "RED") {
            auto grandparent = z->parent->parent;
            auto uncle = GetRoot();
            if (z->parent == grandparent->left) {
                if (grandparent->right) { uncle = grandparent->right; }
                if (uncle->color == "RED") {
                    z->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    grandparent->color = "RED";
                    if (grandparent->data != root->data) { z = grandparent; }
                    else { break; }
                } else if (z == grandparent->left->right) {
                    LeftRotate(z->parent);
                } else {
                    z->parent->color = "BLACK";
                    grandparent->color = "RED";
                    RightRotate(grandparent);
                    if (grandparent->data != root->data) { z = grandparent; }
                    else { break; }
                }
            } else {
                if (grandparent->left) { uncle = grandparent->left; }
                if (uncle->color == "RED") {
                    z->parent->color = "BLACK";
                    uncle->color = "BLACK";
                    grandparent->color = "RED";
                    if (grandparent->data != root->data) { z = grandparent; }
                    else { break; }
                } else if (z == grandparent->right->left) {
                    RightRotate(z->parent);
                } else {
                    z->parent->color = "BLACK";
                    grandparent->color = "RED";
                    LeftRotate(grandparent);
                    if (grandparent->data != root->data) { z = grandparent; }
                    else { break; }
                }
            }
        }
        root->color = "BLACK";
    }

    node *maxValueNode(node *&x) {

        node *ptr = x;

        while (ptr->right != nullptr)
            ptr = ptr->right;

        return ptr;
    }

    node *minValueNode(node *&x) {

        node *ptr = x;

        while (ptr->left != nullptr)
            ptr = ptr->left;

        return ptr;
    }

    void RemoveNode(node *parent, node *curr, int stuff) {
        if (curr == nullptr) { return; }
        if (curr->data == stuff) {
            //CASE -- 1
            if (curr->left == nullptr && curr->right == nullptr) {
                if (parent->data == curr->data) { root = nullptr; }
                else if (parent->right == curr) {
                    RB_Delete_Fixup(curr);
                    parent->right = nullptr;
                } else {
                    RB_Delete_Fixup(curr);
                    parent->left = nullptr;
                }
            }
                //CASE -- 2
            else if (curr->left != nullptr && curr->right == nullptr) {
                int swap = curr->data;
                curr->data = curr->left->data;
                curr->left->data = swap;
                RemoveNode(curr, curr->right, stuff);
            } else if (curr->left == nullptr && curr->right != nullptr) {
                int swap = curr->data;
                curr->data = curr->right->data;
                curr->right->data = swap;
                RemoveNode(curr, curr->right, stuff);
            }
                //CASE -- 3
            else {
                bool flag = false;
                node *temp = curr->left;
                while (temp->right) {
                    flag = true;
                    parent = temp;
                    temp = temp->right;
                }
                if (!flag) { parent = curr; }
                int swap = curr->data;
                curr->data = temp->data;
                temp->data = swap;
                RemoveNode(parent, temp, swap);
            }
        }
    }

    void Remove(int stuff) {
        auto temp = root;
        auto parent = temp;
        bool flag = false;
        if (!temp) { RemoveNode(nullptr, nullptr, stuff); }

        while (temp) {
            if (stuff == temp->data) {
                flag = true;
                RemoveNode(parent, temp, stuff);
                break;
            } else if (stuff < temp->data) {
                parent = temp;
                temp = temp->left;
            } else {
                parent = temp;
                temp = temp->right;
            }
        }

        if (!flag) { cout << "\nElement doesn't exist in the table"; }
    }

    string getColor(node *&x) {
        if (x == nullptr)
            return "BLACK";

        return x->color;
    }

    void setColor(node *&x, string color) {
        if (x == nullptr)
            return;

        x->color = color;
    }

    void RB_Delete_Fixup(node *&z) {
        while (z->data != root->data && z->color == "BLACK") {
            auto sibling = GetRoot();
            if (z->parent->left == z) {
                if (z->parent->right) { sibling = z->parent->right; }
                if (sibling) {
                    //CASE -- 1
                    if (sibling->color == "RED") {
                        sibling->color = "BLACK";
                        z->parent->color = "RED";
                        LeftRotate(z->parent);
                        sibling = z->parent->right;
                    }
                    //CASE -- 2
                    if (sibling->left == nullptr && sibling->right == nullptr) {
                        sibling->color = "RED";
                        z = z->parent;
                    } else if (sibling->left->color == "BLACK" && sibling->right->color == "BLACK") {
                        sibling->color = "RED";
                        z = z->parent;
                    }
                        //CASE -- 3
                    else if (sibling->right->color == "BLACK") {
                        sibling->left->color = "BLACK";
                        sibling->color = "RED";
                        RightRotate(sibling);
                        sibling = z->parent->right;
                    } else {
                        sibling->color = z->parent->color;
                        z->parent->color = "BLACK";
                        if (sibling->right) { sibling->right->color = "BLACK"; }
                        LeftRotate(z->parent);
                        z = root;
                    }
                }
            } else {
                if (z->parent->right == z) {
                    if (z->parent->left) { sibling = z->parent->left; }
                    if (sibling) {
                        //CASE -- 1
                        if (sibling->color == "RED") {
                            sibling->color = "BLACK";
                            z->parent->color = "RED";
                            RightRotate(z->parent);
                            sibling = z->parent->left;
                        }
                        //CASE -- 2
                        if (sibling->left == nullptr && sibling->right == nullptr) {
                            sibling->color = "RED";
                            z = z->parent;
                        } else if (sibling->left->color == "BLACK" && sibling->right->color == "BLACK") {
                            sibling->color = "RED";
                            z = z->parent;
                        }
                            //CASE -- 3 
                        else if (sibling->left->color == "BLACK") {
                            sibling->right->color = "BLACK";
                            sibling->color = "RED";
                            RightRotate(sibling);
                            sibling = z->parent->left;
                        } else {
                            sibling->color = z->parent->color;
                            z->parent->color = "BLACK";
                            if (sibling->left) { sibling->left->color = "BLACK"; }
                            LeftRotate(z->parent);
                            z = root;
                        }
                    }
                }

            }
        }
        z->color = "BLACK";
    }

    node *TreeSearch(int stuff) {
        auto temp = GetRoot();
        if (temp == nullptr) { return nullptr; }

        while (temp) {
            if (stuff == temp->data) { return temp; }
            else if (stuff < temp->data) { temp = temp->left; }
            else { temp = temp->right; }
        }
        return nullptr;
    }

    void LeftRotate(node *&ptr) {
        node *right_child = ptr->right;
        ptr->right = right_child->left;

        if (ptr->right != nullptr)
            ptr->right->parent = ptr;

        right_child->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = right_child;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = right_child;
        else
            ptr->parent->right = right_child;

        right_child->left = ptr;
        ptr->parent = right_child;
    }

    void RightRotate(node *&ptr) {
        node *left_child = ptr->left;
        ptr->left = left_child->right;

        if (ptr->left != nullptr)
            ptr->left->parent = ptr;

        left_child->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = left_child;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = left_child;
        else
            ptr->parent->right = left_child;

        left_child->right = ptr;
        ptr->parent = left_child;
    }

    void PreorderTraversal(node *w, int l = 0) {
        int i;

        if (w != NULL) {
            PreorderTraversal((w->right), l + 1);
            for (i = 1; i <= l; i++) cout << "   ";
            cout << w->data << "<" << w->color << ">" << endl;
            PreorderTraversal((w->left), l + 1);
        }
    }

};

void menu() {
    cout << "\n__________________________________________";
    cout << "\n\n  --HEIGHT BALANCED BINARY SEARCH TREE--";
    cout << "\n          --(Red-Black-Tree)--";
    cout << "\n__________________________________________";
    cout << "\n\n1. Insert elements into the tree.";
    cout << "\n2. Search for an element.";
    cout << "\n3. PRE-ORDER Tree-Walk.";
    cout << "\n4. Remove an element from the tree.";
    cout << "\n5. Exit.";
    cout << "\n__________________________________________";
    cout << "\nYour Choice -- ";
}


int main() {
    RB_TREE demo;
    int info, input;
    menu();
    cin >> info;
    while (info != 6) {
        switch (info) {
            case 1:
                cout << "\nElement to be inserted -- ";
                cin >> input;
                demo.InsertNode(input);
                break;

            case 2:
                cout << "\nElement to be searched -- ";
                cin >> input;
                if (demo.TreeSearch(input)) { cout << "Element found.\n"; }
                else { cout << "Element not found.\n"; }
                break;

            case 3:
                cout << "Pre-Order Tree Walk \n";
                demo.PreorderTraversal(demo.GetRoot());
                cout << endl;
                break;

            case 4:
                cout << "\nElement to be deleted? -- ";
                cin >> input;
                demo.Remove(input);
                break;

            case 5:
                cout << "\nTerminating.... ";
                return 0;

            default:
                cout << "Wrong Choice.\n";
        }
        cout << "\nAnything Else?";
        cin >> info;
    }
}