/*
 * INF1002 (C Language) Group Project.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE, WHY, HOW, WHO, WHEN it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#include <stdio.h>
#include <string.h>
#include "chat1002.h"
#include "chitchat.c"

int pos = 0;

/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {
	return "Chatbot";
}

/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {
	return "User";
}

/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {
	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, ""); 
		return 0;
	}
	/* look for intent in user input */
	for (int i = 0; i < inc; i++) {
		if (compare_token(inv[i], "what") == 0 || compare_token(inv[i], "where") == 0 || compare_token(inv[i], "why") == 0 || compare_token(inv[i], "how") == 0 || compare_token(inv[i], "who") == 0 || compare_token(inv[i], "when") == 0) {
			pos = i;
			break;
		}
	}
	/* invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[pos]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else if (chatbot_is_menu(inv[0]))
		return chatbot_do_menu(inc, inv, response, n);
	else if (chatbot_is_chitchat(inc, inv))
		return chatbot_do_chitchat(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}
}

/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {
	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;
}

/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {
	snprintf(response, n, "Goodbye!");
	return 1;
}

/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {
	return compare_token(intent, "load") == 0;
}

/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {
	int a = 1;
	char *warnfp = "Missing filename.";

	if (inc < 2) {
		snprintf(response, n, "%s", warnfp);
		return 0;
	}

	if (compare_token(inv[1], "file") == 0){
		a = 2;
	} else if (a == 2 && inc < 3) {
		snprintf(response, n, "%s", warnfp);
		return 0;
	}
	
	FILE *fp;
	fp = fopen(inv[a], "r");

	if (fp != NULL) {
		int k = knowledge_read(fp);
		fclose(fp);
		if (k == KB_NOMEM){
			snprintf(response, n, "File %s is too big to load.", inv[a]);
		} else {
			void countLines(char *fp) {
				FILE* inifile = fopen(fp, "r");
				int c, linenum = 0;
				do {
					c = fgetc(inifile);
					if (c == '\n') {
						linenum++;
					}
				}
				while (c != EOF);
				if (c != '\n' && linenum != 0) {
					linenum++;
				}
				snprintf(response, n, "Read %d responses from %s.", linenum, inv[a]);
			}
			countLines(inv[a]);
			return 0;
		}
	} else {
		snprintf(response, n, "Cannot load file. Check file name spelling and path configuration again.", inv[a]);
	}
	return 0;
}

/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", "why", "how", "who" or "when"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {
	/* to be implemented */
	return (compare_token(intent, "what") == 0 || compare_token(intent, "where") == 0 || compare_token(intent, "why") == 0 || compare_token(intent, "how") == 0 || compare_token(intent, "who") == 0 || compare_token(intent, "when") == 0);
}

/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {
	char entity[MAX_RESPONSE] = "\0";
	char qn[MAX_RESPONSE] = "\0";
	char newqna[MAX_RESPONSE] = "\0";
	char *join = " ";
	int len;

	if (inc <= 1) {
		snprintf(response, n, "I don't understand.");
		return 0;
	}
	else if (inv[pos + 1] == NULL) {
		snprintf(response, n, "Missing entity in question.");
		return 0;
	}

	/* remove intent and 'is' from line, remaining words concatenate to entity */
	if ((compare_token(inv[pos + 1], "is") == 0)) {
		for (int i = pos + 2; i < inc; i++) {
			strncat(entity, inv[i], MAX_RESPONSE);
			if (i == inc - 1) {
				"";
			} else {
				strncat(entity, join, MAX_RESPONSE);
			}
			strcpy(qn, inv[pos + 1]);
		}
		if (inv[pos + 2] == NULL) {
			snprintf(response, n, "Missing entity in question.");
			return 0;
		}
		len = knowledge_get(inv[pos], entity, response, n);
	}
	else {
		for (int i = pos + 1; i < inc; i++) {
			strncat(entity, inv[i], MAX_RESPONSE);
			if (i == inc - 1) {
				"";
			} else {
				strncat(entity, join, MAX_RESPONSE);
			}
		}
		len = knowledge_get(inv[pos], entity, response, n);
	}

	if (len == -1) {
		prompt_user(response, n, "I don't know. %s %s %s?", inv[pos], qn, entity);
		pos = 0;
		len = knowledge_put(inv[pos], entity, response);
		snprintf(response, n, "Okay. I learnt something new.");
		return 0;
	} else {
		pos = 0;
		return 0;
	}
}

/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {
	/* to be implemented (confirm done) */
	return compare_token(intent, "reset") == 0;
}

