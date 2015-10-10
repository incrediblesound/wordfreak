#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structures //
typedef struct String {
	size_t length;
	char body[1000];
} String;

typedef struct Lines {
	unsigned int num_lines;
	String lines[10000];
} Lines;

typedef struct WordData {
	int times;
	char word[100];
} WordData;

typedef struct Dictionary {
	short size;
	WordData words[10000];
} Dictionary;

// opens the file and fills a Lines struc
// with the lines of text from that file
Lines* getLines(char* file){
	FILE * fp;
	fp = fopen(file, "r+");
	Lines* text = malloc(sizeof(Lines));
	unsigned int counter = 0;
	while(1){
		String* new_line = malloc(sizeof(String));
		fgets(new_line->body, 1000, fp);
		new_line->length = strlen(new_line->body);
		text->lines[counter] = *new_line;
		if(feof(fp)){
			break;
		}
		counter++;
	}
	text->num_lines = counter+1;
	return text;
}

// tests to see if a word exists in a dictionary
// if so, return the index, otherwise return -1
short dictionary_contains(Dictionary* dict, char* test){
	short counter = 0;
	while(counter < dict->size){
		char* current_word = dict->words[counter].word;
		if(!strcmp(current_word, test)){
			return counter;
		}
		counter++;
	}
	return -1;
};

// adds a word to a dictionary if it in not already
// in there, otherwise increments the counter of
// word occurrances
void add_to_dictionary(Dictionary* dict, char* word){
	short result = dictionary_contains(dict, word);
	if(result > -1){
		dict->words[result].times++;
	} else {
		WordData* data = malloc(sizeof(WordData));
		data->times = 1;
		strcpy(data->word, word);
		dict->words[dict->size] = *data;
		dict->size++;
	}
}

// takes a lines struct, breaks each line into words
// and enters those words into a new dictionary
Dictionary* getDictionary(Lines* text){
	Dictionary* dictionary = malloc(sizeof(Dictionary));
	short line_count = 0;
	while(line_count < text->num_lines){

		String* current_line = &text->lines[line_count];
		char word[100] = "";
		short index = 0;
		short word_size = 0;
		short has_word = 0;

		while(index <= current_line->length){

			char* ch = &current_line->body[index];
			if(*ch == ' ' || *ch == '\n' || index == current_line->length){
				if(has_word){
					add_to_dictionary(dictionary, word);
					memset(word, 0, strlen(word));
					has_word = 0;
					word_size = 0;
				}
			} else {
				has_word = 1;
				word[word_size] = *ch;
				word_size++;
			}
			index++;
		}
		line_count++;
	}
	return dictionary;
}

// prints out the contents of a dictionary
void printDictionary(Dictionary* dict){
	short counter = 0;
	printf("{");
	while(counter < dict->size){
		WordData* word_data = &dict->words[counter];
		printf(" \"%s\": ", word_data->word);
		printf("%d", word_data->times);
		if(counter != dict->size-1){
			printf(",");
		}
		counter++;
	}
	printf("}\n");
}

int main(int num, char **args){
	if(num == 1){
		printf("Error: word freak requires a file path to work.\n");
	} 
	else if(num > 2){
		printf("Error: too many arguments.\n");
	} else {
		Lines* text = getLines(args[1]);
		Dictionary* dictionary = getDictionary(text);
		printDictionary(dictionary);
	}
	return 0;
}