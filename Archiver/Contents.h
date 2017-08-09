#pragma once
#include <queue>
#include <string>
#include <fstream>

struct Ñontents
{
	std::queue<std::string> queueForDir;
	std::queue<std::string> queueForFiles;

	friend std::ofstream& operator << (std::ofstream& fout, Ñontents& obj)
	{
		auto size = obj.queueForDir.size();
		fout.write(reinterpret_cast<const char*>(&size), sizeof(size));

		for (auto i = std::size_t(0); i < size; i++)
		{
			auto len = obj.queueForDir.front().length();
			fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
			fout.write(obj.queueForDir.front().c_str(), obj.queueForDir.front().length());
			obj.queueForDir.pop();
		}

		size = obj.queueForFiles.size();
		fout.write(reinterpret_cast<const char*>(&size), sizeof(size));
		
		for (auto i = std::size_t(0); i < size; i++)
		{
			auto len = obj.queueForFiles.front().length();
			fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
			fout.write(obj.queueForFiles.front().c_str(), obj.queueForFiles.front().length());
			obj.queueForFiles.pop();
		}
		return fout;
	}

	friend std::ifstream& operator >> (std::ifstream& fin, Ñontents& obj)
	{
		std::size_t size = 0;
		fin.read(reinterpret_cast<char*>(&size), sizeof(size));

		for (auto i = std::size_t(0); i < size; i++)
		{
			std::size_t len = 0;
			fin.read(reinterpret_cast<char*>(&len), sizeof(len));
			std::string tmp(len, '\0');
			fin.read(&tmp[0], len);
			obj.queueForDir.push(tmp);
		}

		fin.read(reinterpret_cast<char*>(&size), sizeof(size));
		for (auto i = std::size_t(0); i < size; i++)
		{
			std::size_t len = 0;
			fin.read(reinterpret_cast<char*>(&len), sizeof(len));
			std::string tmp(len, '\0');
			fin.read(&tmp[0], len);
			obj.queueForFiles.push(tmp);
		}
		return fin;
	}

	void Show() 
	{
		std::size_t size = queueForDir.size();
		for (auto i = std::size_t(0); i < size; i++)
		{
			std::cout << queueForDir.front() << std::endl;
			queueForDir.pop();
		}

		std::cout << std::endl;

		size = queueForFiles.size();
		for (auto i = std::size_t(0); i < size; i++)
		{
			std::cout << queueForFiles.front() << std::endl;
			queueForFiles.pop();
		}

		std::cout << std::endl;
	}
};