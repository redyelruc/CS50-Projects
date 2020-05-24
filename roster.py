# TODO

import csv
from sys import argv, exit
from cs50 import SQL

# check number of command line arguments
if len(argv) != 2:
    print("missing command-line argument")
    exit(1)

house_name = argv[1]
db = SQL("sqlite:///students.db")
dictionary = db.execute("SELECT first, middle, last, birth FROM students WHERE students.house = ? ORDER BY last", house_name)
for row in range(len(dictionary)):
    print(dictionary[row]["first"], end=" ")
    if dictionary[row]["middle"] != None:
        print(dictionary[row]["middle"], end=" ")
    print(f"{dictionary[row]['last']}, born {dictionary[row]['birth']}")

