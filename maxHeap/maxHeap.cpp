template<class T>
class max_heap{
    T*arr{};
    int size{0};
    int cap{0};
    void extend_cap()
    {
        cap*=2;
        cap+=1;
        T *cur=new T[cap];
        for(int i=0;i<size;i++)
            cur[i]=arr[i];
        swap(cur,arr);
        delete []cur;
    }
    void hepify_up(int index)
    {
        int par=parent(index);
        if(par==-1||arr[par]>=arr[index])
            return;
        swap(arr[par],arr[index]);
        hepify_up(par);
    }
    int left_child(int pos)
    {
        return (2*pos+1>=size)?-1:2*pos+1;
    }
    int right_child(int pos)
    {
        return (2*pos+2>=size)?-1:2*pos+2;
    }
    int parent(int pos)
    {
        return (pos==0)?-1:(pos-1)/2;
    }
    void hepify_down(int index)
    {
        int child_pos= left_child(index);
        int r= right_child(index);
        if(child_pos==-1)
            return;
        if(r!=-1&&arr[r]>arr[child_pos])
            child_pos= r;
        if(arr[index]<arr[child_pos])
            swap(arr[index],arr[child_pos]), hepify_down(child_pos);
    }
public:
    max_heap()
    {
        this->arr=nullptr;
        this->size=0;
    }
    void push(T value)
    {
        if(size==cap)
            extend_cap();
        arr[size++]=value;
        hepify_up(size-1);
    }
    void pop()
    {
        if(size==0)
            return;
        swap(arr[0],arr[size-1]);
        size--;
        hepify_down(0);
    }
    bool empty()
    {
        return size==0;
    }
    T top()
    {
        return arr[0];
    }
};
