#pragma once
#include <iostream>
class IFile
{
public:
	IFile() = default;
	~IFile() = default;

	virtual void Create(const std::string& path) = 0;
	virtual void Delete(const std::string& path) = 0;
	virtual void GetSize(const std::string& path, unsigned _int64& size) = 0;
};

