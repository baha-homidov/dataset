// Homidov Mirzobakhtiyor
// khamidov.mirzo@gmail.com
// map.h
#include <iostream>



namespace ds{

template <typename Key, typename Val>
class map
{
public:
    class Node
    {
    public:
        Node *lchild;
        std::pair<Key, Val> data;
        Node *rchild;
        int height;
    };

    Node *root = nullptr;
    map() { root = nullptr; }
    map(const map &source)
    {
        deep_copy(source);
    }
    ~map()
    {
        delete_nodes(root);
        root = nullptr;
    }
    map &operator=(const map &source);
    void deep_copy(const map &source);
    bool empty() { return (root == nullptr); }

    // Search
    Val &operator[](const Key &key); // gives a reference to an elements value
                                     // if element with a given key not found, inserts a new element and return reference
    const Node *search(const Key &key) const;

    // Deletion
    void erase(const Key &key) { erase(root, key); }
    void clear()
    {
        this->delete_nodes(root);
        root = nullptr;
    }

    // Insertion
    void insert(const std::pair<Key, Val> &elem); // insert for external use

    // Traversal
    void inorder() { inorder(root); }

private:
    // Helper functions for insertion and deletion
    void delete_nodes(Node *p);
    int node_height(Node *p);
    int balance_factor(Node *p);
    Node *LL_rotation(Node *p);
    Node *RR_rotation(Node *p);
    Node *LR_rotation(Node *p);
    Node *RL_rotation(Node *p);
    Node *InPre(Node *p);
    Node *InSucc(Node *p);

    // deletion
    Node *erase(Node *p, const Key &key); // internal use;

    // Traverlal
    void inorder(Node *p);
    Node *get_root() { return root; }

