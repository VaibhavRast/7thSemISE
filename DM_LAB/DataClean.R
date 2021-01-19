library(arules)
library(dplyr)

#Load
df<-airquality

#Summary and stats
str(df)
summary(df)

#Remove missing values
df$Ozone=ifelse(is.na(df$Ozone),mean(df$Ozone,na.rm = TRUE),df$Ozone)
df$Solar.R=ifelse(is.na(df$Solar.R),mean(df$Solar.R,na.rm = TRUE),df$Solar.R)
head(df)

#Outlier Removal
subset(df,df$Ozone<83.5)
df$Ozone
df2<-subset(df,df$Ozone<83.5)
boxplot(df2$Ozone)

#Normalize
min_max_norm <- function(x) {
  (x - min(x)) / (max(x) - min(x))
}
df3<- as.data.frame(lapply(df[,0:4], min_max_norm))
head(df3)
df3$Month<-df$Month
df3$Day<-df$Day


#Map
df3$Month=gsub(5,"May",df3$Month)
head(df3)
