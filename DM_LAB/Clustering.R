
library(factoextra)

data <- iris
data$Species <- NULL

distance1 <- scale(dist(data,method="euclidian"))
kModel <- kmeans(distance1,3)
fviz_cluster(kModel, data, geom="point")
print(kModel.res)
head(data)

distance2 <- dist(data[,3:4],method="euclidian")
hModel <- hclust(distance2,method="average")
plot(hModel)

data2<-mtcars
distance3 <- dist(data2,method="euclidian")
hModel2 <- hclust(distance3,method="average")
plot(hModel2)

abline(h=110,col="green")
fit<-cutree(hModel2,k=3)
table(fit)
rect.hclust(hModel2,k=3,border = "red")
