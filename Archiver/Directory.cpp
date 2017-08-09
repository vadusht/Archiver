#include "stdafx.h"
#include "Directory.h"

void Directory::Create(const std::string& path)
{
	_set_errno(0);
	if (_mkdir(path.c_str()))
	{
		std::cout << "Error " << errno << ": ";
		perror("");
	}
}

void Directory::Delete(const std::string& path)
{
	if (!_rmdir(path.c_str())) return;

	std::string path_tmp = path + '\\' + defMask;

	_set_errno(0);

	_finddata_t fd = { 0 };
	intptr_t handle = _findfirst(path_tmp.c_str(), &fd);

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
			Delete(path_next);
			_rmdir(path_next.c_str());
		}
		else
		{
			File obj;
			obj.Delete(path_next);
		}
	} while (!_findnext(handle, &fd));

	_findclose(handle);
	_rmdir(path.c_str());
}

void Directory::GetSize(const std::string& path, unsigned _int64& size)
{
	std::string path_tmp = path + '\\' + defMask;

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
			GetSize(path_next, size);
		else
			size += fd.size;

	} while (!_findnexti64(handle, &fd));

	_findclose(handle);
}

