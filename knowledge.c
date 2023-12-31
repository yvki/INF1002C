/*
 * INF1002 (C Language) Group Project.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * knowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

struct LIST {
	char *entity;
	char *response;
	struct LIST *next;
};

typedef struct LIST LIST_NODE;
typedef LIST_NODE *LIST_NODE_PTR;

/* node and pointer for 'what' intent */
typedef struct LIST WHAT_NODE;
typedef WHAT_NODE *WHAT_NODE_PTR;
WHAT_NODE_PTR what_head = NULL;

/* node and pointer for 'where' intent */
typedef struct LIST WHERE_NODE;
typedef WHERE_NODE *WHERE_NODE_PTR;
WHERE_NODE_PTR where_head = NULL;

/* node and pointer for 'why' intent */
typedef struct LIST WHY_NODE;
typedef WHY_NODE *WHY_NODE_PTR;
WHY_NODE_PTR why_head = NULL;

/* node and pointer for 'how' intent */
typedef struct LIST HOW_NODE;
typedef HOW_NODE *HOW_NODE_PTR;
HOW_NODE_PTR how_head = NULL;

/* node and pointer for 'who' intent */
typedef struct LIST WHO_NODE;
typedef WHO_NODE *WHO_NODE_PTR;
WHO_NODE_PTR who_head = NULL;

/* node and pointer for 'when' intent */
typedef struct LIST WHEN_NODE;
typedef WHEN_NODE *WHEN_NODE_PTR;
WHEN_NODE_PTR when_head = NULL;

/* linked list structure */
struct list *linkedNodes(char *intent, char *entity, char *response) {
	LIST_NODE *node = (LIST_NODE_PTR)malloc(sizeof(LIST_NODE));
	WHAT_NODE_PTR what_node = what_head;
	WHERE_NODE_PTR where_node = where_head;
	WHY_NODE_PTR why_node = why_head;
	HOW_NODE_PTR how_node = how_head;
	WHO_NODE_PTR who_node = who_head;
	WHEN_NODE_PTR when_node = when_head;

	if (compare_token(intent, "what") == 0) {
		if (what_head == NULL) {
			what_node = node;
			node->entity = entity;
			node->response = response;
			node->next = NULL;
			what_head = what_node;
		} else {
			while (what_node->next != NULL) {
				what_node = what_node->next;
			}
			what_node->next = node;
			what_node->next->entity = entity;
			what_node->next->response = response;
			what_node->next->next = NULL;
		}
	} 
	else if (compare_token(intent, "where") == 0) {
		if (where_head == NULL) {
			where_node = node;
			node->entity = entity;
			node->response = response;
			node->next = NULL;
			where_head = where_node;
		} else {
			while (where_node->next != NULL) {
				where_node = where_node->next;
			}
			where_node->next = node;
			where_node->next->entity = entity;
			where_node->next->response = response;
			where_node->next->next = NULL;
		}
	}
	else if (compare_token(intent, "why") == 0) {
		if (why_head == NULL) {
			why_node = node;
			node->entity = entity;
			node->response = response;
			node->next = NULL;
			why_head = why_node;
		} else {
			while (why_node->next != NULL) {
				why_node = why_node->next;
			}
			why_node->next = node;
			why_node->next->entity = entity;
			why_node->next->response = response;
			why_node->next->next = NULL;
		}
	}
	else if (compare_token(intent, "how") == 0) {
		if (how_head == NULL) {
			how_node = node;
			node->entity = entity;
			node->response = response;
			node->next = NULL;
			how_head = how_node;
		} else {
			while (how_node->next != NULL) {
				how_node = how_node->next;
			}
			how_node->next = node;
			how_node->next->entity = entity;
			how_node->next->response = response;
			how_node->next->next = NULL;
		}
	}
	else if (compare_token(intent, "who") == 0) {
		if (who_head == NULL) {
			who_node = node;
			node->entity = entity;
			node->response = response;
			node->next = NULL;
			who_head = who_node;
		} else {
			while (who_node->next != NULL) {
				who_node = who_node->next;
			}
			who_node->next = node;
			who_node->next->entity = entity;
			who_node->next->response = response;
			who_node->next->next = NULL;
		}
	}
	else if (compare_token(intent, "when") == 0) {
		if (when_head == NULL) {
			when_node = node;
			node->entity = entity;
			node->response = response;
			node->next = NULL;
			when_head = when_node;
		} else {
			while (when_node->next != NULL) {
				when_node = when_node->next;
			}
			when_node->next = node;
			when_node->next->entity = entity;
			when_node->next->response = response;
			when_node->next->next = NULL;
		}
	}
}

/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
char *toLowerCase(char *a) {
	for (int i = 0; a[i] != '\0'; i++) {
		a[i] = tolower(a[i]);
	}
	return a;
}

