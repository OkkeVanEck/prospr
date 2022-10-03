/* File:            test_protein.cpp
 * Description:     Source file for testing the functionality of protein.
 *                  Expects that the following modules work:
 *                      - amino_acid.
 * License:         This file is licensed under the GNU LGPL V3 license by
 *                  Okke van Eck (2020 - 2022). See the LICENSE file for the
 *                  specifics.
 */

#include <iostream>
#include <string.h>
#include <assert.h>
#include "../src/protein.hpp"
#include "../src/depth_first.hpp"
#include "../src/depth_first_bnb.hpp"


/* Test functionality of depth_first. */
void test_depth_first() {
    /* Check if 2D solutions are found correctly. */
    Protein* protein = new Protein("PHPHPHPPH", 2, "HP");
    protein = depth_first(protein);
    assert (protein->get_score() == -3);
    std::cout << "\t2D Protein solution scores matches.\n";

    /* Check if 3D solutions are found correctly. */
    protein = new Protein("HPPHPHPHPH", 3, "HP");
    protein = depth_first(protein);
    assert (protein->get_score() == -4);
    std::cout << "\t3D Protein solution scores matches.\n";
}

/* Test functionality of depth_first_bnb. */
void test_depth_first_bnb() {
    /* Check if 2D solutions are found correctly. */
    Protein* protein = new Protein("PHPHPHPPH", 2, "HP");
    protein = depth_first_bnb(protein);
    assert (protein->get_score() == -3);
    std::cout << "\t2D Protein solution scores matches.\n";

    /* Check if 3D solutions are found correctly. */
    protein = new Protein("HPPHPHPHPH", 3, "HP");
    protein = depth_first_bnb(protein);
    assert (protein->get_score() == -4);
    std::cout << "\t3D Protein solution scores matches.\n";
}

/* Test functionality of all algorithms. */
void run_all() {
    test_depth_first();
    test_depth_first_bnb();
}

int main(int argc, char* argv[]) {
    /* Determine what algorithms to test. */
    if (argc == 1) {
        /* No extra arguments, so testing all algorithms. */
        std::cout << "\tTesting all algorithms..\n";
        run_all();
    } else if (strcmp(argv[1], "depth_first") == 0) {
        test_depth_first();
    } else if (strcmp(argv[1], "depth_first_bnb") == 0) {
        test_depth_first_bnb();
    } else {
        std::cout << "\tSpecific algorithm not detected..\n";
    }

    return 0;
}