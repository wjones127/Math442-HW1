library(ggplot2)
library(dplyr)

# Read python data from file `python-data.csv`
py.bm <- read.csv('./data.csv') %>%
    mutate(lang = "python") %>%
    mutate(i = 1:nrow(py.bm))

# Read c data from files `c-o0.csv`, `c-o1.csv`, `c-o2.csv`, `c-o3.csv`
# Each file should correspond to optimization level
c.0 <- read.csv('./c-o0.csv') %>%
    mutate(optim.level = "0")
c.1 <- read.csv('./c-o1.csv') %>%
    mutate(optim.level = "1")
c.2 <- read.csv('./c-o2.csv') %>%
    mutate(optim.level = "2")
c.3 <- read.csv('./c-o3.csv') %>%
    mutate(optim.level = "3")
c.fast <- read.csv('./c-ofast.csv') %>%
  mutate(optim.level = "fast")
c.bm <- rbind(c.0, c.1, c.2, c.3, c.fast) %>%
    mutate(lang = "c",
           optim.level = as.factor(optim.level)) %>%
  filter(iter == 5000)

# Also load c code with double
c.dbl <- read.csv('./double.csv') %>%
  mutate(optim.level="fast",
         type="double")
c.type <- c.fast %>%
  mutate(type="float") %>%
  rbind(c.dbl) %>%
  mutate(type=as.factor(type)) %>%
  filter(iter == 5000)

# Read asm data
asm.bm <- read.csv('./asm.csv') %>%
    mutate(lang = "asm")

# Combine datasets
all.bm <- c.bm %>% remove(optim.level) %>%
    rbind(py.bm, asm.bm)


# Plot for just python
py.bm.plot <- ggplot(py.bm, aes(x = size, y = time, color = i)) +
  geom_point() +
  labs(title = "Comparing Benchmarks",
       x = "# of objects",
       y = "time to execute 1000 iterations (microseconds)") + 
  geom_smooth() + 
  scale_x_log10()

py.bm.plot
ggsave(filename="python.png")

# Plot for different C optimizations
c.optim.plot <- ggplot(c.bm, aes(x = jitter(size), y = time, color = optim.level)) +
    labs(title="Runtimes for Different C Optimization Levels",
         x = "# of objects",
         y = "time to execute 1000 iterations (microseconds)") +
    geom_smooth(alpha = 0.2) +
    geom_point() +
    scale_x_log10()

c.optim.plot
ggsave(filename="c_optimizations.png")

# Plot for float and double
ggplot(c.type, aes(x = jitter(size), y = time, color = type)) +
  geom_point() +
  labs(title="Runtimes for Float and Double Implementation",
       x = "# of objects",
       y = "time to execute 1000 iterations (microseconds)") +
  geom_smooth(alpha = 0.2) +
  scale_x_log10()
ggsave(filename="c_type.png")

# Plot with pyhton, C, and asm
lang.plot <- ggplot(all.bm, aes(x = size, y = time, color = lang)) +
    geom_point() +
    labs(title = "Runtimes for different Languages",
         x = "# of objects",
         y = "time to execute 1000 iterations (microseconds)") +
    geom_smooth() +
    scale_x_log10()

lang.plot
ggsave(filename="lang_comparison.png")
