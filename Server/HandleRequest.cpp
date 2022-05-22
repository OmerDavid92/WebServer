#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_BUFEER 2000
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Request.cpp"
#include "Response.cpp"

static Response* GetResponseNotFound(char* i_Version) {
	Response* response = nullptr;
	int bodyLength = 0;
	char path[MAX_BUFEER] = "./StaticPages/404.html";
	ifstream file(path);

	if (file.good()) {
		string fileContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		response = new Response("404", "NOT FOUND", i_Version);
		strcpy(response->m_Body, fileContent.c_str());
		bodyLength = strlen(response->m_Body);
	}

	return response;
}

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
	}
	else {
		response = GetResponseNotFound(i_Request->m_Version);
	}

	headers = new Headers();
	strcpy(headers->m_Content_Language, i_Request->m_Lang);
	strcpy(headers->m_Content_Type, "txt/html; charset=UTF-8");
	bodyLength = strlen(response->m_Body);
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

static Response* HandlePost(Request* i_Request) {
	Response* response = new Response("200", "OK", i_Request->m_Version);
	Headers* headers = new Headers();

	strcpy(headers->m_Content_Language, i_Request->m_Lang);
	strcpy(headers->m_Content_Type, "txt/html; charset=UTF-8");
	strcpy(headers->m_Content_Length, "12");
	response->m_Headers = headers;
	strcpy(response->m_Body, "POST worked!");

	cout << "The POST request body was:" << endl;
	cout << i_Request->m_Body << endl;

	return response;
}

static Response* HandleOptions(Request* i_Request) {
	Response* response = new Response("200", "OK", i_Request->m_Version);
	Headers* headers = new Headers();

	strcpy(headers->m_Allow, "HEAD, GET, POST, PUT, DELETE, TRACE");
	strcpy(headers->m_Content_Language, i_Request->m_Lang);
	strcpy(headers->m_Content_Type, "txt/html; charset=UTF-8");
	strcpy(headers->m_Content_Length, "0");
	response->m_Headers = headers;

	return response;
}

static Response* HandleDelete(Request* i_Request) {
	Response* response = nullptr;
	Headers* headers = nullptr;
	char path[MAX_BUFEER] = "./Pages/";
	int bodyLength = 0;
	string lengthStr;

	strcat(path, i_Request->m_Lang);
	strcat(path, i_Request->m_URI);
	ifstream file(path);


	if (file.good()) {
		file.close();
		if (remove(path) == 0) {
			response = new Response("200", "OK", i_Request->m_Version);
		}
		else
		{
			response = new Response("500", "Fuya Server", i_Request->m_Version);
			strcpy(response->m_Body, "500 - Fuya Server");
		}
	}
	else {
		response = GetResponseNotFound(i_Request->m_Version);
	}

	headers = new Headers();
	strcpy(headers->m_Content_Language, i_Request->m_Lang);
	strcpy(headers->m_Content_Type, "txt/html; charset=UTF-8");
	bodyLength = strlen(response->m_Body);
	lengthStr = to_string(bodyLength);
	strcpy(headers->m_Content_Length, lengthStr.c_str());
	response->m_Headers = headers;

	return response;
}

static void writeToFile(char* i_Content, char* i_Path) {
	ofstream myFile;
	myFile.open(i_Path);
	myFile << i_Content;
	myFile.close();
}

static Response* HandlePut(Request* i_Request) {
	Response* response = nullptr;
	Headers* headers = nullptr;
	char path[MAX_BUFEER] = "./Pages/";
	int bodyLength = 0;
	string lengthStr;

	strcat(path, i_Request->m_Lang);
	strcat(path, i_Request->m_URI);
	ifstream file(path);

	if (file.good()) {
		writeToFile(i_Request->m_Body, path);
		response = new Response("200", "OK", i_Request->m_Version);
	}
	else {
		ofstream myfile(path);
		myfile.open(path);
		writeToFile(i_Request->m_Body, path);
		myfile.close();
		response = new Response("201", "Created", i_Request->m_Version);
	}

	
	headers = new Headers();
	strcpy(headers->m_Content_Language, i_Request->m_Lang);
	strcpy(headers->m_Content_Type, "txt/html; charset=UTF-8");
	bodyLength = strlen(response->m_Body);
	lengthStr = to_string(bodyLength);
	strcpy(headers->m_Content_Length, lengthStr.c_str());
	response->m_Headers = headers;

	return response;
}

static Response* HandleTrace(Request* i_Request) {
	Response* response = new Response("200", "OK", i_Request->m_Version);
	Headers* headers = new Headers();
	string lengthStr;

	strcpy(headers->m_Connection, "close");
	strcpy(headers->m_Content_Type, "message/html");
	lengthStr = to_string(strlen(i_Request->m_Body));
	strcpy(headers->m_Content_Length, lengthStr.c_str());
	response->m_Headers = headers;
	strcpy(response->m_Body, i_Request->m_Body);

	return response;
}

static char* HandleRequest(Request* i_Request) {
	Response* response = nullptr;
	char* serverOutput = nullptr;
	
	if (!strcmp(i_Request->m_Method, "GET")) {
		response = HandleGet(i_Request);
	}
	else if (!strcmp(i_Request->m_Method, "POST")) {
		response = HandlePost(i_Request);
	}
	else if (!strcmp(i_Request->m_Method, "PUT")) {
		response = HandlePut(i_Request);
	}
	else if (!strcmp(i_Request->m_Method, "DELETE")) {
		response = HandleDelete(i_Request);
	}
	else if (!strcmp(i_Request->m_Method, "HEAD")) {
		response = HandleHead(i_Request);
	}
	else if (!strcmp(i_Request->m_Method, "OPTIONS")) {
		response = HandleOptions(i_Request);
	}
	else if (!strcmp(i_Request->m_Method, "TRACE")) {
		response = HandleTrace(i_Request);
	}

	if (response) {
		serverOutput = response->ToString();
	}

	return serverOutput;
}