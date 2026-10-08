# Philosophers

Implementation of the Dining Philosophers problem in C.

The program creates one thread for each philosopher and uses mutexes to control access to the forks and shared data.

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

For example:

```bash
./philo 5 800 200 200
```

## Main points

* One POSIX thread per philosopher
* Mutexes for fork access
* Synchronization of shared state
* Monitoring philosophers to detect deaths
* Handling the case of a single philosopher
* Optional limit on the number of meals

The program also keeps track of the time of the last meal of each philosopher and stops when a philosopher dies or all required meals have been completed.

## Build

```bash
make
```

Available targets:

```bash
make
make clean
make fclean
make re
```

## Technologies

* C
* POSIX threads
* Mutexes
* Time management
* Make
