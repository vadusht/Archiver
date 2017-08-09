#include "stdafx.h"
#include "File.h"

void File::Create(const std::string& path)
{
	std::ofstream fout(path);
	fout.close();
}

void File::Delete(const std::string& path)
{
	::SetFileAttributesA(path.c_str(), FILE_ATTRIBUTE_NORMAL);

	_set_errno(0);
	if (remove(path.c_str()))
	{
		std::cout << "Error " << errno << ": ";
		perror("");
	}
}

void File::GetSize(const std::string& path, unsigned _int64& size)
{
	std::ifstream fin(path);
	fin.seekg(0, std::ios::end);
	size = fin.tellg();
	fin.seekg(0, std::ios::beg);
}

void File::GetSize(std::ifstream& fin, unsigned _int64& size)
{
	fin.seekg(0, std::ios::end);
	size = fin.tellg();
	fin.seekg(0, std::ios::beg);
}





