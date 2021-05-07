.. Quickstart for using Prospr for the first time.

Quickstart
==========
One can choose to use the Python package, or only the C++ core. The C++ core is
handy for maximizing the execution speed of your experiments, while the Python
package may lower development time and offers more functionality.

Example usage is given using the Python package and only shows basic usage.
Please refer to the :doc:`manpages` to see the equivalent usage in C++ and all
functionality.

Please take a look at the :doc:`installation` page first to see how Prospr can
be installed.

Creating Proteins
-----------------
After installing Prospr, one can simply create a Protein object as
follows:

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPHPPH")
    p_3d = Protein("HPPHPPH", dim=3)
    p_4d = Protein("HPPHPPH", dim=4)
    p_5d = Protein("HPPHPPH", dim=5)
    ...

Protein attributes
------------------
A Protein object keeps track of multiple properties while it is being folded.
These properties can be checked as attributes of the Protein object. Below all
properties are listed, but please refer to the :doc:`manpages` to see what they
all keep track of exactly.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")

    p_2d.sequence
    >>> "HPPH"

    p_2d.h_idxs
    >>> [0, 3]

    p_2d.cur_len
    >>> 0

    p_2d.dim
    >>> 2

    p_2d.last_move
    >>> 0

    p_2d.last_pos
    >>> [0, 0]

    p_2d.score
    >>> 0

    p_2d.changes
    >>> 0

Placing amino acids
-------------------
A Protein object is generated with the first amino acid fixed at the origin.
One can place the next amino acid via the *.place_amino(move)* function.
This function takes a move as an argument, which is a number representing the
axis to move over. As an example, 1 can be seen as the x-axis, 2 as the y-axis,
etc. Negative numbers represent movement in negative direction.

.. code-block:: python

    ...
    p_2d.place_amino(1)
    p_2d.place_amino(2)
    p_2d.place_amino(-1)

Removing amino acids
--------------------
Amino acids can be removed via the *.remove_amino()* function.

.. code-block:: python

    ...
    p_2d.remove_amino() # Leaving the previous moves [1, 2]
    p_2d.remove_amino() # Leaving the previous move [1]

Validating moves
----------------
Before trying to place an amino acid, it it is recommended to check whether the
move is valid. This can be done via the *.is_valid(move)* function, which takes
the requested move as an argument.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")
    p_2d.is_valid(1)
    >>> True

    p_2d.place_amino(1)
    p_2d.is_valid(-1)
    >>> False

Placement information
---------------------
While writing algorithms, it might be necessary to check what amino acid is
placed at a specific spot, or where the previous and next ones are placed. This
can be checked via the *.get_amino(position)* function, which takes a list of
integers representing the requested position as an argument. It returns a list
containing the amino acids index, previous direction, and next direction.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")
    p_2d.place_amino(1)
    p_2d.place_amino(2)
    p_2d.get_amino([1, 0])
    >>> [1, -1, 2]

It might also occur that you want to check if an amino acid at a specific index
is hydrophilic. This can be checked via the *.is_hydro(index)* function, which
takes the index of the requested amino acid as an argument.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")
    p_2d.is_hydro(0)
    >>> True

    p_2d.is_hydro(1)
    >>> False

Checking stability
------------------
The stability of a (partially) folded Protein is tracked in the *.score*
attribute. This attribute changes dynamically when placing and removing amino
acids.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")
    p_2d.place_amino(1)
    p_2d.score
    >>> 0

    p_2d.place_amino(2)
    p_2d.place_amino(-1)
    p_2d.score
    >>> -1

.. TODO: Add a figure of the fold.

Checking number of changes
--------------------------
In order to compare the efficiency of algorithms, a Protein object also keeps
track of the number of moves performed thus far. This does not include the
removal of amino acids. The current number of performed moves is tracked in the
*.changes* attribute.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")
    p_2d.place_amino(1)
    p_2d.changes
    >>> 1

    p_2d.place_amino(2)
    p_2d.remove_amino()
    p_2d.place_amino(-2)
    p_2d.place_amino(-1)
    p_2d.changes
    >>> 4

