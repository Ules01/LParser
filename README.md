# LParser
Create an automate, which is able to search words in a string, from a regex 

# Graphe
A class to create and to use the automate associated to the regex
Can be draw

# Regex special character
*  () -> Specify a sub bloc of regex
*  \+ -> is the or symbol
*  \* -> means the char or the block before can be repeated as much as we want or never
*  ! -> means the char or the block before can be repeated as much as we want but at least one time
*  ? -> the char before can be put one or 0 time
*  $ -> means the end of the regex. It automaticly put one at the end of the string
*  . -> represent all of the character

# Struct of the project
There is folder Cpp and Python. Both o them contain the lparser class, one is write in cpp the other in python.
The python contain a show method wich will draw you the graph using matplotlib.
The cpp one is more reliable and contain the export_graphivz which will print in the terminal the graphivz in format.
If you just want to draw some graph you can just use the draw.sh script as:
* ./draw.sh your_regexp_with_no_space_inside

Be aware that the draw.sh script and the show python method only waork on linux ubuntu.
The rest of the functionality work in other systems.

# draw.sh rules
* "Rebuild" or "-rb" will force to rebuild all the project.
* "clean" delete the generated files but do not delete the latest graph picture.
* Rest of strings will be interpreted as a regex. You can put different regexp at the same time. It will generate them one by one.
* If no argument is pass it will print the last graph.

# Futher informations
The parser used on the regex is a LL(1).
