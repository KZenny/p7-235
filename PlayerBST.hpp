#pragma once
#include "ChessPlayer.hpp"
#include "Node.hpp"

#include <string>
#include <vector>
#include <cmath>

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

    // Define your function signatures below ======================================================================================================

    /**
     * @brief Default constructor; constructs an empty BST
     * @post The `root_` is set to nullptr & `size_` to 0.
     */
    PlayerBST();

    /**
     * @brief Getter for the `root_` member
     * @returns The a pointer to the root of the PlayerBST, 
     * or nullptr if the tree is empty.
     */
    Node<ChessPlayer>* getRoot() const;

    /**
     * @brief Getter for the `size_` member
     * @returns The number of Players (ie. nodes) 
     * in the PlayerBST as an integer
     */
    int size() const;
    
    /**
     * @brief Searches for a Player in the PlayerBST
     * with the specified name.
     *
     * @param value A const reference to a STRING representing
     * the name of the Player to search for.
     * @returns True if the player exists in the BST. False otherwise.
     */
    bool contains(const std::string& value) const;

    /**
     * @brief Inserts a Player into the PlayerBST
     * if a player with their name does NOT already exist.
     *
     * @param value A const. reference to the ChessPlayer to insert
     * @returns True if the player was sucessfully inserted. False otherwise.
     * @post Increments the BST's size if the value was succesfully inserted
     */
    bool insert(const ChessPlayer& value);

    /**
     * @brief Calculates the average number of wins
     * across all Players in the PlayerBST, rounded
     * to at second decimal place (eg. 1.00, 2.50, 3.14 etc.)
     *
     * @returns The average number of wins or 0.0
     * if the BST is empty, as a double
     */
    double averageWins() const;

    /**
     * @brief A helper function to calculate the average number of wins across all Players in the PlayerBST, rounded to the second decimal place.
     *
     * @param subroot A Node pointer of the current subroot
     * @returns An integer with the number of wins the player has
    */
    int averageWinsHelper(Node<ChessPlayer>* subroot) const;

    /**
    * @brief Counts the number of Players in the BST with
    * greater than or equal to the specified minimum number of wins.
    *
    * @param min_wins A const reference to an integer
    * denoting the minimum number of wins to check against
    * @returns The count of players with wins >= min_wins
    * as an integer
    */
    int countAboveWins(const int& min_wins) const;

    /**
     * @brief A helper function to count the number of players in BST with greater than or equal to the specified minimum number of wins.
     *
     * @param min_wins A const reference to an integer
     * @param node A Node pointer of the current subroot
     * @returns An integer representing the number of players with wins greater than or equal to specified minimum wins.
     */
    int countAboveWinsHelper(const int& min_wins, Node<ChessPlayer>* node) const;

    /**
     * @brief Creates a vector of all ChessPlayers in the BST
     * using the specified traversal order.
     *
     * @param traversal A const reference to the traversal type
     * (ie. IN_ORDER, PRE_ORDER, POST_ORDER)
     * @returns A vector containing all ChessPlayers in the PlayerBST 
     * read in the specified traversal order.
     */
    std::vector<ChessPlayer> toVector(const TraversalType& traversal) const;

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
    void toVectorHelper(Node<ChessPlayer>* node, std::vector<ChessPlayer>& result, const TraversalType& traversal) const;

};