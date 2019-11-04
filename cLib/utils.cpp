// Tabu List
// TODO: Adaptar para uma TabuList de soluções simuladas

Node::Node() {
  left = NULL;
  right = NULL;
}

BinaryTree::BinaryTree() {
  root = new Node;
  size = 0;
}

BinaryTree::~BinaryTree() {
  clear_tree(root);
}

void BinaryTree::clear_tree(Node *node) {
  if (node != NULL) {
    clear_tree(node->left);
    clear_tree(node->right);
    delete node;
  }
}

bool BinaryTree::find(std::vector<bool> sol) {
  Node *current;

  current = root;
  for (bool k : sol) {
    if (k && current->right) {
      //std::cout << current->right << std::endl;
      current = current->right;
      continue;
    }

    if (!k && current->left) {
      //std::cout << current->left << std::endl;
      current = current->left;
      continue;
    }
    return false;
  }

  return true;
}

void BinaryTree::add(std::vector<bool> sol) {
  int i = 0;
  int size = sol.size();
  Node *current;

  size++;

  current = root;
  while (current) {
    if (sol[i] && current->right) {
      current = current->right;
      i++;
      continue;
    }
    if (!sol[i] && current->left){
      current = current->left;
      i++;
      continue;
    }

    break;
  }

  for (int k=i; k<size; k++) {
    if (sol[k]) {
      current->right = new Node;
      current = current->right;
    }
    else {
      current->left = new Node;
      current = current->left;
    }
  }
}