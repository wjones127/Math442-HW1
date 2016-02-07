library(ggplot2)
library(dplyr)

py.bm <- read.csv('./data.csv')
#c.bm <- read.csv('c_benchmark.csv')

py.bm <- py.bm %>% mutate(lang = "python") %>%
  mutate(i = 1:nrow(py.bm))
#c.bm <- c.bm %>% mutate(lang = "c")

#all.bm <- rbind(py.bm, c.bm)

py.bm.plot <- ggplot(py.bm, aes(x = size, y = time, color = i)) +
  geom_point() +
  labs(title = "Comparing Benchmarks",
       x = "# of objects",
       y = "time to execute 1000 iterations (microseconds)") + 
  geom_smooth() + 
  scale_x_log10()

py.bm.plot
