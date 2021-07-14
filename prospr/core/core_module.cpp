/* File:            core_module.cpp
 * Description:     Source file defining the pybind11 interfaces for exporting
 *                      the c++ core to a Python interface.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include "src/amino_acid.cpp"
#include "src/protein.cpp"
#include "src/depth_first.cpp"
#include "src/depth_first_bnb.cpp"


/* Definition for bond_values as default parameter value. */
std::map<char, int> bond_values_cpp = {{'H', -1}, {'P', 0}};
py::object bond_values = py::cast(bond_values_cpp);

PYBIND11_MODULE(prospr_core, m) {
    m.doc() = "Prospr core written in C++.";

    /* AminoAcid class definition. */
    py::class_<AminoAcid>(m, "AminoAcid")
        .def(py::init<const std::string, int , int, int, int&>(),
                "AminoAcid constructor", py::arg("type"), py::arg("index"),
                py::arg("prev_move"), py::arg("next_move"))
        .def_property_readonly("type", &AminoAcid::get_type)
        .def_property_readonly("index", &AminoAcid::get_index)
        .def_property_readonly("prev_move", &AminoAcid::get_prev_move)
        .def_property_readonly("next_move", &AminoAcid::get_next_move)
    ;

    /* Protein class definition. */
    py::class_<Protein>(m, "Protein")
        .def(py::init<const std::string, int &>(), "Protein constructor",
                py::arg("sequence"), py::arg("dim")=2,
                py::arg("bond_values")=bond_values) // TODO: Check if set correctly.
        .def_property_readonly("changes", &Protein::get_changes)
        .def_property_readonly("cur_len", &Protein::get_cur_len)
        .def_property_readonly("dim", &Protein::get_dim)
        .def_property_readonly("h_idxs", &Protein::get_h_idxs)
        .def_property_readonly("last_move", &Protein::get_last_move)
        .def_property_readonly("last_pos", &Protein::get_last_pos)
        .def_property_readonly("score", &Protein::get_score)
        .def_property_readonly("sequence", &Protein::get_sequence)

        .def("get_amino", &Protein::get_amino,
            "Get amino index and next direction from amino at given position",
            py::arg("position"))
        .def("is_hydro", &Protein::is_hydro,
            "Check if the amino is an H at given position", py::arg("index"))
        .def("reset", &Protein::reset, "Reset the whole protein")
        .def("reset_conformation", &Protein::reset_conformation,
            "Reset only the conformation of the protein, not the statistics")
        .def("is_valid", &Protein::is_valid, "Check if a given move is valid",
            py::arg("move"))
        .def("place_amino", &Protein::place_amino,
            "Place a protein in a given direction", py::arg("move"),
            py::arg("track")=true)
        .def("remove_amino", &Protein::remove_amino,
            "Remove the last placed amino")
        .def("hash_fold", &Protein::hash_fold,
            "Process the current conformation into a sequence of moves")
        .def("set_hash", &Protein::set_hash,
            "Set the conformation to the given sequence of moves",
            py::arg("fold_hash"), py::arg("track")=false)
    ;

    /* Depth-first search function definition. */
    m.def("depth_first", &dfs::depth_first,
        "Finds the optimal conformation via depth-first search",
        py::arg("protein"));

    /* Depth-first branch-and-bound search function definition. */
    m.def("depth_first_bnb", &dfs_bnb::depth_first_bnb,
        "Finds the optimal conformation via depth-first branch-and-bound search",
        py::arg("protein"));
}
