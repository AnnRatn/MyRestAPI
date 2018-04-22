#include "stdafx.h"
#include "NewMyBuff.h"


int NewMyBuff::underflow() {
	if (!file)
		return traits_type::eof();

	if (gptr() < egptr()) //���� ����� �� ����, ������ ������� ������
		return *gptr();

	char_type *start = eback();
	//������ �� ������ ��������, ��� ������� �����
	size_t rd = fread(start, sizeof(char_type), buffer.size(), file);
	//��������� ������ ������ �� ������, ��� ���� ������� ��������
	setg(start, start, start + rd);

	return rd > 0 ? *gptr() : traits_type::eof();
}
NewMyBuff::NewMyBuff(size_t _bufsize)
		: buffer(_bufsize), file(nullptr)
	{
		char_type *start = buffer.data();
		char_type *end = start + buffer.size();
		setg(start, end, end); //������������� eback = start, gptr = end, egptr = end
							   //�.�. gptr == egptr, ����� �� ����� ���� � ����� �������� ��� ������ ������� ������
	}

NewMyBuff::~NewMyBuff() {
		close();
	}

bool NewMyBuff::open(string fn) {
	close();
	file = fopen(fn.c_str(), "r");
	return file != nullptr;
}

void NewMyBuff::close() {
	if (file) {
		fclose(file);
		file = nullptr;
	}
}