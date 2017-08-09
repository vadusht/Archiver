#pragma once
#include <Windows.h>
#include <fstream>
#include "IFile.h"

class File :
	public IFile
{
public:
	File() = default;
	~File() = default;

	virtual void Create(const std::string&) override;
	virtual void Delete(const std::string&) override;
	virtual void GetSize(const std::string&, unsigned _int64&) override;
	void GetSize(std::ifstream&, unsigned _int64&);
};

