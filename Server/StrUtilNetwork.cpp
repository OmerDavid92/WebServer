#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>

static void strcpyByIndexes(char* src, char* dest, int start, int end) {
	char* srcPlusStart = src + start;

	strcpy(dest, srcPlusStart);
	dest[end] = '\0';
}

static int getRow(char* src, char* row) {
	char currentIndex = 0;
	char currentChar = src[currentIndex];

	while (currentChar != '\r' && currentChar != '\0') {
		currentIndex++;
		currentChar = src[currentIndex];
	}

	strcpyByIndexes(src, row, 0, currentIndex);

	if (currentChar == '\r') {
		currentIndex += 2;
	}

	return currentIndex;
}

static int getWord(char* src, char* word, char delimiter) {
	int currentIndex = 0;
	char currentChar = src[currentIndex];

	while (currentChar != delimiter && currentChar != '\0') {
		currentIndex++;
		currentChar = src[currentIndex];
	}

	strcpyByIndexes(src, word, 0, currentIndex);

	if (currentChar == delimiter) {
		currentIndex++;
	}

	return currentIndex;
}

static int getEndIndexOfFirstRequest(char* requests) {
	int currentIndex = 1;

	while (requests[currentIndex] != '\0'
		&& strncmp(requests + currentIndex, "GET", 3) != 0
		&& strncmp(requests + currentIndex, "POST", 4) != 0
		&& strncmp(requests + currentIndex, "PUT", 3) != 0
		&& strncmp(requests + currentIndex, "DELETE", 6) != 0
		&& strncmp(requests + currentIndex, "HEAD", 4) != 0
		&& strncmp(requests + currentIndex, "OPTIONS", 7) != 0
		&& strncmp(requests + currentIndex, "TRACE", 5) != 0)
	{
		currentIndex++;
	}

	return currentIndex - 1;
}