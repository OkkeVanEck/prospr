#!/usr/bin/env python3
"""
File:           visualize.py
Description:    This file contains functions for visualizing a Protein
                instance.
License:        This file is licensed under the GNU LGPL V3 license by
                Okke van Eck (2020 - 2022). See the LICENSE file for the
                specifics.
"""

from .helpers import get_ordered_positions, get_scoring_pairs

from matplotlib import pyplot as plt
from matplotlib.ticker import MaxNLocator
from matplotlib.lines import Line2D
import seaborn as sns
import pandas as pd


def _plot_aminos_2d_basic(protein, df, ax):
    """
    Plot amino acids in basic style in a 2D figure.
    :param Protein      protein:    Protein object to plot the hash of.
    :param DataFrame    df:         DataFrame with all ordered positions.
    :param Axes         ax:         Axis to plot on.
    """
    ax.plot(df["x"], df["y"], color="black", alpha=0.65, zorder=1)
    sns.scatterplot(
        x="x",
        y="y",
        data=df,
        hue="Type",
        hue_order=["H", "P"],
        style="Type",
        markers={"H": "o", "P": "s"},
        palette={"H": "royalblue", "P": "orange"},
        s=80,
        zorder=2,
        ax=ax,
    )

    # Plot dotted lines between the aminos that increase the stability.
    pairs = get_scoring_pairs(protein)

    for pos1, pos2 in pairs:
        ax.plot(
            [pos1[0], pos2[0]],
            [pos1[1], pos2[1]],
            linestyle=":",
            color="indianred",
            alpha=0.9,
            zorder=1,
            lw=1.5,
        )


def _plot_aminos_2d_paper(protein, df, ax):
    """
    Plot amino acids in basic style in a 2D figure.
    :param Protein      protein:    Protein object to plot the hash of.
    :param DataFrame    df:         DataFrame with all ordered positions.
    :param Axes         ax:         Axis to plot on.
    """
    # Split dataframe on amino acid type.
    df_H = df.loc[df["Type"] == "H"]
    df_P = df.loc[df["Type"] == "P"]

    ax.plot(df["x"], df["y"], color="black", alpha=0.65, zorder=1)
    sns.scatterplot(
        x="x",
        y="y",
        data=df_H,
        marker="o",
        edgecolor="royalblue",
        s=80,
        zorder=2,
        ax=ax,
    )
    sns.scatterplot(
        x="x",
        y="y",
        data=df_P,
        marker="o",
        facecolor='white',
        edgecolor="orange",
        linewidth=2,
        s=80,
        zorder=2,
        ax=ax,
    )

    # Plot dotted lines between the aminos that increase the stability.
    pairs = get_scoring_pairs(protein)

    for pos1, pos2 in pairs:
        ax.plot(
            [pos1[0], pos2[0]],
            [pos1[1], pos2[1]],
            linestyle=":",
            color="indianred",
            alpha=0.9,
            zorder=1,
            lw=1.5,
        )

    ax.axis('off')


def _plot_protein_2d(protein, style, ax):
    """
    :param Protein      protein:    Protein object to plot the hash of.
    :param [str]        style:      What style to plot the proteins in.
    :param Axes         ax:         Axis to plot Protein on.

    """
    # Setup dataframe containing the data and set types for the coordinates.
    df = pd.DataFrame(
        get_ordered_positions(protein), columns=["x", "y", "Type"]
    )
    df = df.astype({"x": "int32", "y": "int32"})

    # Plot amino acids in the selected style.
    if style == "paper":
        _plot_aminos_2d_paper(protein, df, ax)
    else:
        ax.set_title(f"2D conformation with {protein.score} energy")
        _plot_aminos_2d_basic(protein, df, ax)

    # Set axis labels.
    ax.set_xlabel("x-axis", fontsize=13)
    ax.set_ylabel("y-axis", fontsize=13)
    ax.xaxis.set_major_locator(MaxNLocator(integer=True))
    ax.yaxis.set_major_locator(MaxNLocator(integer=True))

    # Remove title from legend and add item for bonds.
    handles, labels = ax.get_legend_handles_labels()
    score_patch = Line2D(
        [],
        [],
        color="indianred",
        linestyle=":",
        alpha=0.9,
        label="Bond",
        lw=1.5,
    )
    handles.append(score_patch)
    labels.append(score_patch.get_label())
    ax.legend(handles=handles, labels=labels)


