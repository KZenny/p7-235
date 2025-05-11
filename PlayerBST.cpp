#include "PlayerBST.hpp"

/**
 * @brief Destructor to clean up all nodes.
 */
PlayerBST::~PlayerBST()
{
    destroyTree(root_);
}

void PlayerBST::destroyTree(Node<ChessPlayer>* node)
{
    if (!node) {
        return;
    }

    destroyTree(node->getLeftChild());
    destroyTree(node->getRightChild());
    delete node;
    node = nullptr;
}

Node<ChessPlayer>* PlayerBST::removeHelper(Node<ChessPlayer>* node, const std::string& name)
{
    if (!node) {
        return nullptr;
    }

    // Traverse the tree to find the node to delete
    if (name < node->getValue().name_) {
        node->setLeftChild(removeHelper(node->getLeftChild(), name));
        return node;
    } else if (name > node->getValue().name_) {
        node->setRightChild(removeHelper(node->getRightChild(), name));
        return node;
    }
    // Node found, handle deletion

    // Case 1: Node with no children (leaf node)
    if (!node->getLeftChild() && !node->getRightChild()) {
        delete node;
        size_--;
        return nullptr;
    }
    // Case 2: Node with only one child
    else if (!node->getLeftChild()) {
        Node<ChessPlayer>* temp = node->getRightChild();
        delete node;
        size_--;
        return temp;
    } else if (node->getRightChild() == nullptr) {
        Node<ChessPlayer>* temp = node->getLeftChild();
        delete node;
        size_--;
        return temp;
    }

    // Case 3: Node with two children
    // Find the inorder successor (smallest node in right subtree)
    Node<ChessPlayer>* successor = node->getRightChild();
    while (successor->getLeftChild() != nullptr) {
        successor = successor->getLeftChild();
    }

    // Copy the successor's value to this node
    node->setValue(successor->getValue());

    // Delete the now-duplicate successor
    node->setRightChild(removeHelper(node->getRightChild(), successor->getValue().name_));

    return node;
}

bool PlayerBST::remove(const std::string& name)
{
    int oldSize = size_;
    root_ = removeHelper(root_, name);
    // If size changed, removal was successful
    return oldSize > size_;
}

// ====== Your code below =========================================================================================================================

/**
 * @brief Default constructor; constructs an empty BST
 * @post The `root_` is set to nullptr & `size_` to 0.
 */
PlayerBST::PlayerBST() : root_(nullptr), size_(0) {}

/**
 * @brief Getter for the `root_` member
 * @returns The a pointer to the root of the PlayerBST, 
 * or nullptr if the tree is empty.
 */
Node<ChessPlayer>* PlayerBST::getRoot() const {
    return root_;
}

/**
 * @brief Getter for the `size_` member
 * @returns The number of Players (ie. nodes) 
 * in the PlayerBST as an integer
 */
int PlayerBST::size() const {
    return size_;
}
 
/**
 * @brief Searches for a Player in the PlayerBST
 * with the specified name.
 *
 * @param value A const reference to a STRING representing
 * the name of the Player to search for.
 * @returns True if the player exists in the BST. False otherwise.
 */
bool PlayerBST::contains(const std::string& value) const {
    Node<ChessPlayer>* current = root_;
    while (current != nullptr) {
        if (value == current->getValue().name_) {
            return true;
        } else if (value < current->getValue().name_) {
            current = current->getLeftChild();
        } else {
            current = current->getRightChild();
        }
    }
    return false;
}

 /**
  * @brief Inserts a Player into the PlayerBST
  * if a player with their name does NOT already exist.
  *
  * @param value A const. reference to the ChessPlayer to insert
  * @returns True if the player was sucessfully inserted. False otherwise.
  * @post Increments the BST's size if the value was succesfully inserted
  */
