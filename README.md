*This project has been created as a part of 42 curriculum by <lnakad>*

# Description
    Codexion is a multithreading project in C that simulates coders competing for limited shared resources (USB dongles). Each coder is represented by a thread and must cycle through compiling, debugging, and refactoring, with compiling requiring exclusive access to two dongles.
    The goal is to manage resource sharing safely using mutexes and condition variables, while preventing deadlocks, race conditions, and starvation. The simulation also introduces timing constraints such as burnout deadlines and dongle cooldowns, along with scheduling strategies (FIFO and EDF) to ensure fairness.
    This project focuses on concurrency, synchronization, and precise thread coordination in a time-sensitive environment.


# Instructions
    To compile the project : make (generating executable file ./codexion)
    To execute : ./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
    Other commands:
        make clean    # Remove object files
        make fclean   # Remove object files and executable
        make re       # Recompile everything
    check valgrind: valgrind --leak-check=full ./codexion arguments
    check helgrind: valgrind --tool=helgrind ./codexion arguments


# Resources
    POSIX Threads Programming (pthreads) documentation
    The Open Group Base Specifications (pthread_* functions)
    “The Dining Philosophers Problem” (classic concurrency problem)
    Linux manual pages (man pthread, man gettimeofday)
    Online tutorials on mutexes, condition variables, and thread synchronization


# AI Usage
    AI tools were used to assist with:
        Understanding concurrency concepts and synchronization patterns
        Clarifying the behavior of mutexes, condition variables, and scheduling strategies
        Structuring the project and improving documentation (README writing)


# Blocking Cases Handled
    This project addresses several classic concurrency issues to ensure a correct and fair simulation:
    Deadlock prevention: Deadlocks are avoided by breaking circular waiting using an asymmetric strategy based on coder IDs. Coders with even IDs pick up their right dongle first, while coders with odd IDs pick up their left dongle first. This prevents all coders from holding one dongle while waiting indefinitely for the other, effectively eliminating circular dependency (one of Coffman’s conditions).
    Starvation prevention: With the EDF (Earliest Deadline First) scheduler, coders closest to burnout are prioritized, ensuring that no coder is indefinitely blocked when parameters are feasible.
    Race conditions: Shared resources such as dongles, logging output, and simulation state are protected using mutexes to ensure consistent and predictable behavior.
    Dongle cooldown handling: After being released, each dongle becomes temporarily unavailable. This is enforced through timing checks before allowing it to be acquired again.
    Precise burnout detection: A dedicated monitor thread continuously checks if a coder exceeds time_to_burnout without compiling and reports it within the required timing precision.
    Log serialization: All output messages are protected by a mutex to prevent interleaving and ensure that logs remain readable and correctly ordered.


# Thread Synchronization Mechanisms
    The implementation relies on POSIX thread primitives to coordinate access to shared resources and ensure thread safety:
    pthread_mutex_t:
        Used to protect critical sections:
        Each dongle has its own mutex to prevent simultaneous access.
        A global mutex ensures safe logging (no mixed output).
        Shared simulation state (e.g., burnout flag, counters) is also protected.
    Custom scheduling (FIFO / EDF):
        A priority queue (heap) is used to decide which coder gets access to a dongle:
        FIFO: requests are served in arrival order.
        EDF: priority is based on the nearest burnout deadline.
    Monitor thread:
        A separate thread continuously checks coder states:
        Detects burnout conditions with precise timing.
        Safely communicates termination to all threads via shared flags protected by mutexes.