    // Insertion
    Node *r_insert(Node *p, const std::pair<Key, Val> &elem); // recursive insert for internal use
};

//--------------------------------------------------------------------------------

template <class Key, class Val>
map<Key, Val> &map<Key, Val>::operator=(const map<Key, Val> &source)
{
    if (this != &source)
    {
        deep_copy(source);
    }
    return this;
}

//--------------------------------------------------------------------------------

template <class Key, class Val>
void map<Key, Val>::deep_copy(const map<Key, Val> &source)
{

    delete_nodes(root);
    root = nullptr;

    if (source.root)
    {
        inorder(source.root->lchild);
        this->insert({source.root->data.first, source.root->data.second});
        inorder(source.root->rchild);
    }
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
Val &map<Key, Val>::operator[](const Key &key)
{
    Node *ptr = root;
    const Val val{};
    while (ptr != nullptr) // look for the key in the map
    {                      // and return a reference if the element is found
        if (key == ptr->data.first)
            return ptr->data.second;
        else if (key < ptr->data.first)
            ptr = ptr->lchild;
        else if (key > ptr->data.first)
            ptr = ptr->rchild;
    }

    this->insert({key, val}); // if the key is not found
                              // insert a new element with a given key

    return (*this)[key]; // return the reference to the newly inserted element
}

//--------------------------------------------------------------------------------

template <class Key, class Val>
const typename map<Key, Val>::Node *map<Key, Val>::search(const Key &key) const
{
    Node *ptr = root;
    while (ptr != nullptr) // look for the key in the map
    {                      // and return a reference if the element is found
        if (key == ptr->data.first)
            return ptr;
        else if (key < ptr->data.first)
            ptr = ptr->lchild;
        else if (key > ptr->data.first)
            ptr = ptr->rchild;
    }

    return nullptr;
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
int map<Key, Val>::node_height(typename map<Key, Val>::Node *p)
{
    int hl;
    int hr;

    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;

    return hl > hr ? hl + 1 : hr + 1;
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
int map<Key, Val>::balance_factor(Node *p)
{
    int hl;
    int hr;

    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;

    return hl - hr;
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
typename map<Key, Val>::Node *map<Key, Val>::LL_rotation(Node *p)
{
    Node *pl = p->lchild;
    Node *plr = pl->rchild;

    pl->rchild = p;
    p->lchild = plr;

    // Update height
    p->height = node_height(p);
    pl->height = node_height(pl);

    // Update root
    if (root == p)
        root = pl;
    return pl;
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
typename map<Key, Val>::Node *map<Key, Val>::RR_rotation(Node *p)
{
    Node *pr = p->rchild;
    Node *prl = pr->lchild;

    pr->lchild = p;
    p->rchild = prl;

    // Update height
    p->height = node_height(p);
    pr->height = node_height(pr);

    // Update root
    if (root == p)
        root = pr;
    return pr;
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
typename map<Key, Val>::Node *map<Key, Val>::LR_rotation(map::Node *p)
{
    Node *pl = p->lchild;
    Node *plr = pl->rchild;

    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;

    plr->lchild = pl;
    plr->rchild = p;

    // Update height
    pl->height = node_height(pl);
    p->height = node_height(p);
    plr->height = node_height(plr);

    // Update root
    if (p == root)
        root = plr;

    return plr;
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
typename map<Key, Val>::Node *map<Key, Val>::RL_rotation(map::Node *p)
{
    Node *pr = p->rchild;
    Node *prl = pr->lchild;

    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;

    prl->rchild = pr;
    prl->lchild = p;

    // Update height
    pr->height = node_height(pr);
    p->height = node_height(p);
    pr->height = node_height(pr);

    // Update root
    if (root == p)
        root = prl;

    return prl;
}

//--------------------------------------------------------------------------------

template <class Key, class Val>
void map<Key, Val>::insert(const std::pair<Key, Val> &elem)
{
    root = r_insert(root, elem);
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
typename map<Key, Val>::Node *map<Key, Val>::r_insert(map::Node *p, const std::pair<Key, Val> &elem)
{
    Node *t;
    if (p == nullptr)
    {
        t = new Node;
        t->data = elem;
        t->lchild = nullptr;
        t->rchild = nullptr;
        t->height = 1; // Starting height from 1 onwards
        return t;
    }

    if (elem.first < p->data.first)
        p->lchild = r_insert(p->lchild, elem);
    else if (elem.first > p->data.first)
        p->rchild = r_insert(p->rchild, elem);

    // Update height
    p->height = node_height(p);

    // Balance factor and rotation

    if (balance_factor(p) == 2 && balance_factor(p->lchild) == 1)
        return LL_rotation(p);
    else if (balance_factor(p) == 2 && balance_factor(p->lchild) == -1)
        return LR_rotation(p);
    else if (balance_factor(p) == -2 && balance_factor(p->rchild) == -1)
        return RR_rotation(p);
    else if (balance_factor(p) == -2 && balance_factor(p->rchild) == 1)
        return RL_rotation(p);

    return p;
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
void map<Key, Val>::inorder(typename map<Key, Val>::Node *p)
{
    if (p)
    {
        inorder(p->lchild);
        std::cout << p->data.first << " - " << p->data.second << '\n';
        inorder(p->rchild);
    }
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
typename map<Key, Val>::Node *map<Key, Val>::InPre(map<Key, Val>::Node *p)
{
    while (p && p->rchild != nullptr)
    {
        p = p->rchild;
    }
    return p;
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
typename map<Key, Val>::Node *map<Key, Val>::InSucc(map<Key, Val>::Node *p)
{
    while (p && p->lchild != nullptr)
    {
        p = p->lchild;
    }
    return p;
}

//--------------------------------------------------------------------------------

template <typename Key, typename Val>
typename map<Key, Val>::Node *map<Key, Val>::erase(map<Key, Val>::Node *p, const Key &key)
{
    if (p == nullptr)
    {
        return nullptr;
    }

    if (p->data.first == key && p->lchild == nullptr && p->rchild == nullptr)
    {
        if (p == root)
            root = nullptr;
        delete p;
        return nullptr;
    }

    if (key < p->data.first)
    {
        p->lchild = erase(p->lchild, key);
    }
    else if (key > p->data.first)
    {
        p->rchild = erase(p->rchild, key);
    }
    else if (key == p->data.first)
    {
        Node *q;
        if (node_height(p->lchild) > node_height(p->rchild))
        {
            q = InPre(p->lchild);
            p->data = q->data;
            p->lchild = erase(p->lchild, q->data.first);
        }
        else
        {
            q = InSucc(p->rchild);
            p->data = q->data;
            p->rchild = erase(p->rchild, q->data.first);
        }
    }

    // Update height
    p->height = node_height(p);

    // Balance Factor and Rotation
    if (balance_factor(p) == 2 && balance_factor(p->lchild) == 1)
    { // L1 Rotation
        return LL_rotation(p);
    }
    else if (balance_factor(p) == 2 && balance_factor(p->lchild) == -1)
    { // L-1 Rotation
        return LR_rotation(p);
    }
    else if (balance_factor(p) == -2 && balance_factor(p->rchild) == -1)
    { // R-1 Rotation
        return RR_rotation(p);
    }
    else if (balance_factor(p) == -2 && balance_factor(p->rchild) == 1)
    { // R1 Rotation
        return RL_rotation(p);
    }
    else if (balance_factor(p) == 2 && balance_factor(p->lchild) == 0)
    { // L0 Rotation
        return LL_rotation(p);
    }
    else if (balance_factor(p) == -2 && balance_factor(p->rchild) == 0)
    { // R0 Rotation
        return RR_rotation(p);
    }

    return p;
}

//--------------------------------------------------------------------------------

template <class Key, class Val>
void map<Key, Val>::delete_nodes(map<Key, Val>::Node *p)
{
    if (p != nullptr)
    {
        if (p != nullptr)
            delete_nodes(p->lchild);
        if (p != nullptr)
            delete_nodes(p->rchild);

        delete p;
    }
}

//--------------------------------------------------------------------------------

}