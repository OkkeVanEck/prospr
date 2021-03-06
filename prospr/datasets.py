#!/usr/bin/env python3
"""
File:           vanEck.py
Description:    This file contains functions for loading datasets.
"""

import pkg_resources
import pandas as pd


def _load_dataset(folder, filename):
    """Returns a specified dataset as a dataframe."""
    stream = pkg_resources.resource_stream(
        "prospr", f"data/{folder}/{filename}"
    )
    return pd.read_csv(stream)


def load_vanEck250(length=10):
    """Returns a vanEck250 dataset as a pandas dataframe."""
    return _load_dataset("vanEck250", f"HP{length}.csv")


def load_vanEck1000(length=10):
    """Returns a vanEck250 dataset as a pandas dataframe."""
    return _load_dataset("vanEck1000", f"HP{length}.csv")
