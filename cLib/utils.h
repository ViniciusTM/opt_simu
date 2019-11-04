// Tabu List
// TODO: Adaptar para uma TabuList de soluções simuladas

struct Node {
  Node *left;
  Node *right;

  Node();
};

struct BinaryTree {
  Node *root;
  int size;

  BinaryTree();
  ~BinaryTree();

  void clear_tree(Node*);
  bool find(std::vector<bool>);
  void add(std::vector<bool>);
};