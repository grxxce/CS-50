-- Select the top 5 songs in decreasing length

SELECT name
FROM songs
ORDER BY duration_ms
DESC LIMIT 5;