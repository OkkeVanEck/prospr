/* File:            protein.cpp
 * Description:     Source file for a protein object within the HP-model.
 */

#include "protein.hpp"
#include <stdlib.h>
#include <algorithm>


/* Construct a new Protein. */
Protein::Protein(std::string sequence, int dim,
        std::map<std::string, int> bond_values) {
    this->sequence = sequence;
    space = {};
    cur_len = 0;
    this->dim = dim;
    last_move = 0;
    last_pos.assign(dim, 0);
    score = 0;
    changes = 0;

    /* Store all indices of the H-amino acid characters in hIdxs. */
    size_t pos = sequence.find("H", 0);

    while (pos != std::string::npos) {
        h_idxs.push_back(pos);
        pos = sequence.find("H", pos + 1);
    }

    /* Create AminoAcid objects for all amino acids. */
    for(std::string::size_type i = 0; i < sequence.size(); i++) {
        amino_acids.push_back(AminoAcid::AminoAcid(c, sequence[i], NULL, NULL));
    }

    /* Place the first amino acid at the origin. */
    space[last_pos] = amino_acids[0];
}

/* Returns the Protein's sequence. */
std::string Protein::get_sequence() {
    return sequence;
}

/* Returns the Protein's set maximum dimension. */
int Protein::get_dim() {
    return dim;
}

/* Returns the Protein's current length. */
int Protein::get_cur_len() {
    return cur_len;
}

/* Returns the last performed move. */
int Protein::get_last_move() {
    return last_move;
}

/* Returns the last position an amino acid was placed. */
std::vector<int> Protein::get_last_pos() {
    return last_pos;
}

/* Returns the AminoAcid at the given position, or NULL if there is
 * none.
 */
AminoAcid Protein::get_amino(std::vector<int> position) {
     if (space.count(position))
        return space.at(position);
     else
        return NULL;
}

/* Returns the Protein's current score. */
int Protein::get_score() {
    return score;
}

/* Returns the number of performed changes. */
int Protein::get_changes() {
    return changes;
}

/* Returns the indexes of the "H" amino acids in the sequence. */
std::vector<int> Protein::get_h_idxs() {
    return h_idxs;
}

/* Returns if the amino acid at the given index is hydrophobic. */
bool Protein::is_hydro(int index) {
    return find(h_idxs.begin(), h_idxs.end(), index) != h_idxs.end();
}

/* Reset all variables of a protein as if it was just initialized. */
void Protein::reset() {
    space.clear();
    cur_len = 0;
    last_pos.assign(dim, 0);
    last_move = 0;
    score = 0;
    changes = 0;
}

/* Reset only the conformation variables of a protein. */
void Protein::reset_conformation() {
    space.clear();
    cur_len = 0;
    last_pos.assign(dim, 0);
    last_move = 0;
    score = 0;
}

/* Returns true if a move is valid, returns false otherwise. */
bool Protein::is_valid(int move) {
    std::vector<int> check_pos = last_pos;
    check_pos[abs(move) - 1] += move / abs(move);

    /* Check if the placement causes overlap. */
    if (space.count(check_pos) == 0)
        return true;
    else
        return false;
}

/* Place the next amino acid and update the conformation accordingly. */
void Protein::place_amino(int move, bool track) {
    if (track)
        changes++;

    if (move != 0) {
        space[last_pos][1] = move;
        last_pos[abs(move) - 1] += move / abs(move);
    }

    if (space.count(last_pos) > 0)
        throw std::runtime_error("Protein folded onto itself..");

    /* Change score according to placement of the new amino. */
    if (move != 0 && is_hydro(cur_len))
        change_score(move, -1);

    space[last_pos] = std::vector<int>{cur_len, 0};
    last_move = move;
    cur_len++;
}

// TODO: Change function to use the last_move attribute.
/* Change score according to removal of the last amino. */
void Protein::remove_amino(int move) {
    cur_len--;

    if (move != 0 && is_hydro(cur_len))
        change_score(move, 1);

    /* Remove the last amino. */
    space.erase(last_pos);
    last_pos[abs(move) - 1] -= move / abs(move);
    space[last_pos][1] = 0;
}

/* Change score according to the addition or removal of the given move. */
void Protein::change_score(int move, int weight) {
    std::vector<int> moves;

    for (int i = -dim; i <= dim; i++) {
        if (i != 0 and i != -move)
            moves.push_back(i);
    }

    std::vector<int> cur_pos;

    for (auto &move: moves) {
        cur_pos = last_pos;
        cur_pos[abs(move) - 1] += move / abs(move);

        if (space.count(cur_pos) > 0 && is_hydro(space[cur_pos][0]))
            score += weight;
    }
}

/* Hash and return the fold of the current conformation. */
std::vector<int> Protein::hash_fold() {
    std::vector<int> fold_hash;
    std::vector<int> cur_pos(dim, 0);
    std::vector<int> item;

    if (space.count(cur_pos) > 0) {
        item = space.at(cur_pos);

        while (item[1] != 0) {
            cur_pos[abs(item[1]) - 1] += item[1] / abs(item[1]);
            fold_hash.push_back(item[1]);
            item = space.at(cur_pos);
        }
    }

    return fold_hash;
}

/* Set the conformation to the given hash. */
void Protein::set_hash(std::vector<int> fold_hash, bool track) {
    reset_conformation();
    place_amino(0, track);

    for (auto &move: fold_hash) {
        place_amino(move, track);
    }
}
