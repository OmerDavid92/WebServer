#define _CRT_SECURE_NO_WARNINGS
#include "StrUtilNetwork.cpp"

class Headers
{
public:
	char m_Host[255] = { 0 };
	char m_Lang[3] = "he";
	
	Headers() {};

	static Headers* Parse(char i_Headers[255]) {
		Headers* headers = new Headers();
		char row[255] = { '\0' };
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
		char field[255] = { '\0' };
		char value[255] = { '\0' };

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
		else if (!strcmp(field, "Lang")) {
			strcpy(headers->m_Lang, value);
		}
	}
};