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
class tree{
    tree_node<T>*root{};
    int length=0;
    tree_node<T>*construct(deque<T>&preorder,deque<T>&inorder,int start,int end)
    {
        if(start>end)return nullptr;
        tree_node<T>*temp=new tree_node<T>{preorder.front()};
        preorder.pop_front();
        if(start==end)return temp;
        for(int i=start;i<=end;i++)
        {
            if(temp->data==inorder[i])
            {
                temp->left=construct(preorder,inorder,start,i-1);
                temp->right=construct(preorder,inorder,i+1,end);
                break;
            }
        }
        return temp;
    }
    void preorder_traversal(tree_node<T>*temp)
    {
        if(!temp)return;
        cout<<temp->data<<" ";
        inorder_traversal(temp->left);
        inorder_traversal(temp->right);
    }
    void inorder_traversal(tree_node<T>*temp)
    {
        if(!temp)return;
        inorder_traversal(temp->left);
        cout<<temp->data<<" ";
        inorder_traversal(temp->right);
    }
    void postorder_traversal(tree_node<T>*temp)
    {
        if(!temp)return;
        inorder_traversal(temp->left);
        inorder_traversal(temp->right);
        cout<<temp->data<<" ";
    }
    int height(tree_node<T>*temp)
    {
        int left=0;
        int right=0;
        if(temp->left)
        {
            left+=height(temp->left);
        }
        if(temp->right)
        {
            right+=height(temp->right);
        }
        return 1+max(left,right);
    }
public:
    tree(deque<T>&pre,deque<T>&inorder)
    {
        root= construct(pre,inorder,0,pre.size()-1);
        length=(int)pre.size();
    }
    void insert(vector<T>values,string path)
    {
        tree_node<T>*cur=root;
        if(!cur)
        {
            root=new tree_node<T>{values[0]};
            cur=root;
        }
        for(int i=1;i<path.size();i++)
        {
            if(!cur)
            {
                root=new tree_node<T>{values[i]};
                cur=root;
                continue;
            }
            if(path[i]=='L')
            {
                if(!cur->left)
                    cur->left=new tree_node{values[i]},length++;
                cur=cur->left;
            }
            else
            {
                if(path[i]=='R')
                {
                    if(!cur->right)
                        cur->right=new tree_node{values[i]},length++;
                    cur=cur->right;
                }
            }
        }
    }
    void inorder_traversal()
    {
        inorder_traversal(root);
    }
    void preorder_traversal()
    {
        preorder_traversal(root);
    }
    void postorder_traversal()
    {
        postorder_traversal(root);
    }
    bool empty()
    {
        return length==0;
    }
    int height()
    {
        if(length==0)
            return 0;
        return height(root);
    }
};
