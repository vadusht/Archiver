#pragma once

#include <direct.h>
#include <io.h>
#include "IFile.h"
#include "File.h"

class Directory :
	public IFile
{
	const std::string defMask = "*.*";
	static const std::size_t BUFSIZE = 4096;
public:
	Directory() = default;
	~Directory() = default;

	virtual void Create(const std::string&) override;
	virtual void Delete(const std::string&) override;
	virtual void GetSize(const std::string&, unsigned _int64&) override;
};

