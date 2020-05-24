SELECT COUNT(title) from movies WHERE id = (SELECT movie_id FROM ratings WHERE rating = 10.0);
