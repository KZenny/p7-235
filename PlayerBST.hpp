#pragma once
#include "ChessPlayer.hpp"
#include "Node.hpp"

#include <string>
#include <vector>

enum TraversalType {
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER
};

/**
 * @brief The interface for a PlayerBST,
 * describing a BST ordered by the names
 * of ChessPlayer objects
 */
class PlayerBST {
protected:
    Node<ChessPlayer>* root_;
    int size_;

private:
    /**
     * @brief Helper function to delete node recursively.
     *
     * @param node Current subroot
     * @param value The name of the Player to delete
     * @return Updated node pointer
     */
    Node<ChessPlayer>* removeHelper(Node<ChessPlayer>* node, const std::string& name);

    /**
     * Deletes all nodes in the tree recursively.
     * @param node Current node to delete
     */
    void destroyTree(Node<ChessPlayer>* node);

public:
    /**
     * @brief Destructor to clean up all nodes.
     */
    ~PlayerBST();

    /**
     * @brief Removes a Player from the PlayerBST
     * if a player with their name exists.
     *
     * @param value A const reference a string representing
     * the name of the Player to be removed.
     * @returns True if the player was successfully removed. False otherwise.
     * @post Decrements `size_` if the player was removed.
     */
    bool remove(const std::string& name);

    // Define your function signatures below ========
};