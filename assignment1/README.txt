Group number 10: Jacob Jones 2831078, Steve Charles 2850400
Contribution: Jacob:55% Steve:45%

Design Ideas: Our initial idea was to fork at the begining and have the child process do a majority of the work. The child is in charge of getting the user input and a series of logical gates in order to navigate the state of the program. The parent just waits for the child process to quit or finish executing.

Compile instructions: running "make" in the directory with the "makefile" will compile the program correctly. 

Run instruction: running "./myShell" in the directory will execute the program 

Sample test (running cd): 
Prompts the user for input:
/home/blueman/Documents/dev/c/CIS345/assignment1$

Running cd with the .. directory (which moves back a directoy):
/home/blueman/Documents/dev/c/CIS345/assignment1$cd ..

After running cd: 
/home/blueman/Documents/dev/c/CIS345/

Bugs and Missing Compenents:
Redirection doesn't work if you are trying to do input and output at the same time. The program works if you change the input, the program works if you change the output, but the program does not recognize if you do both. 

EXAMPLE: 
ls < input.txt > output.txt
