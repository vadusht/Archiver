#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>

class ICompression
{
public:
	virtual void Compress(std::ifstream& fin, std::ofstream& fout) = 0;
	virtual void Decompress(std::ifstream& fin, std::ofstream& fout) = 0;
	ICompression();
	~ICompression();
};

