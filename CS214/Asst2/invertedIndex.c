#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

struct Node {
	char * string;
	char * fName;
	int occurances;
	struct Node *next;
};

struct Node * words[10000];

int main(int argc, char * argv[]) {
	if (argv[1] && argv[2]) {
		char rootName[255] = "./";
		strcat(rootName, argv[2]);
		indexDir(rootName);
		struct Node * temp = malloc(sizeof(struct Node));
		int i;
		for (i = 0; i < sizeof(words)/sizeof(words[0]) - 1; i++) {
			int j;
			for (j = i + 1; j < sizeof(words)/sizeof(words[0]); j++) {
				if (words[i] && words[j]) {
					if (strcmp(words[i]->string, words[j]->string) > 0) {
						temp = words[i];
						words[i] = words[j];
						words[j] = temp;
					}
				}
			}
		}
		writeToFile(argv[1]);
	}
	return 0;
}

int indexDir(char * dirName) {
	DIR * d = opendir(dirName);
	struct dirent * cDir;
	if (!d) {
		FILE * fp = fopen(dirName, "r");
		if (fp) {
			cleanFile(dirName);
			return 0;
		} else {
			printf("error: argument is not a directory or file name.\n");
			exit(-1);
		}
	}

	while ((cDir = readdir(d)) != NULL) {
		if (cDir->d_type == DT_DIR && strcmp(cDir->d_name, ".") != 0 && strcmp(cDir->d_name, "..") != 0) {
			char dName[255] = "";
			strcat(dName, dirName);
			strcat(dName, "/");
			strcat(dName, cDir->d_name);
			indexDir(dName);
		} else if (cDir->d_type == DT_REG && cDir->d_name[strlen(cDir->d_name) - 3] == 't' && cDir->d_name[strlen(cDir->d_name) - 2] == 'x'
			&& cDir->d_name[strlen(cDir->d_name) - 1] == 't') {
			char fName[255] = "";
			strcat(fName, dirName);
			strcat(fName, "/");
			strcat(fName, cDir->d_name);
			cleanFile(fName);
		} 
	}
	closedir(d);
	return 0;
}

int cleanFile(char * fileName) {
	FILE * fp = fopen(fileName, "r");
	char buff[255];
	while (fgets(buff, sizeof(buff), fp)) {
		removeBadCharsAndTokenize(buff, fileName);
	}
	fclose(fp);
	return 0;
}

int removeBadCharsAndTokenize(char *string, char *fileName) {
	int i;
	for(i = 0; i < strlen(string); i++) {
		string[i] = tolower(string[i]);
		if(isalnum(string[i]) == 0) {
			string[i] = ' ';
		}
	}
	char * token = strtok(string, " ");
	while (token != NULL) {
		if (isalpha(token[0]) != 0) {
			addWord(token, fileName);
		}
		token = strtok(NULL, " ");
	}
	return 0;
}

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

char * fixFileName(char * longFileName) {
	char * lastSlash = strrchr(longFileName, '/');
	char * newFileName = malloc(sizeof(char) * strlen(lastSlash) - 1);
	int i;
	for (i = 1; i < strlen(lastSlash); i++) {
		newFileName[i-1] = lastSlash[i];
	}
	return newFileName;
}

int addWord(char * token, char *fileName) {
	struct Node * newEntry = malloc(sizeof(struct Node));
	newEntry->string = malloc(sizeof(char) * strlen(token));
	strcpy(newEntry->string, token);
	newEntry->fName = malloc(sizeof(char) * strlen(fileName));
	char * newFileName = fixFileName(fileName);
	strcpy(newEntry->fName, newFileName);
	newEntry->next = NULL;
	int index = hash(token) % 10000;
	if (words[index] && strcmp(words[index]->fName, newEntry->fName) == 0) {
		words[index]->occurances++;
	} else if(words[index] && strcmp(words[index]->fName, newEntry->fName) != 0) {
		struct Node * nodePtr = malloc(sizeof(struct Node));
		struct Node * nodePrev = malloc(sizeof(struct Node));
		nodePtr = words[index];
		while (nodePtr != NULL){
			if (strcmp(nodePtr->fName, newEntry->fName) == 0) {
				nodePtr->occurances++;
				return 0;
			}
			nodePrev = nodePtr;
			nodePtr = nodePtr->next;
		}
		nodePrev->next = newEntry;
		newEntry->occurances = 1;
	} else {
		words[index] = newEntry;
		newEntry->occurances = 1;
	}
	return 0;
}

int writeToFile(char * fileName) {
	FILE * fp;
	fp = fopen(fileName, "w");

	fprintf(fp, "<?xml version= ""1.0"" encoding =""UTF-8""?>\n");
	fprintf(fp, "<fileIndex>\n");
	int i;
	for(i = 0; i < (sizeof(words)/sizeof(*words)); i++) {
		if (words[i]) {
			fprintf(fp, "\t<word text=""%s"">%i""</file>""\n", words[i]->string, words[i]->occurances);
			fprintf(fp, "\t\t<file name=""%s"">%i</file>\n", words[i]->fName, words[i]->occurances);
			fprintf(fp, "\t</word>\n");

			if (words[i]->next) {
				struct Node * nodePtr = malloc(sizeof(struct Node));
				nodePtr = nodePtr->next;
				while (nodePtr != NULL) {
					fprintf(fp, "\t<word text=""%s"">%i""</file>""\n", nodePtr->string, nodePtr->occurances);
					fprintf(fp, "\t\t<file name=""%s"">%i</file>\n", nodePtr->fName, nodePtr->occurances);
					fprintf(fp, "\t</word>");
				}
			}
		}
	}
	fprintf(fp, "</fileIndex>");
	fclose(fp);
	return 0;
}
