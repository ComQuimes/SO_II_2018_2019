#This creates the .exe of the reverse integer sort function
gcc reverse_integers.c -o reverse_integers -lm 
#This creates the .exe of the float sort function
gcc sorted_floats.c -o sorted_floats -lm 
#This creates the .exe of the double sort function
gcc sorted_doubles.c -o sorted_doubles -lm 
#This creates the .exe of the strings by length sort function
gcc sorted_by_len_strings.c -o sorted__by_len_strings -lm
#This creates the .exe of the strings by value sort function
gcc sorted_by_ascii_strings.c -o sorted_by_ascii_strings -lm  