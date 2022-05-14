#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Headers.cpp"
using namespace std;

class Request
{
public:
	int m_RequestLength;
	char m_Method[10] = { 0 };
	char m_URI[500] = { 0 };
	char m_Version[10] = { 0 };
	char m_Lang[3] = "he";
	Headers* m_Headers = nullptr;
	char m_Body[500] = { 0 };

	Request(int requestLength, char method[500], char uri[500], char version[500]) {
		m_RequestLength = requestLength;
		strcpy(m_Method, method);
		strcpy(m_URI, uri);
		strcpy(m_Version, version);
	};

	static Request* Parse(char i_Request[500]) {
		Request* request = nullptr;
		char row[500] = { '\0' };
		char headersStr[500] = { '\0' };
		int currentIndex = 0;
		int headersIndexStart = 0, headersIndexEnd = 0;
		char body[500] = { '\0' };
		int requestLength = strlen(i_Request);

		currentIndex += getRow(i_Request + currentIndex, row);
		headersIndexStart = currentIndex;
		request = ParsefirstRow(requestLength, row);

		if (!request) {
			return request;
		}

		currentIndex += getRow(i_Request + currentIndex, row);

		while (strcmp(row, "\0")) {
			currentIndex += getRow(i_Request + currentIndex, row);
		}

		headersIndexEnd = currentIndex;
		strcpyByIndexes(i_Request, headersStr, headersIndexStart, headersIndexEnd);
		request->m_Headers = Headers::Parse(headersStr);
		strcpyByIndexes(i_Request, body, currentIndex, strlen(i_Request));
		
		return request;
	}
	
	static Request* ParsefirstRow(int requestLength, char* row) {
		Request* request = nullptr;
		int firstLineCurrentIndex = 0;
		int uriAndQueryCurrentIndex = 0;
		char method[500] = { '\0' };
		char uriAndQuery[500] = { '\0' };
		char uri[500] = { '\0' };
		char version[500] = { '\0' };
		char query[500] = { '\0' };

		firstLineCurrentIndex += getWord(row + firstLineCurrentIndex, method, ' ');
		
		if (!strlen(method)) {
			cout << "shity c++";
			return request;
		}

		firstLineCurrentIndex += getWord(row + firstLineCurrentIndex, uriAndQuery, ' ');
		uriAndQueryCurrentIndex += getWord(uriAndQuery + uriAndQueryCurrentIndex, uri, '?');

		if (!strlen(uri)) {
			cout << "shity c++";
			return request;
		}

		firstLineCurrentIndex += getWord(row + firstLineCurrentIndex, version, ' ');

		if (!strlen(version)) {
			cout << "shity c++";
			return request;
		}

		request = new Request(requestLength, method, uri, version);
		uriAndQueryCurrentIndex += getWord(uriAndQuery + uriAndQueryCurrentIndex, query, ' ');

		if (strlen(query)) {
			ParseQueryString(request, query);
		}

		return request;
	}

	static void ParseQueryString(Request* request, char* row) {
		int currentIndex = 0;
		char field[500] = { '\0' };
		char value[500] = { '\0' };

		currentIndex += getWord(row + currentIndex, field, '=');

		if (!strlen(field)) {
			return;
		}

		currentIndex += getWord(row + currentIndex, value, '&');

		if (!strlen(value)) {
			return;
		}

		insertFields(request, field, value);
	}

	static void insertFields(Request* request, char* field, char* value) {
		if (!strcmp(field, "lang")) {
			strcpy(request->m_Lang, value);
		}
	}
};