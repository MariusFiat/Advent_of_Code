f = open("input.txt", "r");

floor = 0; #* Initialize the floor counter with 0 */
ch = f.read(1); #Read the next character from the file;
firstChar = False;
indexFirstChar = 1;

while (ch):         #* While the file still have characters, read the next one;
    if(ch == '('):  # If ch is (, the floor is upper
        floor += 1;
    else:           # Else, counter must be decreased by one;
        floor -= 1; 
    ch = f.read(1);

    if(firstChar == False):
       if(floor == -1):
        print("FirstChar to basement: " + str(ch) + " position: " + str(indexFirstChar));
        firstChar = True;

    indexFirstChar += 1;

print("The floor is: " + str(floor));