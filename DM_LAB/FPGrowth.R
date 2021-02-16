library(rCBA)
library(arules)

df <- read_csv("C:/Users/Vaibhav Rastogi/Downloads/Grocery.csv")
df<-as(df,"transactions")


rules<-rCBA::fpgrowth(df,consequent = "Item5",support = 0.4,confidence = 0.6)
inspect(rules)
prune<-rCBA::pruning(df,rules)
inspect(prune)

rules
rules1<-setdiff(prune,rules)
inspect(rules1)

data("Adult")
inspect(Adult[1:10])
