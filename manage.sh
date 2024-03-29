#!/usr/bin/env bash
# File:             manage.sh
# Description:      This bash file supports the commands:
#                       - "init"        for setting up a developing environment.
#                       - "echo_debug"  for printing the used global variables.
#                       - "build"       for building the Python interfaces for
#                                           the core .cpp files.
#                       - "clean"       for removing all Python interfaces,
#                                           .cxx files, and Python caches.
#                       - "test"        for testing all Python code with pytest.

set -e

COREDIR=prospr/core
CXX_FILES=$(find ${COREDIR}/ -type f -name "*.cxx")
SO_FILES=$(find prospr/ -type f -name "*.so")
PY_FILES=$(find ${COREDIR}/ -type f -name "*.py" ! -name "__init__.py" \
    ! -name "setup.py")
PYCACHES=$(find prospr/ -type d -name "__pycache__")
CFLAGS="-o3 -Wall -Wextra -Wconversion -Wcast-align -std=c++11
    -Wunreachable-code"

case "$1" in
    # Setup a developing environment.
    "init")
        pip install -r requirements.txt
        sudo apt install clang-format
        pre-commit install
        ;;
    # Echo all global variables.
    "echo_debug")
        echo -e "Core dir:\n${COREDIR}\n"
        echo -e "CXX files:\n${CXX_FILES}\n"
        echo -e "SO files:\n${SO_FILES}\n"
        echo -e "PY files:\n${PY_FILES}\n"
        echo -e "PyCaches:\n${PYCACHES}\n"
        ;;
    # Build all Python interfaces for the core .cpp files.
    "build")
        echo "~ Creating the .py interface for the core.."
        # Add -undefined dynamic_lookup flag for MacOS builds.
        if [[ "$OSTYPE" == "darwin"* ]]; then
            c++ -o3 -Wall -shared -std=c++11 -fPIC -undefined dynamic_lookup \
            $(python3 -m pybind11 --includes) "${COREDIR}/core_module.cpp" \
            -o "prospr"/prospr_core$(python3-config --extension-suffix)
        else
            c++ -o3 -Wall -shared -std=c++11 -fPIC \
            $(python3 -m pybind11 --includes) "${COREDIR}/core_module.cpp" \
            -o "prospr"/prospr_core$(python3-config --extension-suffix)
        fi
        echo "~ Done building!"
        ;;
    # Remove all Python interfaces, .cxx files, and Python caches.
    "clean")
        echo "~ Removing all built .cxx, .so and .py files.."
        rm -f ${CXX_FILES} ${SO_FILES} ${PY_FILES}
        rm -f *.so
        echo -e "~ Removing all __pycache__ directories.."
        rm -rf ${PYCACHES}
        echo -e "~ Removing build directories.."
        rm -rf build
        rm -rf prospr.egg-info
        echo -e "~ Removing generated docs.."
        rm -rf docs/build
        echo -e "~ Done cleaning!"
        ;;
    # Generate docs locally.
    "gen_docs")
        cd docs
        echo -e "~ Generating HTML documentation.."
        make html
        echo -e "~ Done generating!"
        ;;
    # Build core, test all Python code, and then clean everything.
    "test")
        echo "~ Uninstalling old prospr.."
        pip uninstall -qy prospr
        echo "~ Installing new prospr.."
        pip install -q .
        echo "~ Running pytest.."
        pytest || true
        echo "~ Uninstalling old prospr.."
        pip uninstall -qy prospr
        echo "~ Done running tests!"
        ;;
    # Test core without building the Python interfaces.
    "test_core")
        echo "~ Running core tests.."
        ./"$COREDIR/tests/run_tests.sh" "$2"
        ;;
    # Test core on memory leaks with Valgrind.
    # Does so without building the Python interfaces.
    "test_core_valgrind")
        echo "~ Running core tests.."
        ./"$COREDIR/tests/run_tests.sh" "$2" "valgrind"
        ;;
    # Test visualizations without building the Python interfaces.
    "test_visualize")
        echo "~ Running visualize tests.."
        echo "~ Uninstalling old prospr.."
        pip uninstall -qy prospr
        echo "~ Installing new prospr.."
        pip install -q .
        python tests/visualize/test_visualization.py "show" "$2" "$3"
        echo "~ Uninstalling old prospr.."
        pip uninstall -qy prospr
        echo "~ Done running tests!"
        ;;
    # Test core without building the Python interfaces and running GDB.
    "debug_core")
        echo "~ Running core tests.."
        ./"$COREDIR/tests/run_tests.sh" "$2" "debug"
        ;;
    # Install prospr locally, launch shell, and uninstall afterwards.
    "debug_shell")
        echo "~ Launch debug shell with Prospr installed.."
                echo "~ Uninstalling old prospr.."
        pip uninstall -qy prospr
        echo "~ Installing new prospr.."
        pip install -q .
        python -i prospr_interpreter.py
        echo "~ Uninstalling old prospr.."
        pip uninstall -qy prospr
        echo "~ Closed successfully!"
        ;;
    # Compile core into binary for debugging.
    "comp_core")
        echo "~ Compiling core.."
        SRCDIR=$COREDIR/src
        c++ "$CFLAGS" -o test_algorithms $COREDIR/tests/test_algorithms.cpp \
            $SRCDIR/beam_search.cpp $SRCDIR/depth_first.cpp \
            $SRCDIR/depth_first_bnb.cpp $SRCDIR/protein.cpp \
            $SRCDIR/amino_acid.cpp
        ;;
    *)
        echo "No command detected from first argument.."
        ;;
esac
