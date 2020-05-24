-- --list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.

SELECT a.title FROM 
(SELECT title FROM movies m
JOIN stars s ON m.id = s.movie_id 
JOIN people p ON s.person_id = p.id 
WHERE p.name = "Johnny Depp") a 
INNER JOIN
(SELECT title FROM movies m
JOIN stars s ON m.id = s.movie_id 
JOIN people p ON s.person_id = p.id 
WHERE p.name = "Helena Bonham Carter")  b 
ON a.title = b.title;
