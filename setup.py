#!/usr/bin/env python3
"""
File:           setup.py
Description:    This file contains the setup required for distributing the
                package on PyPi.org.
"""

import os
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

__version__ = "0.2a3"

# Define core module extension.
ext_modules = [
    Pybind11Extension(
        "prospr_core",
        ["prospr/core/core_module.cpp"],
        define_macros=[("VERSION_INFO", __version__)],
        optional=os.environ.get("CIBUILDWHEEL", "0") != "1",
        language="c++",
    ),
]

# Load README for PyPI description.
with open("README.md", "r") as f:
    long_description = f.read()

setup(
    name="prospr",
    version=__version__,
    author="okkevaneck",
    description="A toolbox for protein folding with Python.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/okkevaneck/prospr",
    license="LGPLv3",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    packages=["prospr"],
    package_data={"prospr": ["data/*/*.csv"]},
    platforms=["any"],
    python_requires=">=3.6",
    zip_safe=False,
    install_requires=[
        "matplotlib",
        "seaborn",
        "numpy",
        "pandas",
    ],
    classifiers=[
        "Programming Language :: Python :: 3",
        "Development Status :: 2 - Pre-Alpha",
        "License :: OSI Approved :: GNU Lesser General Public License v3 "
        + "(LGPLv3)",
        "Operating System :: OS Independent",
        "Topic :: Education",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Bio-Informatics",
    ],
    keywords=[
        "prospr protein structure prediction toolbox python c++ swig cmake "
        + "extension heuristics pypi package"
    ],
)
