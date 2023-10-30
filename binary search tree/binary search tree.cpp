template<typename T>
struct tree_node{
    T data{};
    tree_node*right{},*left{};
    tree_node(T value=0)
    {
        this->data=value;
        this->left=this->right=nullptr;
    }
};
template<class T>
class binary_search_tree{
private:
    tree_node<T>*root{};
    int length{};
    void insert(tree_node<T>*temp,T value)
    {
        if(!temp)
        {
            return;
        }
        if(value==temp->data)return;
        else if(value<temp->data)
        {
            if(temp->left)
                insert(temp->left,value);
            else
                temp->left=new tree_node<T>{value};
        }
        else
        {
            if(temp->right)
                insert(temp->right,value);
            else
                temp->right=new tree_node<T>{value};
        }
    }
    void print(tree_node<T>*temp)
    {
        if(!temp)
            return;
        print(temp->left);
        cout<<temp->data<<" ";
        print(temp->right);
    }
    tree_node<T>*find(T value)
    {
        tree_node<T>*temp=root;
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
    tree_node<T>*find_parent(T value)
    {
        tree_node<T>*temp=root;
        tree_node<T>*prev=nullptr;
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
    void connect_parent_to_grand_child(tree_node<T>*parent,tree_node<T>*child)
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
    tree_node<T>*get_succeor_small_right(tree_node<T>*temp)
    {
        tree_node<T>*cur=temp;
        while(cur->left)cur=cur->left;
        return cur;
    }
public:
    binary_search_tree&copy(const binary_search_tree&co)=delete;
    binary_search_tree&operator=(const binary_search_tree&co)=delete;
    binary_search_tree():root(nullptr),length(0){}
    binary_search_tree(T value)
    {
        this->root=new tree_node<T>{value};
        length=1;
    }
    void insert(T value)
    {
        if(!root)
        {
            root=new tree_node(value);
            length=1;
            return;
        }
        insert(root,value);
        length++;
    }
    void print()
    {
        if(!root)
            return;
        print(root);
        cout<<line;
    }
    bool empty()
    {
        return root==nullptr;
    }
    void erase(T value)
    {
        tree_node<T>*to_del=find(value);
        if(!to_del||!length)
            return;
        if(!to_del->left&&!to_del->right)//has no children just erase
        {
            tree_node<T>*prev= find_parent(value);
            if(!prev)
            {
                delete to_del;
                to_del=nullptr;
                root=nullptr;
                length--;
                return;
            }
            length--;
            if(prev->left==to_del)
                prev->left=nullptr;
            else
                prev->right=nullptr;
            delete to_del;
            to_del=nullptr;
            return;
        }
        else if(!to_del->left||!to_del->right)//only one child connect parent to grand child
        {
            tree_node<T>*prev= find_parent(value);
            if(!prev)
            {
                if(to_del->left)
                    root=root->left,to_del->left=nullptr;
                else
                    root=root->right,to_del->right=nullptr;
                delete to_del;
                to_del=nullptr;
                length--;
                return;
            }
            length--;
            connect_parent_to_grand_child(prev,to_del);
            to_del->right=to_del->left=nullptr;
            delete to_del;
            to_del=nullptr;
            return;
        }
        else //the normal case the node has two children
        {
            tree_node<T>*temp=get_succeor_small_right(to_del->right);
            int toto=temp->data;
            erase(temp->data);
            to_del->data=toto;
        }
    }
    int size()
    {
        return length;
    }
};
