#include "Request.cpp"

static char* HandleRequest(Request* i_Request) {
	char* serverOutput; 
	
	if (i_Request->m_Method == "GET") {
		serverOutput = HandleGet(i_Request);
	}
	else if (i_Request->m_Method == "POST") {
		//serverOutput = HandlePost(i_Request);
	}
	else if (i_Request->m_Method == "PUT") {
		//serverOutput = HandlePut(i_Request);

	}
	else if (i_Request->m_Method == "DELETE") {
		//
	}
	else if (i_Request->m_Method == "HEAD") {
		//
	}
	else if (i_Request->m_Method == "OPTIONS") {
		//
	}
	else if (i_Request->m_Method == "TRACE") {
		//
	}

	return serverOutput;
}

static char* HandleGet(Request* i_Request) {
	char path[255] = "C:\\Users\\omerd\\source\\repos\\WebServer\\Server\\Pages\\";
	strcat(path, i_Request->m_Headers->m_Lang);
	strcat(path, i_Request->m_URI);





}