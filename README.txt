This is a very basic C++ program illustrating how to use a genetic algorithm to 
solve the Eight Queens problem.  

Each state of the board is a string of digits.  Each digit is the row the queen
is in.  So "18514376" becomes:

  12345678
1 Q--Q----
2 --------
3 -----Q--
4 ----Q---
5 --Q-----
6 -------Q
7 ------Q-
8 -Q------

States are randomly created with the only assumption that one queen is in one
column.  

The fitness test is the total number of attacks a queen can make minus a perfect
score where no queen can attack any other queen which is a score of 28.  Note: 
we do not count double dipping.  For example: if q1 can attack q2, that counts 
as one attack.  We do not include the fact that q2 can attack q1.

Using the above example of state "18514376" we have a fitness score of
28 - 5 = 23.  The 5 comes from the following attacks (row, column): 

(1,1)->(1,4)
(5,4)->(6,3)
(7,7)->(8,6)
(1,1)->(7,7)
(1,4)->(6,3)

We have a collection of, say 20, organisms (states of the board).  We then select
the best of these organisms by selecting 10 organisms with the best fitness
score.  We mate them by randomly mix-matching the first 4 genes of an organism
with the last 4 genes of another organism.  

For example, s1="12345678" and s2="66557432".  This gives us:

frontGenes(s1)="1234", backGenes(s1)="5678"
frontGenes(s2)="6655", backGenes(s2)="7432"

To mate s1 with s2 we create two new child states:

s3 = frontGenes(s1) + backGenes(s2) = "12347432" 
s4 = frontGenes(s2) + backGenes(s1) = "66555678".

Finally, we randomly mutate one random gene in each organism.  That is, move
one queen in each state to another random row.  For example: s3="12347432".  
After mutating we have s3="15347432"  The "2" in position 2 is now a "5".

Then we check the fitness number of each new child.  If we find a solution (a
score of 28) we halt the program.  Otherwise, we continue to a specified number
of generations.

TODO:
1) Separate out main.cpp into more files with a makefile.
2) Allow a user to define a function.  Send it by a function pointer?
3) Nicer graphic output for a solution.
4) Allow command line parameters for maxPopulation and maxGeneration.
