#include<iostream>

struct Node {
  int data;
  struct Node * lchild;
  struct Node * rchild;
}* root = NULL;
void Insert(int key) {
  struct Node * t = root;
  struct Node * r;
  struct Node * p;
  if (root == NULL) {
    p = new Node;
    p -> data = key;
    p -> lchild = p -> rchild = NULL;
    root = p;
    return;
  }
  while (t != NULL) {
    r = t;
    if (key < t -> data) {
      t = t -> lchild;
    } else if (key > t -> data) {
      t = t -> rchild;
    } else return;
  }
  p = new Node;
  p -> data = key;
  p -> lchild = p -> rchild = NULL;
  if (key < r -> data) {
    r -> lchild = p;
  } else r -> rchild = p;
}
void inOrder(struct Node * p) {
  if (p) {
    inOrder(p -> lchild);
    std::cout << p -> data;
    inOrder(p -> rchild);
  }
}
struct Node * Search(int key) {
  struct Node * t = root;
  while (t != NULL) {
    if (key == t -> data)
      return t;
    else if (key < t -> data)
      t = t -> lchild;
    else t = t -> rchild;
  }
  return NULL;
}
struct Node * RInsert(struct Node * p, int key) {
  struct Node * t = NULL;
  if (p == NULL) {
    t = new Node;
    t -> data = key;
    t -> lchild = t -> rchild = NULL;
    return t;
  }
  if (key < p -> data)
    p -> lchild = RInsert(p -> lchild, key);
  else if (key > p -> data)
    p -> rchild = RInsert(p -> rchild, key);
  return p;
}
int Height(struct Node * p) {
  int x, y;
  if (p == NULL) return 0;
  x = Height(p -> lchild);
  y = Height(p -> rchild);
  return x > y ? x + 1 : y + 1;
}
struct Node * InPre(struct Node * p) {
  while (p && p -> rchild != NULL)
    p = p -> rchild;
  return p;
}
struct Node * InSucc(struct Node * p) {
  while (p && p -> lchild != NULL)
    p = p -> lchild;
  return p;
}
struct Node* Delete(struct Node* p, int key) {
    struct Node* q;
    if (p == NULL)
        return NULL;
    if (p->lchild == NULL && p->rchild == NULL) {
        if (p == root)
            root = NULL;
        delete p;
        return NULL;
    }
    if (key < p->data)
        p->lchild = Delete(p->lchild, key);
    else if (key > p->data)
        p->rchild = Delete(p->rchild, key);
    else {
        if (Height(p->lchild) > Height(p->rchild)) {
            q = InPre(p->lchild);
            p->data = q->data;
            p->lchild = Delete(p->lchild, q->data);
        } else {
            q = InSucc(p->rchild);
            p->data = q->data;
            p->rchild = Delete(p->rchild, q->data);
        }
    }
    return p;
}
int main() {
  std::ios::sync_with_stdio(false);
  struct Node * temp;
  root = RInsert(root, 10);
  RInsert(root, 5);
  RInsert(root, 20);
  RInsert(root, 8);
  RInsert(root , 30);
  Delete(root, 20);
  inOrder(root);
  temp = Search(10);
  if (temp != NULL) {
    std::cout << "\n";
    std::cout << "Element is found : " << temp -> data;
  } else std::cout << "Element is not found";
  std::cout << "\n";
}