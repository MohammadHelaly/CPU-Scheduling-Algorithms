# CPU-Scheduling-Algorithms
Implementation and representation of different CPU Scheduling Algorithms using C++.
- First Come First Serve (FCFS)
   - Non-preemptive scheduling algorithm. It executes processes in the order they arrive in the ready queue. This means that the process which arrives first in the queue gets executed first. FCFS is a simple and easy-to-implement scheduling algorithm but can lead to poor average waiting times and response times, especially when long processes arrive first in the queue.
- Round Robin (adjustable time quantum) (RR-i)
   - Preemptive scheduling algorithm in which each process is given a fixed time quantum or time slice to execute, and after the time quantum expires, the CPU is given to the next process in the queue. The time quantum is an adjustable parameter that can be changed to balance the trade-off between the response time and the throughput. RR is commonly used in multi-user systems, such as time-sharing systems, where fairness and responsiveness are crucial.
- Shortest Process Next (SPN)
   - Scheduling algorithm that selects the process with the smallest execution time from the pool of available processes. This algorithm reduces the average waiting time and turnaround time compared to other scheduling algorithms because it prioritizes short jobs. However, it may cause starvation for long-running processes since they have to wait for the completion of short processes.
- Shortest Remaining Time (SRT)
   - Pre-emptive scheduling algorithm that selects the process with the shortest remaining burst time to execute next. It is a dynamic algorithm that continuously updates the estimated remaining time of each process and chooses the one with the shortest estimated time. This results in a shorter average waiting time and turnaround time compared to other scheduling algorithms like FCFS and Round Robin. However, this algorithm may suffer from starvation if a process with a very short burst time keeps arriving before other longer processes.
- Highest Response Ratio Next (HRRN)
   - Scheduling algorithm that considers both the length of a process and the amount of time it has been waiting to run. It calculates the response ratio for each process and then selects the one with the highest ratio to run next. This approach ensures that shorter processes are given priority while still considering the waiting time of each process. The HRRN algorithm is non-preemptive, meaning that once a process starts running, it will continue until it completes or blocks.
- Feedback (FB)
   - Dynamic scheduling algorithm that uses multiple queues with different priorities. Each queue is assigned a time quantum, and processes are scheduled in the highest priority queue first. If a process in a lower priority queue exceeds its time quantum, it is moved to the next higher priority queue. This algorithm helps ensure that shorter processes get executed faster and longer processes don't monopolize the CPU for too long. The feedback scheduling algorithm is often used in real-time systems where response time is critical.
- Feedback (adjustable time quantum) (FB2i)
   - Improvement over the basic Feedback (FB) algorithm. It uses multiple queues with varying time quantum values for each queue. The processes are initially placed in the first queue, and if they exceed the time quantum allotted for that queue, they are moved to the next queue. This process is repeated until the process completes or the highest numbered queue is reached. FB2i scheduling algorithm provides better response time than FB algorithm because it allows shorter time quantum values for higher priority processes.
- Aging
   - Scheduling algorithm that is used to prevent starvation in other scheduling algorithms. It works by gradually increasing the priority of a process as it waits in the ready queue for a long time, thus preventing low priority processes from being blocked indefinitely. The longer a process waits in the ready queue, the higher its priority becomes, ensuring that it will eventually be executed. This technique is commonly used in multi-level feedback queue scheduling algorithms.
## Input format:
 See [test cases](./testcases/) folder for input format.   
## Outputs:
 Depending on input, the program will either output a Gnatt chart visual representation of the scheduling algorithm's results on the input processes, or it will output the resulting stats for the processes.
## Contributors:
 - [Mohamed Battawy](https://github.com/MohamedBattawy)
 - [Mohammad Helaly](https://github.com/MohammadHelaly)  