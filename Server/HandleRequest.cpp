#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include "Request.cpp"
#include "Response.cpp"

static Response* HandleGet(Request* i_Request) {
	Response* response = nullptr;
	Headers* headers = nullptr;
	char path[500] = "./Pages/";
	int bodyLength = 0;
	string lengthStr;
	
	strcat(path, i_Request->m_Lang);
	strcat(path, i_Request->m_URI);
	ifstream file(path);

	if (file.good()) {
		string fileContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		response = new Response("200", "OK", i_Request->m_Version);
		strcpy(response->m_Body, fileContent.c_str());
		bodyLength = strlen(response->m_Body);
	}
	else {
		response = new Response("404", "NOT FOUND", i_Request->m_Version);
	}

	headers = new Headers();
	strcpy(headers->m_Conntent_Language, i_Request->m_Lang);
	strcpy(headers->m_Conntent_Type, "txt");
	lengthStr = to_string(bodyLength);
	strcpy(headers->m_Conntent_Length, lengthStr.c_str());
	response->m_Headers = headers;

	return response;
}

static char* HandleRequest(Request* i_Request) {
	Response* reaponse = nullptr;
	char* serverOutput = nullptr;
	
	if (!strcmp(i_Request->m_Method, "GET")) {
		reaponse = HandleGet(i_Request);
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

	if (reaponse) {
		serverOutput = reaponse->ToString();
	}

	return serverOutput;
}