#include "Utilities.h"

std::string funcs::addSpaces(int size) {
	int m_size = 20 - size;
	std::string ans = " ";
	for (int i = 0; i < m_size; i++) ans.append(" ");
	return ans;
}