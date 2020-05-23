# a program that identifies to whom a sequence of DNA belongs
# written for CS50x pset 6

from sys import argv, exit
import csv

# check number of command line arguments
if len(argv) != 3:
    print("missing command-line argument")
    exit(1)
    
# read contents of csv into variable dna_list
with open(argv[1]) as csv_file:
    reader = csv.reader(csv_file)
    dna_list = list(reader)
 
# read contents of the text file into variable str_sequence   
f = open(argv[2], "r")
str_sequence = (f.read())
genomes = []

# make list of occurences of each pattern from the header row of the dna_list
for column in range(len(dna_list[0])):
    pattern = dna_list[0][column]
    length_of_pattern = len(pattern)
    consequetives = 0
    record = 0
    # find dirst occurence
    starts_at = str_sequence.find(pattern)
    # if found
    if starts_at != -1:
        consequetives = 1
        record = 1
        starts_at += length_of_pattern
        # loop through rest of string
        while starts_at <= len(str_sequence):
            if str_sequence[starts_at:starts_at + length_of_pattern] == pattern:
                consequetives += 1
                starts_at += length_of_pattern
                if consequetives > record:
                    record = consequetives
            else:
                consequetives = 0
                # search for new beginning
                starts_at = str_sequence.find(pattern, starts_at + length_of_pattern)
                # if not found
                if starts_at == -1:
                    break
    genomes.append(str(record))

match = False
for row in range(len(dna_list)):
    if genomes[1:] == dna_list[row][1:]:
        print(dna_list[row][0])
        match = True
    
if not match:
    print("No match")