/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {
	/* to be implemented (confirm done) */
	knowledge_reset();
	snprintf(response, n, "Chatbot reset.");
	return 0;
}

/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", "why", "how", "who" or "when"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {
	/* to be implemented (confirm done) */
	return compare_token(intent, "save") == 0;
}

/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {
	/* to be implemented */
	FILE *f;
	if (inv[1] != NULL) {
		char file[MAX_RESPONSE] = "\0";
		strncat(file, inv[inc-1], MAX_RESPONSE);
		/* file does not exists -> create new file VS
		file exists -> delete old file content so that pointer can start from first new input */
		f = fopen(file, "w+");
		knowledge_write(f);
		fclose(f);
		snprintf(response, n, "Saved file.");
	} else {
		snprintf(response, n, "Missing file name.");
	}
	return 0;
}

/* extra feature?? */

int chatbot_is_menu(const char *intent) {
	return compare_token(intent, "menu") == 0;
}

void helpMessage() {
	printf("\n*************************\n");
	printf("Chatbot Instructions Menu\n");
	printf("*************************\n\n");
	printf("MENU\tShow the instruction menu.\n");
	printf("LOAD 'filename.ini'\tLoad entities and responses from file into current working directory.\n");
	printf("SAVE 'filename.ini'\tSave known entities and responses into a file in the current working directory.\n");
	printf("RESET\tReset the chatbot to its initial state.\n");
	printf("EXIT\tExit the chatbot program.\n\n");
	printf("How to ask questions? Type an intent (5W1H) and corresponding entity.\n");
	printf("Chatbot will answer questions to its best of ability.\nOtherwise, you can teach it so that its knowledge can grow.\n\n");
}

int chatbot_do_menu(int inc, char *inv[], char *response, int n) {
	helpMessage();
	snprintf(response, n, "End of instruction menu.");
	return 0;
}

