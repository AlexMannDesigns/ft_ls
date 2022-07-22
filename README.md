# ft_ls

One of the best ways to understand how a program works is to reverse engineer it and then build your own version of it. So that's exactly what I did with the unix ls program. As a side effect, I also learned a lot about how file systems are organised in unix systems, how "read write execute" permissions and other file metadata works and sorting algorithms.

"ls" is used as a command line interface facility, allowing the user to print the contents of the current working directory. For more information 'man ls' on macOS or Linux will provide a detailed overview.

Speaking of Linux, this program was built on a Mac system, and runs best in that environment.

To compile the program, run 'make' in the root directory and the makefile will take care of everything. You can then simply run './ft_ls', to execute the program. Observe:

<img width="965" alt="Screen Shot 2022-07-22 at 11 48 18 AM" src="https://user-images.githubusercontent.com/69106035/180401583-c7a3ca33-6981-4fd7-9a7f-b68ca581ded8.png">

As you can see, the contents of the directory are displayed in neat columns. These will be adjusted to fit the terminal window each time the program runs.

The following flags have also been handled:

```
-1 : output one entry per line
-a : include directory entries whose name begins with a dot (.)
-l : list in long format
-m : Output will be listed across the screen, separated by commas (,)
-n : display user and group id's numerically, rather than converting to their names. Also turns on the -l option
-R : Print the contents of the directory, then all other subdirectories, recursively
-r : Reverse the order of the sorting
-t : Sort by time modified, most recent first
```

Anything else passed as argument, or after the flags, will be interpretted as the directory or file that you want ls to display, just like the original program:

<img width="965" alt="Screen Shot 2022-07-22 at 12 05 51 PM" src="https://user-images.githubusercontent.com/69106035/180405041-e373dbe4-df3c-476e-ba2c-3d02a429a4d8.png">

