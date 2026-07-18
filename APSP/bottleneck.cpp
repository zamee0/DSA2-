//noise problem and danger raiting problem where shortest path doesnt matter

dist[i][j]=
min(
dist[i][j],
max(dist[i][k],dist[k][j])
);