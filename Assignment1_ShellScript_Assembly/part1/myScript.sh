#!/bin/bash
# The line above makes your script executable.
# You should write your tutorial in here.
# Include comments inline with your script explaining what is going on.

# You might start out by first saying the purpose of the script and
# demonstrating its usage.

#I wrote a CSV file called "Valuation" which is a list of few tech companies in a table with some informations regarding their size and profitability.
 
#The first column is the list of the companies, the second column is the number of employees, third one is the income, the fourth the income per worker and the last one is the valuation. 

#In my first steep I am going to sort those great companies by income and save the result in a new csv file called FilterByIncome.csv.

#Secondly, I am going to prompt the user for a company and check if that company is in our list. 

#Last, I just printing the "Valuation.csv" file on the terminal. 



#Part one: sorting!

#head: copying the header to the csv file FilterByIncome.

#">": creating a copy of "Valuation.csv" before to work on in on "FilterByIncome.csv".
 
#tail is taking n+2 as a parameter because we are filtering the income which is located on the third column.

#nkr: nkr is reversing the order of any file. Here we are woking on a csv file but it can be on almost any type of file. the "4" following after "nrk" is doing the sorting on the column number 4.

#""": in a CSV file, each data in every lines and column is following that structure: "20,540,000","406,647".So when we are reading each line, we can stop our lecture of the income in a specific line once we reach the """.

#">>": appending the sorting to a new file or create the file if it does not exists yet.
   
head -1 Valuation.csv > FilterByIncome.csv && tail -n+2 Valuation.csv | sort -t '"' -nrk4 >> FilterByIncome.csv



#Part two: reading from user input.

#"read -p": promping for user input and storing the result in the variable "arg1".

#"grep": build-in function that searches the input files for lines that are matching to any given patter. If itfinds any match in a line, it is making a copy the line to standard output.

#"-q": don't write anything to the output, silent mode. 

#Hint for the TA: When you are writing the company name, be careful the first letter is an uppercase.


read -p "What is your name?: " arg1
if grep -q "$arg1" "Valuation.csv"
then
   printf "%s\n" "We got you!"
else
   printf "%s\n" "Sorry, you are not on the list!"
fi


#Part three: printing the current csv file!

#"$": since bash does interpret string literals such as \n, we have to put the "$" before so the string literal can be read in order to create a new line break.

#"read -r -a array": reading the file and declaring a new array.

#"for i in "${array[@]}"": iterate over every elements within the array(column). Here again we are re-using the "$" because we want to access the elements that are stored inside the array.The "@" is the actual element looped in the aray. 

#"$-25%s": the spacing between each columns.  

#"$i": is the current element so the spacing between each elements within the same column should be 25.

#"done": closing the for loop.

#"echo": outputs the strings it is being passed as arguments, here it is going to print every columns and lines.

#"done": closing the while loop.

#"< Valuation.csv": the argument to pass to the while loop.  

 
while IFS=$',\n' read -r -a array; do
    for i in "${array[@]}"; do
        printf "%-1s" "$i"
    done
    echo ""
done < Valuation.csv
