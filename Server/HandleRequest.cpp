#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_BUFEER 2000
#include <fstream>
#include <string>
#include "Request.cpp"
#include "Response.cpp"

static Response* HandleGet(Request* i_Request) {
	Response* response = nullptr;
	Headers* headers = nullptr;
	char path[MAX_BUFEER] = "./Pages/";
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
	strcpy(headers->m_Content_Language, i_Request->m_Lang);
	strcpy(headers->m_Content_Type, "txt/html; charset=UTF-8");
	lengthStr = to_string(bodyLength);
	strcpy(headers->m_Content_Length, lengthStr.c_str());
	response->m_Headers = headers;

	return response;
}

static Response* HandleHead(Request* i_Request) {
	Response* response = nullptr;

	response = HandleGet(i_Request);

	if (strlen(response->m_Body)) {
		response->m_Body[0] = '\0';
	}

	return response;
}

static char* HandleRequest(Request* i_Request) {
	Response* response = nullptr;
	char* serverOutput = nullptr;
	
	if (!strcmp(i_Request->m_Method, "GET")) {
		response = HandleGet(i_Request);
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
		response = HandleHead(i_Request);
	}
	else if (!strcmp(i_Request->m_Method, "OPTIONS")) {
		//
	}
	else if (!strcmp(i_Request->m_Method, "TRACE")) {
		//
	}

	if (response) {
		serverOutput = response->ToString();
	}

	return serverOutput;
}