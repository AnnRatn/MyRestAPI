#include "stdafx.h"
#include "MyBuff.h"


int MyBuff::overflow(int c) {
	if (out->good() && c != traits_type::eof()) {
		*pptr() = c; //��� ��� ���������� 1 "������" ������, �������� � ������������
		pbump(1); //������� ��������� ������� ������ �� �������� ����� ������
		return sync() == 0 ? c : traits_type::eof();
	}

	return traits_type::eof();
}

int MyBuff::sync() {
	if (pptr() == pbase()) //���� ����� ����, �� � ���������������� ������
		return 0;

	ptrdiff_t sz = pptr() - pbase(); //���������, ������� �������� �������� � ������

									 //������������ ����� � ��� ����
	out->write(pbase(), sz);

	if (out->good()) {
		pbump(-sz); //��� ������ ���������� ��������� ������� ������ � ������
		return 0;
	}

	return -1;
}

MyBuff::MyBuff(std::ofstream &_out, std::size_t _bufsize)
		: out(&_out)
		, buffer(_bufsize)
	{
		char_type *buf = buffer.data();
		setp(buf, buf + (buffer.size() - 1)); // -1 ��� ����, ����� ��������� ���������� overflow()
	}

MyBuff::~MyBuff() {
}