int knowledge_get(const char *intent, const char *entity, char *response, int n) {
	/* to be implemented */
	char haystack[MAX_RESPONSE], needle[MAX_RESPONSE];
	char *end= NULL;
	char dl[] = " ";
	/* 'what' intent */
	if (compare_token(intent, "what") == 0) {
		struct LIST *ptr = what_head;
		while (ptr != NULL) {	
			if (compare_token(ptr->entity, entity) == 0) {
				snprintf(response, n, "%s", ptr->response);
				return KB_OK;
			} else {
				strcpy(needle, entity);
				strcpy(haystack, ptr->entity);
				toLowerCase(needle);
				toLowerCase(haystack);
				end = strstr(haystack, needle);
				if (end!= NULL) {
					snprintf(response, n, "%s", ptr->response);
					return KB_OK;
				}
			}
			ptr = ptr->next;
		}
		return KB_NOTFOUND;
	}
	/* 'where' intent */
	else if (compare_token(intent, "where") == 0) {
		/* type here for 'where' node */
		struct LIST *ptr = where_head;
		while (ptr != NULL) {	
			if (compare_token(ptr->entity, entity) == 0) {
				snprintf(response, n, "%s", ptr->response);
				return KB_OK;
			} else {
				strcpy(needle, entity);
				strcpy(haystack, ptr->entity);
				toLowerCase(needle);
				toLowerCase(haystack);
				end = strstr(haystack, needle);
				if (end!= NULL) {
					snprintf(response, n, "%s", ptr->response);
					return KB_OK;
				}
			}
			ptr = ptr->next;
		}
		return KB_NOTFOUND;
	}
	/* 'why' intent */
	else if (compare_token(intent, "why") == 0) {
		/* type here for 'why' node */
		struct LIST *ptr = why_head;
		while (ptr != NULL) {	
			if (compare_token(ptr->entity, entity) == 0) {
				snprintf(response, n, "%s", ptr->response);
				return KB_OK;
			} else {
				strcpy(needle, entity);
				strcpy(haystack, ptr->entity);
				toLowerCase(needle);
				toLowerCase(haystack);
				end = strstr(haystack, needle);
				if (end!= NULL) {
					snprintf(response, n, "%s", ptr->response);
					return KB_OK;
				}
			}
			ptr = ptr->next;
		}
		return KB_NOTFOUND;
	}
	/* 'how' intent */
	else if (compare_token(intent, "how") == 0) {
		/* type here for 'how' node */
		struct LIST *ptr = how_head;
		while (ptr != NULL) {	
			if (compare_token(ptr->entity, entity) == 0) {
				snprintf(response, n, "%s", ptr->response);
				return KB_OK;
			} else {
				strcpy(needle, entity);
				strcpy(haystack, ptr->entity);
				toLowerCase(needle);
				toLowerCase(haystack);
				end = strstr(haystack, needle);
				if (end!= NULL) {
					snprintf(response, n, "%s", ptr->response);
					return KB_OK;
				}
			}
			ptr = ptr->next;
		}
		return KB_NOTFOUND;
	}
	/* 'who' intent */
	else if (compare_token(intent, "who") == 0) {
		/* type here for 'who' node */
		struct LIST *ptr = who_head;
		while (ptr != NULL) {	
			if (compare_token(ptr->entity, entity) == 0) {
				snprintf(response, n, "%s", ptr->response);
				return KB_OK;
			} else {
				strcpy(needle, entity);
				strcpy(haystack, ptr->entity);
				toLowerCase(needle);
				toLowerCase(haystack);
				end = strstr(haystack, needle);
				if (end!= NULL) {
					snprintf(response, n, "%s", ptr->response);
					return KB_OK;
				}
			}
			ptr = ptr->next;
		}
		return KB_NOTFOUND;
	}
	/* 'when' intent */
	else if (compare_token(intent, "when") == 0) {
		/* type here for 'when' node */
		struct LIST *ptr = when_head;
		while (ptr != NULL) {
			if (compare_token(ptr->entity, entity) == 0) {
				snprintf(response, n, "%s", ptr->response);
				return KB_OK;
			} else {
				strcpy(needle, entity);
				strcpy(haystack, ptr->entity);
				toLowerCase(needle);
				toLowerCase(haystack);
				end = strstr(haystack, needle);
				if (end != NULL) {
					snprintf(response, n, "%s", ptr->response);
					return KB_OK;
				}
			}
			ptr = ptr->next;
		}
		return KB_NOTFOUND;
	}
}

/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_OK, if successful (instead of previous KB_FOUND)
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response) {
	/* to be implemented */
	if (chatbot_is_question(intent) == KB_INVALID) {
		return KB_INVALID;
	} 
	else if ((WHAT_NODE_PTR) calloc(1, sizeof(what_head)) == NULL) {
		return KB_NOMEM;
	} 
	else if ((WHERE_NODE_PTR) calloc(1, sizeof(where_head)) == NULL) {
		return KB_NOMEM;
	}
	else if ((WHY_NODE_PTR) calloc(1, sizeof(why_head)) == NULL) {
		return KB_NOMEM;
	}
	else if ((HOW_NODE_PTR) calloc(1, sizeof(how_head)) == NULL) {
		return KB_NOMEM;
	}
	else if ((WHO_NODE_PTR) calloc(1, sizeof(who_head)) == NULL) {
		return KB_NOMEM;
	}
	else if ((WHEN_NODE_PTR) calloc(1, sizeof(when_head)) == NULL) {
		return KB_NOMEM;
	}
	else {
		linkedNodes(strdup(intent), strdup(entity), strdup(response));
		return KB_OK;
	}
}

