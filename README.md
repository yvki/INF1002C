## Problem Statement
Chatbots, computer programs that can respond to queries typed in natural language, have recently become a popular addition to web sites and other interactive applications. The aim of this project is to implement a simple chatbot, in C language, that can respond to simple queries made up of a single question word (called the intent) and an object (called the entity) using a command-line-like interface. The chatbot will be able to answer questions such as 'Where is the printer?' or 'What is C?' by identifying the intent (where or what) and entity (printer or C) then looking up the answer corresponding to this pair in a simple database. It will also be able to learn new answers by asking questions of the user. If a user asks a question for which the database does not contain an answer, the user will be given the option to supply an answer that can be used to respond to the same question in future. This simulates having the chatbot refer the unknown question to a third party who does know the answer.

## Specifications
The skeleton program provided to you gives some guidance on how to structure a program of this kind and some hints on how it can be implemented.
- `chat1002.h` is a header file that contains all of the type definitions and function prototypes for the program together with three other modules 
- `main.c` contains the main loop and some utility functions, prompting the user to type in a question before it gathers the response and divides it into words
- `chatbot.c` implements the behaviour of the chatbot. It is required to:
1. Identify the intent and entity in each line of input from the user
2. If the intent is an instruction, carry it out
3. If the intent is a question, search the knowledge base for an answer
4. If the knowledge base does not contain an answer, ask the user for an answer, and add the new answer to the knowledge base
- `knowledge.c` implements the chatbot’s knowledge base. For each question intent understood by the chatbot, the knowledge base should support:
1. Searching the knowledge base for an answer corresponding to the entity in the question
2. Adding a new entity with a corresponding answer to the question
3. Erasing the existing entities and answers

## Detailed Usage
- WHERE [IS] any noun phrase to Give the location of the entity
- WHAT [IS] any noun phrase to Give a definition of the term
- WHO [IS] name to Describe the person of this name
- WHEN [IS] event to Give the date and time of the entity
- WHY [IS] any noun phrase to Provide reasoning for the entity
- HOW [IS] any noun phrase to Describe the situation of the entity

For example, the user might type in 'Where is SIT?', which consists of an intent “WHERE” and an entity “SIT”. The chatbot might answer 'SIT has campuses at each of Singapore’s polytechnics, and a dedicated campus at Dover'. It will start without any knowledge of any entities, but can learn about them by asking the user. If someone asks it a question for which it does not know the answer, the chatbot will print 'I don’t know' followed by the question. The user may then type in answer. If the user types an answer, the chatbot will thereafter use this answer. If the user simply presses ‘enter’ without typing anything, the chatbot will ignore the response. In either case, the chatbot will then go back to waiting for more questions. 
- RESET to Reset the chatbot to its initial state
- LOAD to Load entities and responses from `filename.ini`
- SAVE to Save the known entities and responses to `filename.ini`
- EXIT to Exit the program

Once the chatbot has learned some entities, they can be saved to disk using the `SAVE` intent, and recalled using the `LOAD`intent. The `RESET` intent will erase all of the chatbot’s knowledge. The `LOAD`intent should append all of the entities and responses in the file to whatever entities and responses already exist in the chatbot’s memory. If an entity in the file is the same as one that is already in memory, the corresponding response from the file will replace the response currently in memory.
