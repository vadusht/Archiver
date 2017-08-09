#pragma once
#include <string>
#include <io.h>
#include <iostream>
#include "Contents.h"
#include "ICompression.h"
#include "CompHuffman.h"
#include "Directory.h"
#include "File.h"

class Archiving
{
	void RecreateDir(const std::string& path_from, const std::string& path_to, Ñontents& obj, ICompression* comp, const std::size_t ind_method);
	void RecursiveBypassToCompress(const std::string& path_from, const std::string& path_to, ICompression*, const std::size_t);
	void RecursiveBypassToDecompress(const std::string& path_from, const std::string& path_to, ICompression* comp, const std::size_t ind_method);
	void GetAllPaths(const std::string&, Ñontents&, const std::size_t);
	void GetPrimaryDir(const std::string&, Ñontents&);
public:
	void FillContents(const std::string&, Ñontents&);
	void Compression(const std::string&, const std::string&, Ñontents&, const std::size_t);
	void Decompression(const std::string&, const std::string&, Ñontents&, const std::size_t);
	Archiving();
	~Archiving();
};

