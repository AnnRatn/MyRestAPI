#pragma once
#include "stdafx.h"

using namespace std;

class NewMyBuff : public std::streambuf {
private:
	vector<char_type> buffer;
	FILE *file;
protected:
	virtual int underflow() override;
public:
	NewMyBuff(size_t _bufsize);

	~NewMyBuff();

	bool open(string fn);

	void close();
};

