# Dr Doom

![Dr Doom](doom.jpg "Dr Doom comic")

Consume resources, see what happens.

## Use

### `dr-doom memory-cannon`

Consume as much memory as a single process can. This is achieved by `malloc`ing 4Kb blocks until our process is killed by the kernel. After each `malloc` the memory is
set to zero to ensure the allocation has really occured. 

### `dr-doom fork-bomb`

`fork()` the dr-doom process over and over again in classic [fork bomb](https://en.wikipedia.org/wiki/Fork_bomb) fashion. Each fork allocates and writes 10Mb of memory to
ensure the process is copied and each instance is not using the same page(s) of memory.

### `dr-doom halt-catch-fire`

Create threads for each parallel stream of execution (cores/HT) that your processor supports. Each loop is kept busy resulting in nearly 100% CPU usage. 

### `dr-doom -h | --help`

Print the help.

### `dr-doom -v | --version`

Print the version. 

## Vagrant

If you want to try this out on your own machine. Please use the provided Vagrant configuration (dr-doom should not crash the host machine if used in Vagrant).

```
vagrant up && vagrant ssh
cd /vagrant
dr-doom fork-bomb
```

## Development

`dr-doom` is written in C++. Source files are under `./src`. The executable can be built with `make`. 