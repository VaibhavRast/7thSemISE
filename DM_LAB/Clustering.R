#Kmeans
library(factoextra)

data <- iris
data$Species <- NULL

distance1 <- scale(dist(data,method="euclidian"))
kModel <- kmeans(distance1,3)
fviz_cluster(kModel, data, geom="point")
print(kModel.res)
head(data)


#Selecting 20 data points for k means clustering
set.seed(123)
index=sample(seq_len(nrow(data)),size = 20)
df=data[index,] #Dataset with 20 points

distance2 <- scale(dist(df,method="euclidian"))
kModel2 <- kmeans(distance2,3)
print(kModel2)
fviz_cluster(kModel2,df,check.names=TRUE)

# Hierarchial Clustering(Not Required)
distance2 <- dist(data[,3:4],method="euclidian")
hModel <- hclust(distance2,method="average")
plot(hModel)

