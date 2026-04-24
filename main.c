#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

static void free_list(Node *head) {
    if (!head) return;
    Node *cur = head->next;
    while (cur && cur != head) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(head);
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }
    if (n <= 0 || m <= 0) {
        return 0;
    }

    // Build singly circular list with values 1..n
    Node *head = NULL;
    Node *prev = NULL;
    for (int i = 1; i <= n; ++i) {
        Node *node = (Node *)malloc(sizeof(Node));
        if (!node) {
            free_list(head);
            return 0;
        }
        node->val = i;
        node->next = NULL;
        if (!head) {
            head = node;
        } else {
            prev->next = node;
        }
        prev = node;
    }
    // close circle
    if (prev) prev->next = head;

    // For deletion in singly circular list, keep a pointer to node before current
    Node *before = head;
    // Move 'before' to the last node so that before->next is the first node to count from
    if (before) {
        while (before->next != head) before = before->next;
    }

    // While more than one node remains
    int remaining = n;
    while (remaining > 1) {
        // Move m-1 steps: after this, before points to node before the one to delete
        for (int step = 1; step < m; ++step) {
            before = before->next;
        }
        Node *to_del = before->next;
        printf("%d\n", to_del->val);
        before->next = to_del->next;
        // If deleting head, update head to next
        if (to_del == head) {
            head = to_del->next;
        }
        free(to_del);
        --remaining;
        // Next counting starts from the node after deleted, and 'before' stays as previous of that
    }

    // Print the last remaining node
    if (head) {
        printf("%d\n", head->val);
    }
    // Free last node
    free_list(before ? before->next : head);
    return 0;
}
