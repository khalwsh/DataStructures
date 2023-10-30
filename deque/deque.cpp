template<typename T>
struct node{
    T data{};
    node*next{};
    node*prev{};
    node(T value=-1)
    {
        this->data=value;
        this->next=this->prev=nullptr;
    }
};
template<class T>
class doubly_linked_list{
    node<T>*head{},*tail{};
    int length{};
public:
    doubly_linked_list()
    {
        this->head=this->tail=nullptr;
        length=0;
    }
    node<T>*first()
    {
        return head;
    }
    void insert(T value) {
        if (length == 0) {
            length++;
            head = new node<T>{value};
            head->next = head->prev = nullptr;
            tail=head;
            return;
        } else if (length == 1)
        {
            length++;
            tail=nullptr;
            tail=new node<T>{value};
            tail->prev=head;
            head->next=tail;
            return;
        }
        length++;
        tail->next=new node<T>{value};
        tail->next->prev=tail;
        tail=tail->next;
    }
    void pop_back()
    {
        if(length==0)return;
        if(length==1){
            delete head;
            length--;
            return;
        }
        length--;
        node<T>*cur=tail;
        tail=tail->prev;
        cur->prev=nullptr;
        delete cur;
    }
    void pop_front()
    {
        if(length<=1)
        {
            pop_back();
            return;
        }
        length--;
        node<T>*cur=head;
        head=head->next;
        cur->next=nullptr;
        delete cur;
    }
    bool empty()
    {
        return length==0;
    }
    bool size()
    {
        return length==0;
    }
    T front()
    {
        if(length==0)throw runtime_error("fuck you");
        return head->data;
    }
    T back()
    {
        if(length==0)throw runtime_error("fuck you");
        return tail->data;
    }
    void insert_front(T value)
    {
        if (length == 0) {
            length++;
            head = new node<T>{value};
            head->next = head->prev = nullptr;
            return;
        } else if (length == 1)
        {
            tail=new node<T>{};
            tail=head;
            node<T>*cur=new node<T>{value};
            head=cur;
            head->next=tail;
            tail->prev=head;
            length++;
        }
        length++;
        head->prev=new node<T>{value};
        head->prev->next=head;
        head=head->prev;
    }
};
template<typename T>
class Deque{
public:
    doubly_linked_list<T>dll;
    void insert_back(T value)
    {
        dll.insert(value);
    }
    void insert_front(T value)
    {
        dll.insert_front(value);
    }
    void pop()
    {
        dll.pop_front();
    }
    int size()
    {
        return dll.size();
    }
    bool empty()
    {
        return dll.empty();
    }
    T top()
    {
        return dll.front();
    }
};
