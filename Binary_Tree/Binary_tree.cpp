#include <iostream>
#include <vector> //for storing nodes data, help user to see exist value
#include<queue> //for level order traversal


using namespace std;

struct Node // Genral binary tree structer
{
    int data;
    struct Node *left;
    struct Node *right;
};

// adding unique node in binary tree
bool find_and_add(Node *&head, int value, int data, char side)
{
    if (head == NULL)
    {
        return false;
    }
    if (head->data == value)
    {
        if (side == 'l') //adding data to left side
        {
            head->left = new Node();
            head->left->data = data;
            head->left->left = NULL;
            head->left->right = NULL;
        }
        if (side == 'r') //adding data to right side
        {
            head->right = new Node();
            head->right->data = data;
            head->right->left = NULL;
            head->right->right = NULL;
        }
        return true;
    }

    bool leftSubtree = find_and_add(head->left, value, data, side);
    bool rightSubtree = find_and_add(head->right, value, data, side);

    return leftSubtree || rightSubtree;
}

// adding root node and passing next data to be added in binary tree
void add(Node *&head, int data, char side, vector<int> &vec, int value)
{
    if (head == NULL && vec.size() == 0) // root node data add
    {
        head = new Node();
        head->data = data;
        head->left = NULL;
        head->right = NULL;
        cout << "Data is inserted.\n";
        vec.push_back(data);
        return;
    }

    // function for adding a data and check if it is unique or not
    if (find_and_add(head, value, data, side)) 
    {
        cout << "Data is inserted.\n";
        vec.push_back(data);
    }
    else
    {
        cout << "parent node is not found. Data not inserted.\n";
    }
}

//update node
bool update(Node *&head,int update_data,int data)
{
    if(head==NULL) return false;
    if(data==head->data)
    {
        head->data=update_data;
        return true;
    }

    bool left_result=update(head->left,update_data,data);
    bool right_result=update(head->right,update_data,data);

    return left_result || right_result;
}

// funtion for deleting a node

bool delete_node(Node *&root, int data) {
    if (root == NULL) {
        return false; // Base case: tree is empty or node not found
    }

    // Check if the root itself is the node to delete
    if (root->data == data) {
        // Case 1: Leaf node
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
            return true;
        }
        // Case 2: One child (right only)
        else if (root->left == NULL) {
            Node *temp = root;
            root = root->right;
            delete temp;
            return true;
        }
        // Case 2: One child (left only)
        else if (root->right == NULL) {
            Node *temp = root;
            root = root->left;
            delete temp;
            return true;
        }
        // Case 3: Two children
        else {
            Node *temp = root;
            root = root->right; // Replace with right child
            Node *leftmost = root;
            // Find the leftmost node in the right subtree
            while (leftmost->left != NULL) {
                leftmost = leftmost->left;
            }
            leftmost->left = temp->left; // Attach left subtree to leftmost node
            delete temp;
            return true;
        }
    }

    // Check left child
    if (root->left != NULL && root->left->data == data) {
        Node *temp = root->left;
        // Case 1: Leaf node
        if (temp->left == NULL && temp->right == NULL) {
            delete temp;
            root->left = NULL;
            return true;
        }
        // Case 2: One child (right only)
        else if (temp->left == NULL) {
            root->left = temp->right;
            delete temp;
            return true;
        }
        // Case 2: One child (left only)
        else if (temp->right == NULL) {
            root->left = temp->left;
            delete temp;
            return true;
        }
        // Case 3: Two children
        else {
            root->left = temp->right; // Replace with right child
            Node *leftmost = root->left;
            // Find the leftmost node in the right subtree
            while (leftmost->left != NULL) {
                leftmost = leftmost->left;
            }
            leftmost->left = temp->left; // Attach left subtree to leftmost node
            delete temp;
            return true;
        }
    }

    // Check right child
    if (root->right != NULL && root->right->data == data) {
        Node *temp = root->right;
        // Case 1: Leaf node
        if (temp->left == NULL && temp->right == NULL) {
            delete temp;
            root->right = NULL;
            return true;
        }
        // Case 2: One child (right only)
        else if (temp->left == NULL) {
            root->right = temp->right;
            delete temp;
            return true;
        }
        // Case 2: One child (left only)
        else if (temp->right == NULL) {
            root->right = temp->left;
            delete temp;
            return true;
        }
        // Case 3: Two children
        else {
            root->right = temp->right; // Replace with right child
            Node *leftmost = root->right;
            // Find the leftmost node in the right subtree
            while (leftmost->left != NULL) {
                leftmost = leftmost->left;
            }
            leftmost->left = temp->left; // Attach left subtree to leftmost node
            delete temp;
            return true;
        }
    }

    // Recursively search in subtrees
    bool leftDeleted = delete_node(root->left, data);
    bool rightDeleted = delete_node(root->right, data);
    return leftDeleted || rightDeleted;
}

