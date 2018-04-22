#pragma once
#include "stdafx.h"

class MyBuff : public std::streambuf {
private:
	std::ofstream * out;
	vector<char_type> buffer;
protected:
	virtual int overflow(int c) override;

	virtual int sync() override;

public:
	MyBuff(std::ofstream &_out, size_t _bufsize);

	~MyBuff();
};