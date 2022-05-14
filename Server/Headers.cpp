#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "StrUtilNetwork.cpp"
using namespace std;

class Headers
{
public:
	char m_Host[100] = { 0 };
	char m_Conntent_Type[100] = { 0 };
	char m_Conntent_Length[100] = { 0 };
	char m_Conntent_Language[100] = { 0 };
	
	Headers() {};

	static Headers* Parse(char i_Headers[500]) {
		Headers* headers = new Headers();
		char row[500] = { '\0' };
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
		char field[500] = { '\0' };
		char value[500] = { '\0' };

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
		char returnHeaders[500] = { '\0' };
		string headers;

		if (m_Conntent_Type && strlen(m_Conntent_Type)) {
			headers.append("Content-Type: ");
			headers.append(m_Conntent_Type);
			headers.append("\r\n");
		}

		if (m_Conntent_Length && strlen(m_Conntent_Length)) {
			headers.append("Content-Length: ");
			headers.append(m_Conntent_Length);
			headers.append("\r\n");
		}

		if (m_Conntent_Language && strlen(m_Conntent_Language)) {
			headers.append("Content-Language: ");
			headers.append(m_Conntent_Language);
			headers.append("\r\n");
		}

		if (headers.length()) {
			strcpy(returnHeaders, headers.c_str());
		}

		return returnHeaders;
	}
};