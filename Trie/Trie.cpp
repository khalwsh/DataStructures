class trie{
private:
    static const int siz=26;
    map<int,trie*>arr;
    bool leaf{false};
void get_all(vector<string>&v,string s="")
    {
        if(leaf)
            v.emplace_back(s);
        for(int i=0;i<26;i++)
        {
            if(arr[i])
            {
                arr[i]->get_all(v,s+(char)('a'+i));
            }
        }
    }
    void insert(string &s,int index)
    {
        if(index==s.size()) {
            leaf = true;
            return;
        }
        if(!arr[s[index]-'a'])
            arr[s[index]-'a']=new trie();
        arr[s[index]-'a']->insert(s,index+1);
    }
    bool is_word(string &s,int index)
    {
        if(index==s.size()) {
            return leaf;
        }
        if(!arr[s[index]-'a'])
            return false;
        return arr[s[index]-'a']->is_word(s,index+1);
    }
    bool is_prefix(string &s,int index)
    {
        if(index==s.size())
            return true;
        if(!arr[s[index]-'a'])
            return false;
        return arr[s[index]-'a']->is_prefix(s,index+1);
    }
    string first_word_prefix(const string&s,int index)
    {
        if(leaf)
            return s.substr(0,index);
        if(!arr[s[index]-'a'])
            return s;
        return arr[s[index]-'a']->first_word_prefix(s,index+1);
    }
public:
    trie()
    {
        leaf=false;
    }
    void insert( string s)
    {
        //reverse(s.begin(),s.end());
        insert(s,0);
    }
    bool is_word(string s)
    {
        return is_word(s,0);
    }
    bool is_prefix(string s)
    {
        return is_prefix(s,0);
    }
    string first_word_prefix(const string&s)
    {
        return first_word_prefix(s,0);
    }
    bool is_suffix(string &s)
    {
        //after reverse the input
        reverse(s.begin(),s.end());
        return is_prefix(s);
    }
    void insert(vector<string>&s)
    {
       string sk;
       for(auto &val:s)
           sk+=val;
       insert(sk);
    }
    bool is_sub_path(const vector<string>&s)
    {
        string sk;
        for(auto &val:s)
            sk+=val;
        return is_prefix(sk);
    }
 void get_all_content(vector<string>&v)
    {
        get_all(v);
    }
    void auto_complete(const string &prefix,vector<string>&v,int index=0)
    {
        if(index==prefix.size())
        {
            this->get_all(v,prefix);
        }
        if(!arr[prefix[index]-'a'])
            return;
        arr[prefix[index]-'a']->auto_complete(prefix,v,index+1);
    }
    bool word_exist(const string &s,int index=0)
    {
        if(index==s.size())
        {
            return leaf;
        }
        if(!arr[s[index]-'a'])
            return false;
        return arr[s[index]-'a']->word_exist(s,index+1);
    }
    bool change_one_letter_at_most(string &s)
    {
        for(int i=0;i<s.size();i++)
        {
            for(char j='a';j<='z';j++)
            {
                char temp=s[i];
                s[i]=j;
                if(word_exist(s,0))
                    return true;
                s[i]=temp;
            }
        }
        return false;
    }

};
