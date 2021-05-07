.. How to install Prospr.

Installation
============
One can choose to use the Python package, or only the C++ core. The C++ core is
handy for maximizing the execution speed of your experiments, while the Python
package may lower development time and offers more functionality. Installation
instructions are provided for both scenarios.


Python package
--------------
Prospr offers support for Python 3.6 and newer. However, using the latest Python
version is always recommended. The instructions below assume that a new project
will be set up.

Virtual environments
~~~~~~~~~~~~~~~~~~~~
It is recommended to use a new virtual environment for each Python project. An
easy way to setup a new virtual environment is via the **venv** module that
comes with Python 3. After creation, one must activate the virtual environment
before installing any packages. Examples for Linux/MacOS and Windows are given
below.

For Linux/MacOS:

.. code-block:: text

    $ python3 -m venv venv
    $ source venv/bin/activate

For Windows:

.. code-block:: text

    > py -3 -m venv venv
    > venv/Scripts/activate

Installing Prospr
~~~~~~~~~~~~~~~~~
After activating the environment, use pip to install Prospr:

.. code-block:: bash

    $ pip install prospr

Congratulations! Prospr is now installed. Check out the :doc:`quickstart`
to see how to use the basics, or read the :doc:`manpages` for all functionality.


C++ core
--------
Using the C++ core for your project is very easy. Follow the installation steps
below and include the header files you want to use in your code.

Installing Prospr
~~~~~~~~~~~~~~~~~
Using the C++ core is very easy. Download a *prospr_core.x* archive from the
`archives <https://github.com/OkkeVanEck/prospr/tree/master/archives>`_ folder
on GitHub, then drag the source files to your code directory. Add the files to
your Makefile in order to compile the Prospr files with your project. No
additional libraries need to be linked during compile time.

.. TODO: Add an example of how to setup the project + an example Makefile.

Congratulations! Prospr is now installed. Check out the :doc:`quickstart`
to see how to use the basics, or read the :doc:`manpages` for all functionality.
