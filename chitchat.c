#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

struct chitchat {
    char *entity;
    char *response;
    struct chitchat *next;
};

typedef struct chitchat NODE;
typedef NODE *NODE_PTR;
NODE_PTR head = NULL;

typedef struct chitchat pronoun_NODE;
typedef pronoun_NODE *PR_NODE_PTR;
PR_NODE_PTR pr_head = NULL;

struct list *linkedChat(char *entity, char *response, int chattype) {
    NODE *node = (NODE_PTR)malloc(sizeof(NODE));
    NODE_PTR current = head;
    PR_NODE_PTR pr_node = pr_head;

    switch (chattype) {
        /* for input without pronouns eg. hello */
        case 0:
            if (head == NULL) {
                current = node;
                node->entity = entity;
                node->response = response;
                node->next = NULL;
                head = current;
            }
            else {
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = node;
                current->next->entity = entity;
                current->next->response = response;
                current->next->next = NULL;
            }
            break;
         /* for input with pronouns eg. how are you */
        case 1:
            if (pr_head == NULL) {
                pr_node = node;
                node->entity = entity;
                node->response = response;
                node->next = NULL;
                pr_head = pr_node;
            }
            else {
                while (pr_node->next != NULL) {
                    pr_node = pr_node->next;
                }
                pr_node->next = node;
                pr_node->next->entity = entity;
                pr_node->next->response = response;
                pr_node->next->next = NULL;
            }
            break;
        /* for input that is not chitchat */
        default:
            break;
    }
}