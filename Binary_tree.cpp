#include <iostream>
#include <vector>

using namespace std;

struct  Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

bool find_and_add(Node *&head, int value, int data,char side)
{
    if(head==NULL)
    {
        return false;
    }
    if(head->data==value)
    {        
        if(side=='l')
        {
            head->left=new Node();
            head->left->data=data;
            head->left->left=NULL;
            head->left->right=NULL;
        }
        if(side=='r')
        {
            head->right=new Node();
            head->right->data=data;
            head->right->left=NULL;
            head->right->right=NULL;
        }        
        return true;
    }

    bool leftSubtree=find_and_add(head->left,value,data,side);
    bool rightSubtree=find_and_add(head->right,value,data,side);

    return leftSubtree || rightSubtree;
}

void add(Node *&head, int data, char side, vector<int> &vec, int value)
{    
    if(head==NULL && vec.size()==0) //root node data add
    {
        head=new Node();
        head->data=data;
        head->left=NULL;
        head->right=NULL;  
        cout<<"Data is inserted.\n"; 
        vec.push_back(data);  
        return;
    }

    if(find_and_add(head,value,data,side))
    {
        cout<<"Data is inserted.\n";
        vec.push_back(data);
    }
    else{
        cout<<"parent node is not found. Data not inserted.\n";
    }

}

int main()
{
    struct Node *head = NULL;
    vector<int> vec;
    while (1)
    {
        cout << "1. Add a node\n";
        // cout << "2. Display a Binary Tree in \" In_ordered traversal \"\n";
        // cout << "3. Display a Binary Tree in \" Pre_ordered traversal \"\n";
        // cout << "4. Display a Binary Tree in \" Post_ordered traversal \"\n";
        // cout << "5. Display a Binary Tree in \" Level_ordered traversal \"\n";
        cout << "6. Exit\n";
        int option;
        cout << "Choose Option : ";
        cin >> option;

        bool flag;
        switch (option)
        {
        case 1:
            int value;
            int data;
            cout << "Enter a data : ";
            cin >> data;
            flag=false;
            for(int i=0; i<vec.size(); i++)
            {
                if(data==vec[i]){
                    cout<<"Node is already in tree with this data. Duplicate data isn't allowed.\n";
                    flag=true;
                    break;
                }
            }
            if(flag==true) break;
            char side; //right or left
            if(vec.size()!=0){
                cout<<"Which node should be parent of this data? ";
                cin>>value;
                cout<<"Choose which side data should be stored.. left as l or right as r : ";
                cin>>side;
            }
            add(head, data, side, vec, value);
            for(int i=0; i<vec.size(); i++)
            {
                cout<<vec[i]<<"\t";
            }
            cout<<endl;
            break;

        case 2:
            //display_in_ordered_traversal(head);
            cout << "\n";
            break;

        case 3:
            //display_pre_ordered_traversal(head);
            cout << "\n";
            break;

        case 4:
            //display_post_ordered_traversal(head);
            cout << "\n";
            break;

        case 5:
            //display_level_ordered_traversal(head);
            cout << "\n";
            break;

        case 6:
            return 0;

        default:
            cout << "Please enter a valid option.\n";
            break;
        }
    }

    return 0;

}