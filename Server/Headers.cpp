#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_BUFEER 2000
#include <iostream>
#include <string.h>
#include "StrUtilNetwork.cpp"
using namespace std;

class Headers
{
public:
	char m_Host[100] = { 0 };
	char m_Content_Type[100] = { 0 };
	char m_Content_Length[100] = { 0 };
	char m_Content_Language[100] = { 0 };
	
	Headers() {};

	static Headers* Parse(char i_Headers[MAX_BUFEER]) {
		Headers* headers = new Headers();
		char row[MAX_BUFEER] = { '\0' };
		int currentIndex = 0;

		currentIndex += getRow(i_Headers + currentIndex, row);

		while (strcmp(row, "\0")) {
			ParseField(headers, row);
			currentIndex += getRow(i_Headers + currentIndex, row);
		}

		return headers;
	}

	static void ParseField(Headers* headers, char* row) {
		int currentIndex = 0;
		char field[MAX_BUFEER] = { '\0' };
		char value[MAX_BUFEER] = { '\0' };

		currentIndex += getWord(row + currentIndex, field, ':');

		if (!strlen(field)) {
			return;
		}

		currentIndex += getWord(row + currentIndex + 1, value, '\r');

		if (!strlen(value)) {
			return;
		}

		insertFields(headers, field, value);
	}

	static void insertFields(Headers* headers, char* field, char* value) {
		if (!strcmp(field, "Host")) {
			strcpy(headers->m_Host, value);
		}
	}

	char* ToString() {
		char returnHeaders[MAX_BUFEER] = { '\0' };
		string headers;

		if (m_Content_Type && strlen(m_Content_Type)) {
			headers.append("Content-Type: ");
			headers.append(m_Content_Type);
			headers.append("\r\n");
		}

		if (m_Content_Length && strlen(m_Content_Length)) {
			headers.append("Content-Length: ");
			headers.append(m_Content_Length);
			headers.append("\r\n");
		}

		if (m_Content_Language && strlen(m_Content_Language)) {
			headers.append("Content-Language: ");
			headers.append(m_Content_Language);
			headers.append("\r\n");
		}

		if (headers.length()) {
			strcpy(returnHeaders, headers.c_str());
		}

		return returnHeaders;
	}
};