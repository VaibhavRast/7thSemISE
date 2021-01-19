data<-iris

#Scatter Plot
plot(data,col="blue")

#Scatter Plot Sepal Length vs Sepal Width 
plot(data$Sepal.Width,data$Sepal.Length,col="red")

# Histogram
hist(data$Sepal.Width,col="green")

#Feature plot for each class
install.packages("caret")
library(caret)
boxplot(iris$Sepal.Length,horizontal = TRUE)

pie(table(iris$Species),main="No of species")
barplot(table(iris$Sepal.Length),col="green")
