template<typename T>
struct node{
   T data{};
   node<T>*left{},*right{};
   int height{};
   node()
   {
       this->data={};
       this->left=this->right=nullptr;
       height=0;
   }
   node(T data)
   {
       this->data=data;
       this->left=this->right=nullptr;
       height=0;
   }
};
template<class T>
class AVL{
    node<T>*root{};
    node<T>*find(T value)
    {
        node<T>*temp=root;
        while(temp)
        {
            if(temp->data==value)
                break;
            else if(temp->data>value)
                temp=temp->left;
            else
                temp=temp->right;
        }
        return temp;
    }
    node<T>*find_parent(T value)
    {
        node<T>*temp=root;
        node<T>*prev=nullptr;
        while(temp)
        {
            if(temp->data==value)
                break;
            else if(temp->data>value)
                prev=temp,temp=temp->left;
            else
                prev=temp,temp=temp->right;
        }
        return prev;
    }
    void connect_parent_to_grand_child(node<T>*parent,node<T>*child)
    {
        if(child->left)
        {
            if(parent->left==child)
                parent->left=child->left;
            else
                parent->right=child->left;
        }
        else
        {
            if(parent->left==child)
                parent->left=child->right;
            else
                parent->right=child->right;
        }
        child->left=child->right=nullptr;
    }
    node<T>*get_succeor_small_right( node<T>*temp)
    {
        node<T>*cur=temp;
        while(cur->left)cur=cur->left;
        return cur;
    }
    int cal_height(node<T>*temp)
    {
        //if node is null so it's height is -1
        //else return the height of the node
        if(temp)return temp->height;
        return -1;
    }
    void update_height(node<T>*temp)
    {
        //the new height of a node after insert or deletion is the 1+max_height of it's children
        temp->height=1+max(cal_height(temp->left), cal_height(temp->right));
    }
    int balance_factor(node<T>*temp)
    {
        //it must be |x|<=1 to hold the property of self balanced binary tree
        //if it is 1 so the left subtree is more depth than right by one and verse if -1
        //if zero this mean it's height of it's right subtree equal it's left subtree
        return cal_height(temp->left)- cal_height(temp->right);
    }
    node<T>*balance(node<T>*temp)
    {
        if(balance_factor(temp)==-2)//it's the case of right right or right left
        {
            if(balance_factor(temp->right)==1)//case of right left and this to convert it to case of right right
                temp->right=right_rotation(temp->right);
            temp=left_rotation(temp);//normal case right right
        }
        else if(balance_factor(temp)==2)//it's the case of left left or left right
        {
            if(balance_factor(temp->left)==-1)//case of left right and this to convert it to case of left left
                temp->left=left_rotation(temp->left);
            temp=right_rotation(temp);//it's the case of left left
        }
        return temp;//return the new root
    }
    node<T>*left_rotation(node<T>*temp)
    {
        //         before
        //    node1
        //  node2
        //node3
        //          after
        //     node2
        // node3   node1
        node<T>*P=temp->right;
        temp->right=P->left;
        P->left=temp;
        update_height(P), update_height(temp);
        return P;
    }
    node<T>*right_rotation(node<T>*temp)
    {
        //         before
        //    node1
        //        node2
        //           node3
        //          after
        //     node2
        // node1   node3
        node<T>*P=temp->left;
        temp->left=P->right;
        P->right=temp;
        update_height(P);
        update_height(temp);
        return P;
    }
    node<T>* insert(node<T>*temp,T value)
    {
        //we do normal insert but we add to that after every call of fuction we return the balance of the node
        //to hold the self balanced property
        if(value>temp->data)
        {
            if(temp->right)
                temp->right=insert(temp->right,value);//we return to the temp the balance after the insertion is done
            else
                temp->right=new node<T>{value};
        }
        else if(value<temp->data)
        {
            if(temp->left)
                temp->left=insert(temp->left,value);
            else
                temp->left=new node<T>{value};
        }
        update_height(temp);//the height change cause an extra node been added
        return balance(temp);//return the balanced subtree
    }
    void inorder(node<T>*temp)
    {
        if(!temp)return;
        inorder(temp->left);
        cout<<temp->data<<" ";
        inorder(temp->right);
    }
    void preorder(node<T>*temp)
    {
        if(!temp)return;
        cout<<temp->data<<" ";
        preorder(temp->left);
        preorder(temp->right);
    }
    node<T>*erase(node<T>*temp,T target)
    {
        if(temp&&temp->data>target)
            temp->left=erase(temp->left,target);
        else if(temp&&temp->data<target)
            temp->right= erase(temp->right,target);
        else if(temp)
        {
            //found the target
            node<T>*t=temp;
            if(!temp->left&&!temp->right)
                temp=nullptr;
            else if(!temp->right)
                temp=temp->left;
            else if(!temp->left)
                temp=temp->right;
            else
            {
                node<T>*mn= get_succeor_small_right(temp->right);
                temp->data=mn->data;
                temp->right= erase(temp->right,temp->data);
                t=nullptr;
            }
            if(t)
                delete t;
        }
        if(temp)
            update_height(temp),temp= balance(temp);
        return temp;
    }
    int min_nodes_per_height(vector<int>&heights,int height)
    {
        if(height==0)
            return 1;
        if(height==1)
            return 2;
        if(heights[height]!=-1)return heights[height];
        return heights[height]=1+ min_nodes_per_height(heights,height-1)+ min_nodes_per_height(heights,height-2);
    }
public:
    AVL&operator=(const node<T>*&equal)=delete;//delete the assignment operator
    AVL(const node<T>*&copy)=delete;//delete copy constructor
    AVL()
    {
        //empty_constructor
        this->root=nullptr;
    }
    AVL(T data)
    {
        //parametrized constructor
        this->root=new node<T>();
        this->root->data=data;
    }
    void insert(T value)
    {
        if(root== nullptr)
            root=new node<T>(value);
        else
            root=insert(root,value);
    }
    void print()
    {
        inorder(root);
    }
    void delete_value(T value)
    {
        if(!root||!find(value))return ;
        root=erase(root,value);
    }
    bool search(T value)
    {
        node<T>*temp=root;
        while(temp)
        {
            if(temp->data==value)
                return true;
            else if(temp->data>value)
                temp=temp->left;
            else
                temp=temp->right;
        }
        return false;
    }
    T lower_bound(T value)
    {
        if(!root)
            return -1;
        node<T>*temp=root;
        node<T>*res=nullptr;
        while(temp)
        {
            if(temp->data<value)
                temp=temp->right;
            else
                res=temp,temp=temp->left;
        }
        if(res==nullptr)return -1;
        return res->data;
    }
    T upper_bound(T value)
    {
        if(!root)
            return -1;
        node<T>*temp=root;
        node<T>*res=nullptr;
        while(temp)
        {
            if(temp->data<=value)
                temp=temp->right;
            else
                res=temp,temp=temp->left;
        }
        if(res==nullptr)return -1;
        return res->data;
    }
    int min_nodes(int height)
    {
        vector<int>heights(1ll<<height,-1);
        return min_nodes_per_height(heights,height);
    }
};