bool PlayerBST::insert(const ChessPlayer& value) {
    Node<ChessPlayer>* newNode = new Node<ChessPlayer>(value);
    if (root_ == nullptr) {
        root_ = newNode;
        size_++;
        return true;
    } 

    Node<ChessPlayer>* current = root_;
    Node<ChessPlayer>* parent = nullptr;

    while (current != nullptr) {
        if (value.name_ == current->getValue().name_) {
            delete newNode; 
            return false; 
        }

        parent = current;
        if (value.name_ < current->getValue().name_) {
            current = current->getLeftChild();
        } else {
            current = current->getRightChild();
        }
    }

    if (value.name_ < parent->getValue().name_) {
        parent->setLeftChild(newNode);
    } else {
        parent->setRightChild(newNode);
    }

    size_++;
    return true;
}
/**
 * @brief Calculates the average number of wins
 * across all Players in the PlayerBST, rounded
 * to at second decimal place (eg. 1.00, 2.50, 3.14 etc.)
 *
 * @returns The average number of wins or 0.0
 * if the BST is empty, as a double
 */
double PlayerBST::averageWins() const {
    if (size_ == 0) {
        return 0.0;
    }

    int totalWins = averageWinsHelper(root_);
    double average = static_cast<double>(totalWins) / size_;
    return std::round(average * 100.0) / 100.0; // Round to 2 decimal places
}

/**
 * @brief A helper function to calculate the average number of wins across all Players in the PlayerBST, rounded to the second decimal place.
 *
 * @param subroot A Node pointer of the current subroot
 * @returns An integer with the number of wins the player has
 */
int PlayerBST::averageWinsHelper(Node<ChessPlayer>* subroot) const {
    if (subroot == nullptr) {
        return 0;
    }

    int leftSum = averageWinsHelper(subroot->getLeftChild());
    int rightSum = averageWinsHelper(subroot->getRightChild());
    int currentWins = subroot->getValue().wins_;

    return leftSum + rightSum + currentWins;
}

/**
 * @brief Counts the number of Players in the BST with
 * greater than or equal to the specified minimum number of wins.
 *
 * @param min_wins A const reference to an integer
 * denoting the minimum number of wins to check against
 * @returns The count of players with wins >= min_wins
 * as an integer
 */
int PlayerBST::countAboveWins(const int& min_wins) const {
    return countAboveWinsHelper(min_wins, root_);
}

/**
 * @brief A helper function to count the number of players in BST with greater than or equal to the specified minimum number of wins.
 *
 * @param min_wins A const reference to an integer
 * @param node A Node pointer of the current subroot
 * @returns An integer representing the number of players with wins greater than or equal to specified minimum wins.
 */
int PlayerBST::countAboveWinsHelper(const int& min_wins, Node<ChessPlayer>* node) const{
    if (!node) {
        return 0;
    }
    int num_wins_count = 0;

    if (node->getValue().wins_ >= min_wins) {
        num_wins_count = 1;
    }

    return num_wins_count + countAboveWinsHelper(min_wins, node->getLeftChild()) + countAboveWinsHelper(min_wins, node->getRightChild());
}


/**
 * @brief Creates a vector of all ChessPlayers in the BST
 * using the specified traversal order.
 *
 * @param traversal A const reference to the traversal type
 * (ie. IN_ORDER, PRE_ORDER, POST_ORDER)
 * @returns A vector containing all ChessPlayers in the PlayerBST 
 * read in the specified traversal order.
 */
std::vector<ChessPlayer> PlayerBST::toVector(const TraversalType& traversal) const {
    std::vector<ChessPlayer> result;
    toVectorHelper(root_, result, traversal);
    return result;
}

/**
 * @brief A helper function to create a vector of all ChessPlayers in the BST 
 *
 * @param node A pointer to the current node that is visted by the transversal
 * @param result A reference to the vector to be filled with ChessPlayers
 * @param traversal A const reference to the traversal type
 * (ie. IN_ORDER, PRE_ORDER, POST_ORDER)
 * @returns A vector containing all ChessPlayers in the PlayerBST 
 * read in the specified traversal order.
 */
void PlayerBST::toVectorHelper(Node<ChessPlayer>* node, std::vector<ChessPlayer>& result, const TraversalType& traversal) const {
    if (!node) return;

    if (traversal == PRE_ORDER) {
        result.push_back(node->getValue());
    }

    toVectorHelper(node->getLeftChild(), result, traversal);

    if (traversal == IN_ORDER) {
        result.push_back(node->getValue());
    }

    toVectorHelper(node->getRightChild(), result, traversal);

    if (traversal == POST_ORDER) {
        result.push_back(node->getValue());
    }
}

 