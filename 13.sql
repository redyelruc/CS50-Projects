--list the names of all people who starred in a movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.


SELECT name FROM 
(SELECT DISTINCT p.name FROM people p
JOIN stars s ON p.id = s.person_id
WHERE s.movie_id IN
( SELECT m.id FROM movies m 
JOIN stars s ON m.id = s.movie_id
JOIN people p ON s.person_id = p.id 
WHERE p.name = "Kevin Bacon" AND p.birth = 1958)) 
WHERE name != "Kevin Bacon";