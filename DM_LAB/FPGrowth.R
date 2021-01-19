library(rCBA)
library(arules)

data("Adult")
head(Adult)
rules<- rCBA::fpgrowth(Adult,support = 0.01,confidence = 0.2,consequent = "income")
inspect(rules[1:10])
inspect(Groceries[1:10])
plot(rules,method = "graph",max=10)


prunedRules <- rCBA::pruning(Adult, rules, method="m2cba", parallel=FALSE)
