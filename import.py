# a programme to import a csv file and save the contents to an SQLite database

import csv
from sys import argv, exit
from cs50 import SQL


# check number of command line arguments
if len(argv) != 2:
    print("missing command-line argument")
    exit(1)
    
# open the database
db = SQL("sqlite:///students.db")

# read contents of csv into variable student_list
with open(argv[1]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        full_name = row["name"]
        if len(full_name.split()) == 2:
            first_name = full_name.split(' ', 1)[0]
            last_name = full_name.split(' ', 1)[1]
            middle_name = None
        else:
            first_name = full_name.split(' ', 2)[0]
            middle_name = full_name.split(' ', 2)[1]
            last_name = full_name.split(' ', 2)[2]
        house = row["house"]
        birth = row["birth"]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   first_name, middle_name, last_name, house, birth)
