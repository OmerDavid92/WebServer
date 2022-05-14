#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "Request.cpp"

static char* HandleGet(Request* i_Request) {
	char path[255] = "./Pages/";
	char content[255] = { '\0' };
	char currentChar = '\0';
	int currentIndex = 0;

	strcat(path, i_Request->m_Lang);
	strcat(path, i_Request->m_URI);

	ifstream file(path);

	if (file.good()) {
		while (!file.eof())
		{
			currentChar = file.get();
			content[currentIndex] = currentChar;
			currentIndex++;
		}

		content[currentIndex] = '\0';
	}

	return content;
}

static char* HandleRequest(Request* i_Request) {
	char* serverOutput = nullptr; 
	
	if (!strcmp(i_Request->m_Method, "GET")) {
		serverOutput = HandleGet(i_Request);
	}
	else if (!strcmp(i_Request->m_Method, "POST")) {
		//serverOutput = HandlePost(i_Request);
	}
	else if (!strcmp(i_Request->m_Method, "PUT")) {
		//serverOutput = HandlePut(i_Request);

	}
	else if (!strcmp(i_Request->m_Method, "DELETE")) {
		//
	}
	else if (!strcmp(i_Request->m_Method, "HEAD")) {
		//
	}
	else if (!strcmp(i_Request->m_Method, "OPTIONS")) {
		//
	}
	else if (!strcmp(i_Request->m_Method, "TRACE")) {
		//
	}

	return serverOutput;
}