int chatbot_is_chitchat(int inc, char *inv[]) {
	struct chitchat *tmp = head;
	int chat_pr = 0;
	/* check for pronouns in input */
	while (tmp != NULL) {
		for (int i = 0; i < inc; i++) {
			if (compare_token(inv[i], "you") == 0) {
				chat_pr = 1;
				break;
			}
		}
		if (chat_pr == 1) {
			break;
		} else {
			tmp = tmp->next;
		}
	}
	if (((compare_token(inv[pos], "what") == 0) && chat_pr == 1) || ((compare_token(inv[pos], "where") == 0) && chat_pr == 1) || ((compare_token(inv[pos], "why") == 0) && chat_pr == 1) || ((compare_token(inv[pos], "how") == 0) && chat_pr == 1) || ((compare_token(inv[pos], "who") == 0) && chat_pr == 1) || ((compare_token(inv[pos], "when") == 0) && chat_pr == 1)) {
		return 1;
	}
	else if (compare_token(inv[pos], "what") != 0 && compare_token(inv[pos], "where") != 0 && compare_token(inv[pos], "why") != 0 && compare_token(inv[pos], "how") != 0 && compare_token(inv[pos], "who") != 0 && compare_token(inv[pos], "when") != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void chatbot_chitchat() {
	char chatdata[MAX_RESPONSE + 1 + MAX_INPUT + 1];
	char noundata[MAX_RESPONSE + 1 + MAX_INPUT + 1];
	/* delim for strtok */
	char dl4[] = "=";
	/* load pronouns */
	FILE *p;
	p = fopen("pronouns.ini", "r");
	while (fgets(noundata, MAX_ENTITY + 1 + MAX_RESPONSE + 1, p)) {
		noundata[strcspn(noundata, "\n")] = 0;
		char *cp_entity = strtok(noundata, dl4);
		char *cp_response = strtok(NULL, dl4);
		linkedChat(strdup(cp_entity), strdup(cp_response), 1);
	}
	fclose(p);
	/* load chitchat */
	FILE *c;
	c = fopen("chitchat.ini", "r");
	while (fgets(chatdata, MAX_ENTITY + 1 + MAX_RESPONSE + 1, c)) {
		chatdata[strcspn(chatdata, "\n")] = 0;
		char *cp_entity = strtok(chatdata, dl4);
		char *cp_response = strtok(NULL, dl4);
		linkedChat(strdup(cp_entity), strdup(cp_response), 0);
	}
	fclose(c);
}

const int y = 32;
char *LowerCase(char *a) {
	for (int i = 0; a[i] != '\0'; i++) {
		a[i] = tolower(a[i]);
	}
	return a;
}

int chatbot_do_chitchat(int inc, char *inv[], char *response, int n) {
	struct chitchat *tmp = head;
	struct chitchat *pr_tmp = pr_head;
	/* pronouns variables */
	char *value = NULL;
	char match[MAX_RESPONSE + MAX_INPUT] = "\0";
	char resp[MAX_RESPONSE] = "\0";
	char *pr = NULL;
	char *cont = NULL;
	/* input variables */
	char input[MAX_INPUT + MAX_RESPONSE] = "\0";
	char haystack[MAX_RESPONSE], needle[MAX_RESPONSE] = "\0"; 
	char extract_input[MAX_RESPONSE] = "\0";
	char extract[MAX_INPUT][MAX_RESPONSE], extract_needle[MAX_INPUT][MAX_RESPONSE];
	/* response to array */
	char arr_resp[10][MAX_INPUT];
	char pr_array[MAX_INPUT][MAX_INPUT];
	int check = 0;

	/* concatenate input into a string */
	for (int i = 0; i < inc; i++) {
		strncat(input, inv[i], MAX_RESPONSE);
		if (i != inc - 1)
			strncat(input, " ", MAX_RESPONSE);
	}

	while (tmp != NULL) {
		int check = 0;
		strcpy(haystack, input);
		strcpy(needle, tmp->entity);
		LowerCase(haystack);
		LowerCase(needle);
		value = strstr(haystack, needle);
		if (value != NULL) {
			strcpy(match, tmp->response);
			break;
		}
		tmp = tmp->next;
	}
	
	/* response string to array */
	char *str = strtok(input, " ");
	int num_extract = 0;
	while (str != NULL) {
		strcpy(extract[num_extract], str);
		str = strtok(NULL, " ");
		num_extract++;
	}

	/* specific string in response to array */
	char *compare = strtok(needle, " ");
	int num = 0;
	while (compare != NULL) {
		strcpy(extract_needle[num], compare);
		compare = strtok(NULL, " ");
		num++;
	}

	int checknum = 0;
	int count = 0;
	char *dltab = " ";
	
	for (int i = 0; i < num_extract; i++) {
		if (checknum == num) {
			strncat(extract_input, extract[i], MAX_RESPONSE);
			if (i != num_extract - 1) {
				strncat(extract_input, dltab, MAX_RESPONSE);
			}
		}
		else if (compare_token(extract[i], extract_needle[checknum]) == 0) {
			checknum++;
		}
		else if (compare_token(extract[i], extract_needle[checknum]) != 0) {
			checknum = 0;
		}
	}
	/* for not entity question and not chitchat */
	if (compare_token(match, "") == 0) {
		snprintf(response, n, "Ok.");
		return 0;
	}

	/* separate responses by ',' */
	char *extract_match = strtok(match, ",");
	while (extract_match != NULL) {
		strcpy(arr_resp[count], extract_match);
		extract_match = strtok(NULL, ",");
		count++;
	}

	/* randomize responses */
	int r = 0;
	r = (rand() % (count));
	strcpy(resp, arr_resp[r]);

	while (pr_tmp != NULL) {
		int check = 0;
		strcpy(haystack, extract_input);
		strcpy(needle, pr_tmp->entity);
		LowerCase(haystack);
		LowerCase(needle);
		pr = strstr(haystack, needle);
		if (pr != NULL) {
			/* input to array */
			char *pr_extract = strtok(haystack, " ");
			while (pr_extract != NULL) {
				strcpy(pr_array[check], pr_extract);
				pr_extract = strtok(NULL, " ");
				check++;
			}
			/* locate pronoun in input */
			for (int i = 0; i < check; i++) {
				if (compare_token(pr_array[i], needle) == 0) {
					strcpy(pr_array[i], pr_tmp->response);
				}
			}
			/* clean input */
			strcpy(extract_input, "");
			/* array back to string */
			for (int i = 0; i < check; i++) {
				strncat(extract_input, pr_array[i], MAX_RESPONSE);
				if (i != check - 1) {
					strcat(extract_input, " ");
				}
			}
			break;
		}
		pr_tmp = pr_tmp->next;
	}

	/* response based on previous input string */
	cont = strstr(resp, "{0}");
	if (cont != NULL) {
		char *extract_resp = strtok(resp, "{0}");
		char *last = strtok(NULL, "{0}");
		strncat(extract_input, last, MAX_RESPONSE);
		strncat(extract_resp, extract_input, MAX_RESPONSE);
		snprintf(response, n, "%s", extract_resp);
		return 0;
	}
	else {
		snprintf(response, n, "%s", resp);
		return 0;
	}
	return 0;
}