/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE *f) {
	/* to be implemented*/
	int inttype = 4;
	char line[128];
	char *entity;
	char *response;

	/* delim for line handling */
	char d1[] = "[";
	char d2[] = "]";
	char d3[] = "=";

	while (fgets(line, MAX_ENTITY + 1 + MAX_RESPONSE + 1, f)) {
		line[strcspn(line, "\n")] = 0;
		/* ignore '[' ,']' or '=' */
		for (int i = 0; i < strlen(line); i++) {
			if (isalpha(line[i]) != 0 && !strstr(line, "=")) {
				char *char_ptr = strtok(line, d1);
				char *char_line = strtok(char_ptr, d2);
				if (compare_token(char_line, "what") == 0) {
					inttype = 0;
				}
				else if (compare_token(char_line, "where") == 0) {
					inttype = 1;
				}
				else if (compare_token(char_line, "why") == 0) {
					inttype = 2;
				}
				else if (compare_token(char_line, "how") == 0) {
					inttype = 3;
				}
				else if (compare_token(char_line, "who") == 0) {
					inttype = 4;
				}
				else if (compare_token(char_line, "when") == 0) {
					inttype = 5;
				}
			}
			/* not intent means line is response */
			else if (isalpha(line[i]) == 0 && strstr(line, "=")) {
				char *entity = strtok(line, d3);
				char *response = strtok(NULL, d3);
				switch (inttype) {
					case 0:
						knowledge_put("what", entity, response);
						break;
					case 1:
						knowledge_put("where", entity, response);
						break;
					case 2:
						knowledge_put("why", entity, response);
						break;
					case 3:
						knowledge_put("how", entity, response);
						break;
					case 4:
						knowledge_put("who", entity, response);
						break;
					case 5:
						knowledge_put("when", entity, response);
						break;
					default:
						break;
				}
			}
		}
	}

	if (inttype > 6) {
		return KB_NOTFOUND;
	} else {
		return 0;
	}
}

/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
	/* to be implemented */
	struct LIST *tmp;
	/* 'what' intent */
	while (what_head != NULL) {
		tmp = what_head;
		what_head = what_head->next;
		//deallocate memory from 'what' head
		free(tmp);
	}
	/* 'where' intent */
	while (where_head != NULL) {
		tmp = where_head;
		where_head = where_head->next;
		//deallocate memory from 'what' head
		free(tmp);
	}
	/* 'why' intent */
	while (why_head != NULL) {
		tmp = why_head;
		why_head = why_head->next;
		//deallocate memory from 'why' head
		free(tmp);
	}
	/* 'how' intent */
	while (how_head != NULL) {
		tmp = how_head;
		how_head = how_head->next;
		//deallocate memory from 'how' head
		free(tmp);
	}
	/* 'who' intent */
	while (who_head != NULL) {
		tmp = who_head;
		who_head = who_head->next;
		//deallocate memory from 'who' head
		free(tmp);
	}
	/* 'when' intent */
	while (when_head != NULL) {
		tmp = when_head;
		when_head = when_head->next;
		//deallocate memory from 'when' head
		free(tmp);
	}
}

/* Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {
	/* to be implemented */
	/* 'what' intent */
	struct LIST *what_ptr = what_head;
	fputs("[what]\n", f);
	while (what_ptr != NULL) {
		fprintf(f, "%s=%s\n", what_ptr->entity, what_ptr->response);
		what_ptr = what_ptr->next;
	}	
	/* 'where' intent */
	struct LIST *where_ptr = where_head;
	fputs("[where]\n", f);
	while (where_ptr != NULL) {
		fprintf(f, "%s=%s\n", where_ptr->entity, where_ptr->response);
		where_ptr = where_ptr->next;
	}
	/* 'why' intent */
	struct LIST *why_ptr = why_head;
	fputs("[why]\n", f);
	while (why_ptr != NULL) {
		fprintf(f, "%s=%s\n", why_ptr->entity, why_ptr->response);
		why_ptr = why_ptr->next;
	}
	/* 'how' intent */
	struct LIST *how_ptr = how_head;
	fputs("[how]\n", f);
	while (how_ptr != NULL) {
		fprintf(f, "%s=%s\n", how_ptr->entity, how_ptr->response);
		how_ptr = how_ptr->next;
	}
	/* 'who' intent */
	struct LIST *who_ptr = who_head;
	fputs("[who]\n", f);
	while (who_ptr != NULL) {
		fprintf(f, "%s=%s\n", who_ptr->entity, who_ptr->response);
		who_ptr = who_ptr->next;
	}
	/* 'when' intent */
	struct LIST *when_ptr = when_head;
	fputs("[when]\n", f);
	while (when_ptr != NULL) {
		fprintf(f, "%s=%s\n", when_ptr->entity, when_ptr->response);
		when_ptr = when_ptr->next;
	}
}