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
	void RecreateDir(const std::string& path_from, const std::string& path_to, �ontents& obj, ICompression* comp, const std::size_t ind_method);
	void RecursiveBypassToCompress(const std::string& path_from, const std::string& path_to, ICompression*, const std::size_t);
	void RecursiveBypassToDecompress(const std::string& path_from, const std::string& path_to, ICompression* comp, const std::size_t ind_method);
	void GetAllPaths(const std::string&, �ontents&, const std::size_t);
	void GetPrimaryDir(const std::string&, �ontents&);
public:
	void FillContents(const std::string&, �ontents&);
	void Compression(const std::string&, const std::string&, �ontents&, const std::size_t);
	void Decompression(const std::string&, const std::string&, �ontents&, const std::size_t);
	Archiving();
	~Archiving();
};

