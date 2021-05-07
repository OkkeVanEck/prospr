.. prospr documentation master file, created by
   sphinx-quickstart on Fri Apr 30 14:15:36 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Prospr: The Protein Structure Prediction Toolbox
================================================
Release v\ |release|

Welcome to Prospr's documentation! Prospr is a Python toolbox for protein
structure prediction, build on a C++ core. The Python package can be used when
quick development is of key, and when Prospr's datasets and visualization module
are of interest. The C++ core is available as a standalone for all
high-performance computing applications. Ideally, the C++ core is used for time
efficient data gathering, while the Python package is used for managing
experiments. However, the Python package wraps all the C++ core's functionality,
hence one can solely rely on using the Python package.

See the :doc:`installation` and :doc:`quickstart` pages for an easy introduction
to the basics of Prospr. There are also the :doc:`manpages` where all
functionality of Prospr is explained in-depth per module.

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   installation
   quickstart
   manpages
