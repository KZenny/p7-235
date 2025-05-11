// File: ChessPlayer.hpp
// Author: Kenny Zhou
// Date: 5/11/2025
// A header file containing a ChessPlayer struct.
#pragma once

#include <string>
struct ChessPlayer {
    /**
     * @brief The name of the Chess player
     */
    std::string name_;

    /**
     * @brief The number of wins this player has
     * @pre Must be non-negative (ie. >= 0)
     */
    int wins_;
};