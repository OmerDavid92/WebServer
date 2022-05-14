#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_BUFEER 2000
#include <iostream>
#include <string.h>
#include "Headers.cpp"
using namespace std;

class Response
{
public:
	char m_StatusCode[10] = { 0 };
	char m_StatusWord[MAX_BUFEER] = { 0 };
	char m_Version[10] = { 0 };
	Headers* m_Headers = nullptr;
	char m_Body[MAX_BUFEER] = { 0 };

	Response(const char statusCode[10], const char statusWord[MAX_BUFEER], const char version[10]) {
		strcpy(m_StatusCode, statusCode);
		strcpy(m_StatusWord, statusWord);
		strcpy(m_Version, version);
	};

	char* ToString() {
		char headers[MAX_BUFEER] = { '\0' };
		char returnResponse[MAX_BUFEER] = { '\0' };
		string response;

		response.append(m_Version);
		response.append(" ");
		response.append(m_StatusCode);
		response.append(" ");
		response.append(m_StatusWord);
		response.append("\r\n");

		if (m_Headers) {
			strcpy(headers, m_Headers->ToString());
			response.append(headers);
		}

		response.append("\r\n");
		response.append(m_Body);
		strcpy(returnResponse, response.c_str());

		return returnResponse;
	}
};