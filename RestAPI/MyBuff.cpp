#include "stdafx.h"
#include "MyBuff.h"


int MyBuff::overflow(int c) {
	if (out->good() && c != traits_type::eof()) {
		*pptr() = c; //тут нам пригодился 1 "лишний" символ, убранный в конструкторе
		pbump(1); //смещаем указатель позиции буфера на реальный конец буфера
		return sync() == 0 ? c : traits_type::eof();
	}

	return traits_type::eof();
}

int MyBuff::sync() {
	if (pptr() == pbase()) //если буфер пуст, то и синхронизировать нечего
		return 0;

	ptrdiff_t sz = pptr() - pbase(); //вычисляем, сколько символов записано в буффер

									 //заворачиваем буфер в наш блок
	out->write(pbase(), sz);

	if (out->good()) {
		pbump(-sz); //при успехе перемещаем указатель позиции буфера в начало
		return 0;
	}

	return -1;
}

MyBuff::MyBuff(std::ofstream &_out, std::size_t _bufsize)
		: out(&_out)
		, buffer(_bufsize)
	{
		char_type *buf = buffer.data();
		setp(buf, buf + (buffer.size() - 1)); // -1 для того, чтобы упростить реализацию overflow()
	}

MyBuff::~MyBuff() {
}
