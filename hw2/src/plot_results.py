#!/usr/bin/env python
import matplotlib.pyplot as plt
try:
    import pandas as pd
except ModuleNotFoundError:
    raise ModuleNotFoundError("This script require pandas to work")
import sys

output_file = False
if len(sys.argv) == 2:
  pass
elif len(sys.argv) == 3:
  output_file = sys.argv[2]
else:
  sys.exit("plot_results.py <file_to_plot> <output_file OPTIONAL>")

def plot_results(my_df, output_file):
    fig = plt.figure()
    axe = fig.add_subplot(1, 1, 1)

    x = my_df['x'].values
    numerical = my_df['Numerical'].values

    axe.plot(x, numerical, marker='o', label='Numerical')

    if "Analytic" in my_df:
        analytic = my_df["Analytic"].values
        axe.plot(x, analytic, label='Analytical')

    axe.set_xlabel(r'$k$')
    axe.set_ylabel(r'Series')
    axe.legend()
    if output_file:
        plt.savefig(output_file)
    else:
        plt.show()

filename = sys.argv[1]
file_ending=filename.split('.')[-1]
if file_ending == "txt":
    sep="\s+"
elif file_ending == "csv":
    sep=","
elif file_ending == "psv":
    sep="|"
else:
    raise Exception("Can not parse this filetype")

my_df = pd.read_csv(filename, sep=sep, engine='python', header=None)

if len(my_df.columns) == 3:
    columns = ["x", "Numerical", "diff"]
elif len(my_df.columns) == 4:
    columns = ["x", "Numerical", "diff", "Analytic"]
else:
    raise Exception("Could not parse file, check if format matches"
                    " the extension!")
my_df.columns = columns


plt = plot_results(my_df, output_file)
