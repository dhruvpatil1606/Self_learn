#include <iostream>
#include<vector> //for storing nodes data, help user to see existing value

using namespace std;

struct BST{
    int data;
    struct BST *left;
    struct BST *right;
};

void add_node(BST *&head, int data)
{

    if(head==NULL)
    {
        head=new BST();
        head->data=data;
        head->left=NULL;
        head->right=NULL;
        return;
    }

    if(head->data>data) add_node(head->left,data);
    else add_node(head->right,data);
       
}

void update_node(BST *&head,int value,int data)
{
    if(head==NULL)
    {
        return;
    }
    if(head->data==value)
    {
        head->data=data;
        return;
    }

    if(value>head->data) update_node(head->right,value,data);
    if(value<head->data) update_node(head->left,value,data);
}

void inOrderTraversal(BST *head)
{
    if(head==NULL)
    {        
        return;
    }

    inOrderTraversal(head->left);
    cout<<head->data<<" ";
    inOrderTraversal(head->right);
    
}

int main()
{
    struct BST *head=NULL; //NULL entry, first node will be root node

    vector<int> vec; //vector to store data of nodes for checking duplicate data

    while(1)
    {
        cout<<"1. Add a node\n";
        cout<<"2. Update a node\n";
        cout<<"3. Delete a node\n";
        cout<<"4. Check if node exist or not\n";
        cout<<"5. Display a Binary Tree in \" In_ordered traversal \"\n";
        cout<<"6. Display a Binary Tree in \" Pre_ordered traversal \"\n";
        cout<<"7. Display a Binary Tree in \" Post_ordered traversal \"\n";
        cout<<"8. Display a Binary Tree in \" Level_ordered traversal \"\n";
        cout<<"9. Exit\n";

        int option;
        cout<<"\nEnter your choice : ";
        cin>>option;

        int data; //data for actual node data 
        
        bool flag=false;

        switch(option)
        {
            case 1:            
                cout << "Enter data : ";
                cin >> data;

                for(int i=0; i<vec.size(); i++)
                {
                    if(vec[i]==data)
                    {
                        cout<<"This value already exist in BST.. Enter a different value.\n";
                        break;
                    }
                }
                add_node(head,data);
                vec.push_back(data);                    
                break;                   
            
            case 2:            
                int value;
                cout<<"Enter node value to update : ";
                cin>>value;

                flag=false;
                for(int i=0; i<vec.size(); i++)
                {
                    if(vec[i]==data)
                    {
                        flag=true;
                        break;
                    }
                }
                if(flag==false)
                {
                    cout<<" This value does not exist in tree. Therefor we can not update it.\n";
                    break;
                }
                cout<<"Enter new value : ";
                cin>>data;

                update_node(head,value,data);
                break;

            case 5: //in order traversal
                inOrderTraversal(head);
                cout<<"\n";
                break;

            case 9:                
                return 0;

            default:
                cout<<"Choose right option..\n";     
                break;       
        }
        cout<<"\n";
    }    

    return 0;
}