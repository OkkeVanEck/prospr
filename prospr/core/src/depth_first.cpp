/* File:            depth_first.cpp
 * Description:     Source file for a depth-first search function.
 */

#include "depth_first.hpp"
#include <stack>
#include <vector>
#include <algorithm>

namespace dfs {
    /* Initialize the stack and all_moves vector. */
    void initialize_vars(Protein* protein,
                         std::stack<std::vector<int>>* dfs_stack,
                         std::stack<int>* prev_moves,
                         std::vector<int>* all_moves,
                         int max_length,
                         int first_move) {
        int dim = protein->get_dim();

        /*  Setup all_moves for stack initialization. */
        for (int i = 1; i <= dim; i++) {
            if (i == first_move)
                continue;

            all_moves->push_back(i);
        }

        /* Setup stacks, limiting negative movement to prevent symmetry. */
        for (int i = 0; i < max_length - 2; i++) {
            protein->place_amino(2);
            dfs_stack->push(*all_moves);
            prev_moves->push(2);
        }

        /* Setup all_moves for further usage. */
        all_moves->clear();

        for (int i = -dim; i <= dim; i++) {
            if (i == 0)
                continue;

            all_moves->push_back(i);
        }
    }

    /* A depth-first search function for finding a minimum energy conformation. */
    Protein depth_first(Protein protein) {
        int max_length = protein.get_sequence().length();

        /* The first two amino acids are fixed in order to prevent symmetry. */
        if (max_length >= 1)
            protein.place_amino(0);
        if (max_length >= 2)
            protein.place_amino(2);
        if (max_length < 3)
            return protein;

        /* Setup all_moves for initializing the stack. */
        int move = 2;
        std::vector<int> all_moves;
        std::stack<std::vector<int>> dfs_stack;
        std::stack<int> prev_moves;
        initialize_vars(&protein, &dfs_stack, &prev_moves, &all_moves, max_length,
                        move);

        /* Declare and set variables for the depth-first search. */
        int best_score = 1;
        std::vector<int> best_hash;
        std::vector<int> remaining_moves;
        int prev_move;
        int score;
        bool placed_amino;

        while (!dfs_stack.empty()) {
            /* Check if the bottom of the tree is reached and store best folds.
             * Continue with next amino acid otherwise.
             */
            if (protein.get_cur_len() == max_length) {
                score = protein.get_score();

                if (score < best_score) {
                    best_score = score;
                    best_hash = protein.hash_fold();
                }

                remaining_moves.clear();
            } else {
                remaining_moves = all_moves;
                remaining_moves.erase(std::remove(remaining_moves.begin(),
                                                  remaining_moves.end(), -move),
                                      remaining_moves.end());
            }

            /* Loop till an amino acid is placed or no new combinations are left. */
            placed_amino = false;

            while (!placed_amino) {
                /* Try all remaining moves for the current amino acid. */
                while (!placed_amino && !remaining_moves.empty()) {
                    move = remaining_moves.back();
                    remaining_moves.pop_back();

                    /* Place amino acid if valid and update stacks accordingly. */
                    if (protein.is_valid(move)) {
                        protein.place_amino(move);
                        dfs_stack.push(remaining_moves);
                        prev_moves.push(move);
                        placed_amino = true;
                    }
                }

                /* Backtrack if the current amino acid has no moves left. */
                while (!placed_amino && remaining_moves.empty() &&
                       !dfs_stack.empty()) {
                    remaining_moves = dfs_stack.top();
                    prev_move = prev_moves.top();
                    dfs_stack.pop();
                    prev_moves.pop();
                    protein.remove_amino(prev_move);
                }

                /* Check if there are no moves left. */
                if (remaining_moves.empty())
                    break;
            }
        }

        protein.set_hash(best_hash);

        return protein;
    }
}