Hashing folds
-------------
The current fold of a Protein can be generated via the *.hash_fold()* function.
The function will return the sequence of moves for the current conformation.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")
    p_2d.place_amino(1)
    p_2d.hash_fold()
    >>> [1]

    p_2d.place_amino(2)
    p_2d.place_amino(-1)
    p_2d.hash_fold()
    >>> [1, 2, -1]

Setting folds
-------------
At any time, a Protein's conformation can be set to a given set of moves. This
is done via the *.set_hash(fold_hash)* function, which takes a sequence of moves
as an argument, just like the ones generated by the *.hash_fold()* function.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")
    p_2d.place_amino(2)
    p_2d.place_amino(-1)
    p_2d.hash_fold()
    >>> [2, -1]

    p_2d.set_hash([1, 2, -1])
    p_2d.hash_fold()
    >>> [1, 2, -1]

Resetting Proteins
------------------
Sometimes you might want to reset a Protein object. This can be because you want
to reuse the same Protein object, or because you want to clear the conformation.
Each of these scenarios has their own function.

In order to reset the whole Protein object, use the *.reset()* function.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")
    p_2d.place_amino(1)
    p_2d.place_amino(2)
    p_2d.place_amino(-1)
    p_2d.changes
    >>> 3

    p_2d.hash_fold()
    >>> [1, 2, -1]

    p_2d.reset()
    p_2d.changes
    >>> 0

    p_2d.hash_fold()
    >>> []

Use the *.reset_conformation()* function to only reset the placement of the
amino acids. This includes setting the *.score* to 0, as only the amino acid in
the origin remains in place.

.. code-block:: python

    from prospr import Protein

    p_2d = Protein("HPPH")
    p_2d.place_amino(1)
    p_2d.place_amino(2)
    p_2d.place_amino(-1)
    p_2d.changes
    >>> 3

    p_2d.hash_fold()
    >>> [1, 2, -1]

    p_2d.reset_conformation()
    p_2d.changes
    >>> 3

    p_2d.hash_fold()
    >>> []

Built-in algorithms
-------------------
Prospr offers some algorithms for finding the most optimal conformation of a
Protein. These are included in the C++ core, making them time efficient relative
to Python alternatives. The :doc:`manpages` contain a list of all available
built-in algorithms. They can all easily be used via a direct import, as is
shown below.

.. code-block:: python

    from prospr import Protein, depth_first

    p_2d = Protein("HPPH")
    p_2d = depth_first(p_2d)
    p_2d.score
    >>> 1

    p_2d.hash_fold()
    >> [1, 2, -1]

Visualizing conformations
-------------------------
Visualizing conformations can be key to understanding how the optimal
conformation was found. It also helps illustrating your research. Prospr's
Python package has a built-in visualization module so you do not have to write
your own. Visualizing a conformation can easily be done via the *plot_protein()*
function from the *prospr.visualize* module.

.. code-block:: python

    from prospr import Protein
    from prospr.visualize import plot_protein

    p_2d = Protein("HPPH")
    p_2d.place_amino(1)
    p_2d.place_amino(2)
    p_2d.place_amino(-1)
    plot_protein(p_2d)
    >>>

.. TODO: Give example image of visualization.

Using datasets
--------------
Datasets are valuable for a fair comparison between algorithms. That is why
Prospr's Python package comes with a built-in collection of datasets. Loading a
dataset can easily be done via the available load functions in the
*prospr.datasets* module. Please refer to the :doc:`manpages` for all available
datasets.

.. code-block:: python

    from prospr.datasets import load_vanEck250

    length_10 = load_vanEck250()
    length_15 = load_vanEck250(15)
    length_20 = load_vanEck250(20)
    ...
