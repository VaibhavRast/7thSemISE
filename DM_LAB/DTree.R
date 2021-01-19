library(rpart)
library(rpart.plot)
library(e1071)
library(caret)
library(party)

df<-iris

#Test-Train Split
smp_siz=floor(0.75*nrow(df))
smp_siz

set.seed(123)
train_ind=sample(seq_len(nrow(df)),size = smp_siz)

train_set=df[train_ind,]
test_set=df[-train_ind,]

head(train_set)

#Plot DTree
tree1<-rpart(Species~.,train_set,method = "class")
rpart.plot(tree1)


#Model DTree
tree_model<-ctree(Species~.,train_set)
res1<-predict(tree_model,test_set)
res1
#Report
confusionMatrix(res1,test_set$Species)

#Model NaiveBayes
nb_model<-naiveBayes(Species~.,train_set)
print(nb_model)

res2<-predict(nb_model,test_set)
res2

#Report
confusionMatrix(res2,test_set$Species)
