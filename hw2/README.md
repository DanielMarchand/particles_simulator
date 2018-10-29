Majority of the code was written in pair-programming style, (add wiki link), with the driver and navigator marked in the git commit.

Final aspects of the writer was handled by Daniel and final aspects of the dumper was handled by Ali.


1) Clone the repository from C4Science to $SP4E_HW
2) cd into $SP4E_HW/hw2
3) compile the hw2_program (from the $SP4E_HW/hw2 directory)
$mkdir build && cd build && ccmake .. && make
4) from the build directory the hw2_program may be run as:
$./src/main <series_type> <dumper_type> max_iter freq <filepath optional> 

For the series_type there are two options:
  algebraic: computes sum over N
  pi: computes an approximation for pi 

For dumper_type there are two options:
  print: prints the output to the screen
  write: writes the output to <filepath>, which defaults to my_file.txt in the build directory
         the file type will be determined by extension:
         txt " " seperation, csv "," seperation, psv "|" seperation
         
max_iter: gives the maximum number of iterations

freq: gives the frequency of the output

filepath determines the output file, see write option under dumper_type

5) The results may be plotted using the "plot_results.py" script, 
   located at $SP4E_HW/hw2/src/plot_results.py

$plot_results.py <input_file> <output_file optional>

input_file: the input file to be plotted, only txt, csv and psv supported
            which was produced earlier by the hw2_program 
output_file: the path to an output file containing a plot of the data, 
             if left unspecified, plots results to screen
           
The "Naive" Algorithm for calculation of the sereis would have N*N complexity. However,
The finally algorithm which uses the members current_values & current_index helps us to enjoy complexity of order N.
In the case of summing up the terms reversely, the complexity is not effected merely the order of the operations
