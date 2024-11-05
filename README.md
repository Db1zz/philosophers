
# Philosophers

A core project for the 42 curriculum focused on concurrent programming, simulating the classic dining philosophers problem. Written in C, this project aims to address synchronization issues in multithreaded environments.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [License](#license)

## Introduction
This project implements a solution to the dining philosophers problem, a well-known synchronization challenge. Philosophers alternately eat, think, and sleep, requiring resource management to avoid deadlocks.

## Features
- Efficient handling of concurrency and threading.
- Bonus version with additional constraints.
- Deadlock prevention strategies.

## Installation
Clone the repository:
```bash
git clone https://github.com/Db1zz/philosophers.git
cd philosophers
make
```

## Usage
Run the program with:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

## Project Structure
- `philo`: Main program source files.
- `philo_bonus`: Extended functionality.

## License
This project is licensed under the MIT License.
