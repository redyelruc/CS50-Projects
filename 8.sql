--list the names of all people who starred in Toy Story.
--output a table with a single column for the name of each person.

SELECT name FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id WHERE title = "Toy Story";