def _plot_aminos_3d_basic(protein, df, ax):
    """
    Plot amino acids in basic style in a 3D figure.
    :param Protein      protein:    Protein object to plot the hash of.
    :param DataFrame    df:         DataFrame with all ordered positions.
    :param Axes         ax:         Axis to plot on.
    """
    # Split dataframe on amino acid type.
    df_H = df.loc[df["Type"] == "H"]
    df_P = df.loc[df["Type"] == "P"]

    # Plot the aminos connected with an opaque line.
    ax.scatter(
        df_H["x"],
        df_H["y"],
        df_H["z"],
        c="royalblue",
        marker="o",
        depthshade=False,
        s=60,
        label="H",
    )
    ax.scatter(
        df_P["x"],
        df_P["y"],
        df_P["z"],
        c="orange",
        marker="s",
        depthshade=False,
        s=60,
        label="P",
    )
    ax.plot(df["x"], df["y"], df["z"], color="black", alpha=0.65, zorder=1)

    # Plot dotted lines between the aminos that increase the stability.
    pairs = get_scoring_pairs(protein)

    for pos1, pos2 in pairs:
        ax.plot(
            [pos1[0], pos2[0]],
            [pos1[1], pos2[1]],
            [pos1[2], pos2[2]],
            linestyle=":",
            color="indianred",
            alpha=0.9,
            zorder=1,
            lw=1.5,
        )


def _plot_aminos_3d_paper(protein, df, ax):
    """
    Plot amino acids in basic style in a 3D figure.
    :param Protein      protein:    Protein object to plot the hash of.
    :param DataFrame    df:         DataFrame with all ordered positions.
    :param Axes         ax:         Axis to plot on.
    """
    # Split dataframe on amino acid type.
    df_H = df.loc[df["Type"] == "H"]
    df_P = df.loc[df["Type"] == "P"]

    # Plot the aminos connected with an opaque line.
    ax.scatter(
        df_H["x"],
        df_H["y"],
        df_H["z"],
        c="royalblue",
        marker="o",
        depthshade=False,
        s=60,
        label="H",
    )
    ax.scatter(
        df_P["x"],
        df_P["y"],
        df_P["z"],
        c="orange",
        marker="s",
        depthshade=False,
        s=60,
        label="P",
    )
    ax.plot(df["x"], df["y"], df["z"], color="black", alpha=0.65, zorder=1)

    # Plot dotted lines between the aminos that increase the stability.
    pairs = get_scoring_pairs(protein)

    for pos1, pos2 in pairs:
        ax.plot(
            [pos1[0], pos2[0]],
            [pos1[1], pos2[1]],
            [pos1[2], pos2[2]],
            linestyle=":",
            color="indianred",
            alpha=0.9,
            zorder=1,
            lw=1.5,
        )


def _plot_protein_3d(protein, style, ax):
    """
    :param Protein      protein:    Protein object to plot the hash of.
    :param [str]        style:      What style to plot the proteins in.
    :param Axes         ax:         Axis to plot Protein on.
    """
    # Setup dataframe containing the data and set types for the coordinates.
    df = pd.DataFrame(
        get_ordered_positions(protein), columns=["x", "y", "z", "Type"]
    )
    df = df.astype({"x": "int32", "y": "int32", "z": "int32"})

    # Plot amino acids in the selected style.
    if style == "paper":
        _plot_aminos_3d_paper(protein, df, ax)
    else:
        _plot_aminos_3d_basic(protein, df, ax)

    # Set axis labels and tics.
    ax.set_title(f"3D conformation with {protein.score} energy")
    ax.set_xlabel("x-axis", fontsize=13)
    ax.set_ylabel("y-axis", fontsize=13)
    ax.set_zlabel("z-axis", fontsize=13)
    ax.xaxis.set_major_locator(MaxNLocator(integer=True))
    ax.yaxis.set_major_locator(MaxNLocator(integer=True))
    ax.zaxis.set_major_locator(MaxNLocator(integer=True))

    # Remove title from legend and add item for bonds.
    handles, labels = ax.get_legend_handles_labels()
    score_patch = Line2D(
        [],
        [],
        color="indianred",
        linestyle=":",
        alpha=0.9,
        label="Bond",
        lw=1.5,
    )
    handles.append(score_patch)
    labels.append(score_patch.get_label())
    ax.legend(handles=handles, labels=labels)


def plot_protein(protein, style="basic", ax=None):
    """
    Plot conformation of a protein.
    :param Protein      protein:    Protein object to plot the hash of.
    :param [str]        style:      What style to plot the proteins in.
    :param Axes         ax:         Axis to plot Protein on.
    """
    if ax is None:
        if style == "paper":
            fig = plt.figure(figsize=(2,2))
        else:
            fig = plt.figure(figsize=(5,6))
            sns.set_style("whitegrid")

    # Plot data according to used dimension.
    if protein.dim == 2:
        if ax is None:
            ax = fig.gca()
        _plot_protein_2d(protein, style, ax)
    elif protein.dim == 3:
        if ax is None:
            ax = fig.gca(projection="3d")
        _plot_protein_3d(protein, style, ax)
    else:
        raise RuntimeError(
            f"Cannot plot the structure of a protein with "
            f"dimension '{protein.dim}'"
        )

    plt.show()
