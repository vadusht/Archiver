#include "stdafx.h"
#include "Archiving.h"



Archiving::Archiving()
{
}


Archiving::~Archiving()
{
}



void Archiving::FillContents(const std::string& path, Ñontents& obj)
{
	GetPrimaryDir(path, obj);
}

void Archiving::Decompression(const std::string& path_from, const std::string& path_to, Ñontents& obj, const std::size_t ind_method)
{
	std::ifstream fin(path_from, std::ios_base::binary);
	fin >> obj;

	ICompression* comp = { new CompHuffman/*, new CompRLE */ };

	RecreateDir(path_from, path_to, obj, comp, ind_method);
	/*RecursiveBypassToCompress(fin, p)*/
}

void Archiving::Compression(const std::string& path_from, const std::string& path_to, Ñontents& obj, const std::size_t ind_method) 
{
	FillContents(path_from, obj);
	
	std::string compressFile = path_to + path_from.substr(path_from.find_last_of('\\')) + ".myrar";
	std::ofstream fout(compressFile);

	fout << obj;
	fout.close();

	ICompression* comp = { new CompHuffman/*, new CompRLE */};

	RecursiveBypassToCompress(path_from, compressFile, comp, ind_method);
}

void Archiving::GetPrimaryDir(const std::string& path, Ñontents& obj)
{
	const std::size_t POS = path.find_last_of('\\') + 1;
	obj.queueForDir.push(path.substr(POS));

	GetAllPaths(path, obj, POS);
}

void Archiving::GetAllPaths(const std::string& path, Ñontents& obj, const std::size_t POS)
{
	std::string path_tmp = path + "\\*.*";

	_set_errno(0);

	_finddatai64_t fd = { 0 };
	intptr_t handle = _findfirsti64(path_tmp.c_str(), &fd);

	if (handle == -1)
	{
		std::cout << "Error " << errno << ": ";
		perror("");
		return;
	}

	do
	{
		if (fd.name == std::string(".") || fd.name == std::string("..")) continue;

		std::string path_next = path + '\\' + fd.name;

		if (fd.attrib & _A_SUBDIR)
		{
			obj.queueForDir.push(path_next.substr(POS));
			GetAllPaths(path_next, obj, POS);
		}
		else
			obj.queueForFiles.push(path_next.substr(POS));

	} while (!_findnexti64(handle, &fd));

	_findclose(handle);
}

void Archiving::RecursiveBypassToCompress(const std::string& path_from, const std::string& path_to, ICompression* comp, const std::size_t ind_method)
{

	std::string path_tmp = path_from + "\\*.*";

	_set_errno(0);

	_finddatai64_t fd = { 0 };
	intptr_t handle = _findfirsti64(path_tmp.c_str(), &fd);

	if (handle == -1)
	{
		std::cout << "Error " << errno << ": ";
		perror("");
		return;
	}

	do
	{
		if (fd.name == std::string(".") || fd.name == std::string("..")) continue;

		std::string path_next = path_from + '\\' + fd.name;

		if (fd.attrib & _A_SUBDIR)
			RecursiveBypassToCompress(path_next, path_to, comp, ind_method);
		else
		{
			std::ifstream fin(path_next, std::ios_base::binary);
			std::ofstream fout(path_to, std::ios_base::binary | std::ios_base::app);

			comp->Compress(fin, fout);

			fin.close();
			fout.close();
		}

	} while (!_findnexti64(handle, &fd));

	_findclose(handle);
}

void Archiving::RecursiveBypassToDecompress(const std::string& path_from, const std::string& path_to, ICompression* comp, const std::size_t ind_method)
{

	std::string path_tmp = path_from + "\\*.*";

	_set_errno(0);

	_finddatai64_t fd = { 0 };
	intptr_t handle = _findfirsti64(path_tmp.c_str(), &fd);

	if (handle == -1)
	{
		std::cout << "Error " << errno << ": ";
		perror("");
		return;
	}

	do
	{
		if (fd.name == std::string(".") || fd.name == std::string("..")) continue;

		std::string path_next = path_from + '\\' + fd.name;

		if (fd.attrib & _A_SUBDIR)
			RecursiveBypassToDecompress(path_next, path_to, comp, ind_method);
		else
		{
			std::ifstream fin(path_next, std::ios_base::binary);
			std::ofstream fout(path_to, std::ios_base::binary | std::ios_base::app);

			comp->Compress(fin, fout);

			fin.close();
			fout.close();
		}

	} while (!_findnexti64(handle, &fd));

	_findclose(handle);
}

void Archiving::RecreateDir(const std::string& path_from, const std::string& path_to, Ñontents& obj, ICompression* comp, const std::size_t ind_method)
{
	std::size_t size = obj.queueForDir.size();

	Directory dir;
	for (auto i = std::size_t(0); i < size; i++)
	{
		dir.Create(path_to + '\\' + obj.queueForDir.front());
		obj.queueForDir.pop();
	}

	size = obj.queueForFiles.size();

	File file;
	for (auto i = std::size_t(0); i < size; i++)
	{
		file.Create(path_to + '\\' + obj.queueForFiles.front());
		obj.queueForFiles.pop();
	}
}