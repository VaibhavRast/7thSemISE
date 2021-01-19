library("fpc")
set.seed(120)
data<-iris
data$Species<-NULL

db_model=dbscan(data,showplot = TRUE,eps = 0.45)
db_model$cluster
table(db_model$cluster,iris$Species)
plot(db_model,data,main = "Dbs")

plot(db_model,data$Sepal.Length,main = "Petal Width vs Sepal Length")
