
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;


struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int startTime = -1;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};


vector<Process> generateProcesses(int n) {
    vector<Process> processes;
    srand(time(0));
    for (int i = 0; i < n; i++) {
        Process p;
        p.id = i + 1;
        p.arrivalTime = rand() % 10;  (0-9)
        p.burstTime = rand() % 10 + 1; (1-10)
        p.priority = rand() % 5 + 1;  (1-5)
        p.remainingTime = p.burstTime;
        processes.push_back(p);
    }
    return processes;
}


void shortestJobFirst(vector<Process> processes) {
    cout << "\nShortest Job First (SJF) Scheduling:\n";
    vector<Process*> readyQueue;
    int time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed < n) {
     
        for (auto& p : processes) {
            if (p.arrivalTime <= time && p.remainingTime > 0) {
                readyQueue.push_back(&p);
            }
        }

       
        sort(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
            return a->remainingTime < b->remainingTime;
        });

        if (!readyQueue.empty()) {
            Process* current = readyQueue.front();
            readyQueue.erase(readyQueue.begin());

          
            if (current->startTime == -1) {
                current->startTime = time;
            }
            time += current->remainingTime;
            current->remainingTime = 0;
            current->completionTime = time;
            current->turnaroundTime = current->completionTime - current->arrivalTime;
            current->waitingTime = current->turnaroundTime - current->burstTime;
            completed++;

            cout << "Process " << current->id << " completed at time " << time << "\n";
        } else {
            time++;
        }
    }
}


void prioritySchedulingWithAging(vector<Process> processes) {
    cout << "\nPriority Scheduling with Aging:\n";
    int time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed < n) {
    
        vector<Process*> readyQueue;
        for (auto& p : processes) {
            if (p.arrivalTime <= time && p.remainingTime > 0) {
                readyQueue.push_back(&p);
            }
        }

        
        for (auto& p : readyQueue) {
            if (time - p->arrivalTime > 5) { 
                p->priority = max(1, p->priority - 1); 
            }
        }

        
        sort(readyQueue.begin(), readyQueue.end(), [](Process* a, Process* b) {
            return a->priority < b->priority;
        });

        if (!readyQueue.empty()) {
            Process* current = readyQueue.front();
            readyQueue.erase(readyQueue.begin());

            
            if (current->startTime == -1) {
                current->startTime = time;
            }
            time += current->remainingTime;
            current->remainingTime = 0;
            current->completionTime = time;
            current->turnaroundTime = current->completionTime - current->arrivalTime;
            current->waitingTime = current->turnaroundTime - current->burstTime;
            completed++;

            cout << "Process " << current->id << " with priority " << current->priority
                 << " completed at time " << time << "\n";
        } else {
            time++;
        }
    }
}


void analyzePerformance(vector<Process> processes) {
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    for (auto& p : processes) {
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }
    cout << "\nAverage Waiting Time: " << totalWaitingTime / processes.size() << "\n";
    cout << "Average Turnaround Time: " << totalTurnaroundTime / processes.size() << "\n";
}


int main() {
    int n = 5; 

    vector<Process> processes = generateProcesses(n);

    cout << "Generated Processes:\n";
    for (auto& p : processes) {
        cout << "Process ID: " << p.id
             << ", Arrival Time: " << p.arrivalTime
             << ", Burst Time: " << p.burstTime
             << ", Priority: " << p.priority << "\n";
    }

    
    shortestJobFirst(processes);
    analyzePerformance(processes);

   
    prioritySchedulingWithAging(processes);
    analyzePerformance(processes);

    return 0;
}
