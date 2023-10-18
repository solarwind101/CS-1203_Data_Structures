#include <stdio.h>
#define MAX 64

// Define the towers and their tops
int tower[3][MAX];
int top[3] = {-1, -1, -1};

// Function to add a disk to a tower
void push(int id, int disk) {
    tower[id][++top[id]] = disk;
}

// Function to remove a disk from a tower
int pop(int id) {
    return tower[id][top[id]--];
}

// Function to print the current state of the towers
void print_towers(int num) {
    char towerLabels[] = {'A', 'B', 'C'};

    // Loop through each tower
    for (int i = 0; i < 3; i++) {
        printf("Tower %c: ", towerLabels[i]);
        // Loop through each disk in the current tower
        for (int j = 0; j <= top[i]; j++) {
            printf("%d ", tower[i][j]);
        }
        printf("\n");
    }
}

// Function to move a disk from one tower to another
void move_disk(int from, int to, int num) {
    // Move the disk and print the move
    push(to, pop(from));
    printf("%d moved from Tower %c to Tower %c\n", num, 'A' + from, 'A' + to);
}

// Recursive function to solve the Tower of Hanoi problem
void tower_of_hanoi(int num, int source, int dest, int helper) {
    if (num == 1) {
        // If there is only one disk left, move it and return
        move_disk(source, dest, num);
        return;
    }
    // Move n-1 disks from source to helper
    tower_of_hanoi(num - 1, source, helper, dest);
    // Move the nth disk from source to destination
    move_disk(source, dest, num);
    // Move the n-1 disks from helper to destination
    tower_of_hanoi(num - 1, helper, dest, source);
}

int main() {
    int num;
    // Ask the user for the number of disks
    printf("Enter the number of disks: ");
    scanf("%d", &num);
    
    // Initialize the towers with the disks
    for (int i = num; i >= 1; i--)
        push(0, i);
    
    // Print the initial state of the towers
    printf("Initial Tower State:\n");
    print_towers(num);
    
    // Start the Tower of Hanoi algorithm and print each move
    printf("\nSequence of Moves:\n");
    tower_of_hanoi(num, 0, 2, 1);

    // Print the final state of the towers
    printf("\nFinal Tower State:\n");
    print_towers(num);

    return 0;
}
