library(rpart)
library(rpart.plot)
library(e1071)
library(caret)
library(party)
library(ipred)

df<-iris

#Test-Train Split
smp_siz=floor(0.75*nrow(df))
smp_siz

set.seed(123)
train_ind=sample(seq_len(nrow(df)),size = smp_siz)

train_set=df[train_ind,]
test_set=df[-train_ind,]

head(train_set)

#Bagging Model
bag_model<-bagging(Species ~.,data=train_set,coob=TRUE)
print(bag_model)

res<-predict(bag_model,test_set)
res

confusionMatrix(res,test_set$Species)
