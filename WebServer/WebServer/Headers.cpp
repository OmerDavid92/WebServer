class Headers
{
public:
	char m_Host[255];
	char m_Lang[3];
	


	Headers();
	~Headers();
	static Headers Parse(char i_Headers[255]) {
		char header[255];
		for (int i = 0; i < 255 && i_Headers[i]!='\n'; i++) {
			if (i_Headers[i] != '\n' && i_Headers[i] != ':') {
				header[i] = i_Headers[i];
			}

		}


	}


private:

};

Headers::Headers()
{

}

Headers::~Headers()
{

}