bool check_node(Node *&head,int data)
{
    if(head==NULL) return false;

    if(head->data==data) return true;

    bool left_tree=check_node(head->left,data);
    bool right_tree=check_node(head->right,data);

    return left_tree || right_tree;
}

//function for in order traversal
void display_in_ordered_traversal(Node* head)
{
    if(head==NULL) return;

    display_in_ordered_traversal(head->left);
    cout<<head->data<<" ";
    display_in_ordered_traversal(head->right);
}

//function for pre order traversal
void display_pre_ordered_traversal(Node* head)
{
    if(head==NULL) return;

    cout<<head->data<<" ";
    display_pre_ordered_traversal(head->left);
    display_pre_ordered_traversal(head->right);
}

//function for post order traversal
void display_post_ordered_traversal(Node* head)
{
    if(head==NULL) return;

    display_post_ordered_traversal(head->left);
    display_post_ordered_traversal(head->right);
    cout<<head->data<<" ";
}

//function for level order traversal
void display_level_ordered_traversal(Node *head)
{
    if(head==NULL) return;
    queue<Node*> q;
    q.push(head);

    while(!q.empty())
    {
        Node *curr=q.front();
        q.pop();

        cout<<curr->data<<" ";
        if(curr->left!=NULL)
        {
            q.push(curr->left);
        }
        if(curr->right!=NULL)
        {
            q.push(curr->right);
        }
    }

}

//main function
int main()
{
    struct Node *head = NULL;
    vector<int> vec;
    while (1)
    {
        cout << "1. Add a node\n";
        cout << "2. Update a node\n";
        cout << "3. Delete a node\n";
        cout << "4. Check if node exist or not\n";
        cout << "5. Display a Binary Tree in \" In_ordered traversal \"\n";
        cout << "6. Display a Binary Tree in \" Pre_ordered traversal \"\n";
        cout << "7. Display a Binary Tree in \" Post_ordered traversal \"\n";
        cout << "8. Display a Binary Tree in \" Level_ordered traversal \"\n";
        cout << "9. Exit\n";
        int option;
        cout << "Choose Option : ";
        cin >> option;
        int data;
        bool flag;
        switch (option)
        {
        case 1: //insert data node
            int value;            
            cout << "Enter a data : ";
            cin >> data;
            flag = false;
            for (int i = 0; i < vec.size(); i++)
            {
                if (data == vec[i])
                {
                    cout << "Node is already in tree with this data. Duplicate data isn't allowed.\n";
                    flag = true;
                    break;
                }
            }
            if (flag == true)
                break;
            char side; // right or left
            if (vec.size() != 0) //no need for root data to check sides
            {
                cout << "Which node should be parent of this data? ";
                cin >> value;
                cout << "Choose which side data should be stored.. left as l or right as r : ";
                cin >> side;
            }
            add(head, data, side, vec, value);
            //display present nodes to user
            for (int i = 0; i < vec.size(); i++)
            {
                cout << vec[i] << "\t";
            }
            cout << endl;
            break;

        case 2:
            // update data node
            int update_data;
            cout<<"Select Data to be update : ";
            cin>>data;
            cout<<"Enter new data : ";
            cin>>update_data;            
            if(update(head,update_data,data))
            {
                cout<<"Data is updatetd.\n";
                for (int i = 0; i < vec.size(); i++) {
                    if(vec[i]==data)
                    {
                        vec[i]=update_data; // change data in vector also, which has been updated in BT
                        break;
                    }
                }
                //display present nodes to user
                for (int i = 0; i < vec.size(); i++) {
                    cout << vec[i] << "\t";
                }
                cout << endl;
            }
            else{
                cout<<"Data not found. Update operation failed.\n";
            }
            break;

        case 3: //delete node
            cout << "Enter data to be deleted : ";
            cin >> data;
            if (delete_node(head, data)) {
                cout << "Data is deleted.\n";
                // Remove the deleted data from vec
                for (auto it = vec.begin(); it != vec.end(); ++it) {
                    if (*it == data) {
                        vec.erase(it);
                        break;
                    }
                }
                //display present nodes to user
                for (int i = 0; i < vec.size(); i++) {
                    cout << vec[i] << "\t";
                }
                cout << endl;
            } else {
                cout << "Data not found.\n";
            }
            break;

        case 4: //check node
            cout<<"Enter a data to check : ";
            cin>>data;
            if(check_node(head,data))
            {
                cout<<"Data with this node is present.\n";
            }
            else{
                cout<<"Data with this node is not present.\n";
            }
        
        case 5: //in order traversal
            display_in_ordered_traversal(head);
            cout << "\n";
            break;

        case 6: //pre order traversal
            display_pre_ordered_traversal(head);
            cout << "\n";
            break;

        case 7: //post order traversal
            display_post_ordered_traversal(head);
            cout << "\n";
            break;

        case 8: //level order traversal
            display_level_ordered_traversal(head);
            cout << "\n";
            break;

        case 9:
            return 0; //exit program

        default:
            cout << "Please enter a valid option.\n";
            break;
        }
        cout<<"\n";
    }

    return 0;
}