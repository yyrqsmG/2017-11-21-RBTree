#include <iostream>
using namespace std;

template <typename K, typename V> class Map;
template <typename K, typename V>
class MapNode{
    friend class Map<K, V>;
    enum Color{Red, Black};
public:
    Color color;//2种颜色 红黑
    MapNode *parent;//父亲
    MapNode *left;//左孩子
    MapNode *right;//右孩子
    const K key;//下标数字
    V val;//存放字符串

    MapNode(Color _color=Red, MapNode* _parent=0, MapNode* _left=0,
             MapNode* _right=0, const K _key=K(), V _val=V()):
            color(_color), parent(_parent), left(_left), right(_right),
            key(_key), val(_val){}
};

template <typename K, typename V> 
class Map{
private:
    MapNode<K, V>* root;
public:
    Map(void):root(NULL){}

    V& operator [](const K& key)//重载[]
    {
        MapNode<K, V> *p = root;
        MapNode<K, V> *s = 0;
        while(p)
        {
            s= p;
            if(key < p->key)
                p = p->left;
            else if(key > p->key)
                p = p->right;
            else
                return p->val;
        }
        p = new MapNode<K, V>(MapNode<K, V>::Red, s, 0, 0, key, V());
        if(!s)
            root =  p;
        else if(key < s->key)
            s->left = p;
        else
            s->right = p;
        insert_fix_up(p);
        return p->val;
    }

    void insert_fix_up(MapNode<K,V> *p)//插入数据(颜色)
    {
        if(!(p->parent))//根的颜色为黑
            p->color=MapNode<K,V>::Black;  
        else if(p->parent->color==MapNode<K,V>::Black)  
            return;  
        else if(uncle(p)!=0 && uncle(p)->color == MapNode<K,V>::Red)
        {  
            p->parent->color = MapNode<K,V>::Black;  
            uncle(p)->color = MapNode<K,V>::Black;  
            grandparent(p)->color = MapNode<K,V>::Red;  
            insert_fix_up(grandparent(p));  
        }  
        else if(p==p->parent->right && p->parent==grandparent(p)->left)
        {  
            rotate_left(p->parent); //左旋 
            p=p->left;  
        }
        else if(p==p->parent->left&&p->parent==grandparent(p)->right)
        {  
            rotate_right(p->parent); //右旋 
            p=p->right;  
        }  
        else
        {  
            p->parent->color=MapNode<K,V>::Black;  
            grandparent(p)->color=MapNode<K,V>::Red;  
            if(p==p->parent->left&&p->parent==grandparent(p)->left)  
                rotate_right(grandparent(p));  
            else  
                rotate_left(grandparent(p));  
        } 
    }

    MapNode<K, V> *grandparent(MapNode<K, V> *p)//p的爷爷
    {
        return p->parent->parent;
    }
    MapNode<K, V> *uncle(MapNode<K, V> *p)//p的叔父
    {
        return p->parent==grandparent(p)->left?grandparent(p)->right:grandparent(p)->left;
    }
    
    void rotate_left(MapNode<K, V> *p)//左旋
    {
        MapNode<K,V> *s = p->right;
        p->right = p->right->left;  
        if(s->left) 
            s->parent = p;  
        s->parent = p->parent;  
        if(!p->parent)  
            root = s;  
        else if(p == p->parent->left)  
            p->parent->left = s;  
        else  
            p->parent->right = s;  
        s->left = p;  
        p->parent = s;
    }

    void rotate_right(MapNode<K, V> *p)//右旋
    {
        MapNode<K,V> *pl = p->left;  
        p->left = p->left->right;  
        if(pl->right) 
            pl->right->parent = p;  
        pl->parent = p->parent;  
        if(!p->parent)  
            root = pl;  
        else if(p==p->parent->right)  
            p->parent->right=pl;  
        else  
            p->parent->left=pl;  
        pl->right=p;  
        p->parent=pl;
    }

    void print(MapNode<K, V> *p)
    {
        if(!p)
            return;
        cout<<' '<<p->key<<' '<<'('<<p->color<<")\t"<<p->val<<endl;
        print(p->left);       
        print(p->right);
    }
    void show(void)
    {
        cout<<"下标"<<"颜色"<<' '<<"字符串"<<endl;
        print(root);
        //cout<<endl;
    }
};

int main(void)  
{  
    Map<int, string> m;  
    m[1] = "one";  
    m[2] = "two";  
    m[0] = "zero";  
    m[3] = "three";  
    m[4] = "four";  
    m[5] = "five";  
    m[6] = "six";  
    m[10] = "ten";  
    m.show();  
    return 0;  
}