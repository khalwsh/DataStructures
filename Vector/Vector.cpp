template<class T>
class Vector{
    T*arr{};
    int length{};
    int cap{0};
    void extend_cap()
    {
        cap*=2;
        cap+=1;
        T *cur=new T[cap];
        for(int i=0;i<length;i++)
            cur[i]=arr[i];
        swap(cur,arr);
        delete []cur;
    }
public:
    int size()
    {
        return length;
    }
    Vector():arr(nullptr),length(0),cap(0){}
    Vector(int size)
    {
        length=size;
        arr=new T[size];
        cap=length;
    }
    T*begin()
    {
        return arr;
    }
    T*end()
    {
        return arr+length;
    }
    ~Vector()
    {
        delete []arr;
    }
    void push_back(T value)
    {
        if(arr==nullptr)
            arr=new T[1];
        if(length==cap)
        {
            extend_cap();
        }
        arr[length++]=value;
    }
    void pop_back()
    {
        if(length==0)
            return;
        length--;
    }
    T&operator[](int index)
    {
        if(index>=length||index<0)
        {
            throw invalid_argument("out of limit");
        }
        return arr[index];
    }
};
