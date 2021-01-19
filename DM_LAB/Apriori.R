library(arules)
library(arulesViz)

data("Groceries")

itemSets<-apriori(Groceries,parameter = list(supp=0.01,conf=0.2,target="frequent itemsets"))
inspect(sort(itemSets,by="support"))

rules<-apriori(Groceries,parameter = list(supp=0.01,conf=0.2))
inspect(rules[1:10])

library(RColorBrewer)
arules::itemFrequencyPlot(Groceries, topN = 20,  
                          col = brewer.pal(8, 'Pastel2'), 
                          main = 'Relative Item Frequency Plot', 
                          type = "relative", 
                          ylab = "Item Frequency (Relative)")
plot(rules,method = "graph",max=3)
