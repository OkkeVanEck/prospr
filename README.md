## Prospr: The Protein Structure Prediction Toolbox
![GitHub](https://img.shields.io/github/license/OkkeVanEck/prospr)
![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/OkkeVanEck/prospr?include_prereleases)
![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/OkkeVanEck/prospr/CI-CD/master)
[![Documentation Status](https://readthedocs.org/projects/prospr/badge/?version=latest)](https://prospr.readthedocs.io/en/latest/?badge=latest)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)
**Creator:** Okke van Eck

This project is a universal toolbox for protein structure prediction within the HP-model.
It will contain a datastructure for creating own algorithms, pre-created algorithms, datasets and visualization functions.
Besides folding proteins, this package will also make it possible to determine the relative hardness of a protein for an algorithm.
This allows for a fair comparison across the different algorithms.

So far, only square lattices are supported in n-dimensions.
The amino acids can only be placed in the corners of the squares and have to be one unit away from the previously placed amino acid.

## Installation guide
This package can simply be installed via pip by running:
```bash
pip install prospr
```

## Archives
All the C++ core files and datasets are also available as compressed archives.
See the subsections below for direct links.

### C++ core
All the core code which prospr runs on, is available as a compressed archive.
The folder `archives` contains a [.zip](archives/prospr_core.zip) and
a [.tar.gz](archives/prospr_core.tar.gz) archive.

### Datasets
The complete collection of datasets is available as a compressed archive in the
`archives` folder. It is available as a [.zip](archives/prospr_data.zip) and a
[.tar.tz](archives/prospr_data.tar.gz) archive.

## Example usage
*Work in progress*

## Future work
This toolbox could be used for other protein folding problems within discrete models.
It would be a great extension to support different models by creating a modular amino acid.

## Changelog
*Work in progress*

## License
The used license is the GNU LESSER GENERAL PUBLIC LICENSE.
A copy can be found in the [LICENSE](LICENSE) file on GitHub.
