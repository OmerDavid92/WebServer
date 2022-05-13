#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Headers.cpp"
using namespace std;

class Request
{
public:
	char m_Method[10] = { 0 };
	char m_URI[255] = { 0 };
	char m_Version[10] = { 0 };
	Headers* m_Headers = nullptr;
	char m_Body[255] = { 0 };

	Request(char method[255], char uri[255], char version[255]) {
		strcpy(m_Method, method);
		strcpy(m_URI, uri);
		strcpy(m_Version, version);
	};

	static Request* Parse(char i_Request[255]) {
		Request* request = nullptr;
		char row[255] = { '\0' };
		char headersStr[255] = { '\0' };
		int currentIndex = 0;
		int headersIndexStart = 0, headersIndexEnd = 0;
		char body[255] = { '\0' };

		currentIndex += getRow(i_Request + currentIndex, row);
		headersIndexStart = currentIndex;
		request = ParsefirstRow(row);

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
	}
	
	static Request* ParsefirstRow(char* row) {
		int currentIndex = 0;
		char method[255] = { '\0' };
		char uri[255] = { '\0' };
		char version[255] = { '\0' };

		currentIndex += getWord(row + currentIndex, method, ' ');
		
		if (!strlen(method)) {
			cout << "shity c++";
			return nullptr;
		}

		currentIndex += getWord(row + currentIndex, uri, ' ');

		if (!strlen(uri)) {
			cout << "shity c++";
			return nullptr;
		}

		currentIndex += getWord(row + currentIndex, version, ' ');

		if (!strlen(version)) {
			cout << "shity c++";
			return nullptr;
		}

		return new Request(method, uri, version);
	}
};