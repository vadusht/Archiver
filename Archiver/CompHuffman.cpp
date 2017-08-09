#include "stdafx.h"
#include "CompHuffman.h"
#include <vector>

CompHuffman::CompHuffman()
{
}

CompHuffman::~CompHuffman()
{
}

void CompHuffman::BuildTable(Node* root)
{
	if (root->left != NULL)
	{
		code.push_back(0);
		BuildTable(root->left);
	}

	if (root->right != NULL)
	{
		code.push_back(1);
		BuildTable(root->right);
	}

	if (root->left == NULL && root->right == NULL) table[root->byte] = code;

	if (code.size())
		code.pop_back();
}

void CompHuffman::CreateCharFrequency(std::ifstream& fin)
{
	std::vector<char> vecBuf(4096);
	std::size_t resultRead = 0;

	do
	{
		fin.read(&vecBuf[0], 4096);
		resultRead = fin.gcount();
		for (std::size_t i = 0; i < resultRead; i++)
		{
			unsigned char byte = vecBuf[i];
			charFrequency[byte]++;
		}


	} while (resultRead == 4096);



	/*while (!fin.eof())
	{
		unsigned char byte = fin.get();
		charFrequency[byte]++;
	}*/
}

void CompHuffman::CreateNodes()
{
	for (auto i = charFrequency.begin(); i != charFrequency.end(); i++)
	{
		Node* node = new Node;
		node->byte = i->first;
		node->count = i->second;
		nodes.push_back(node);
	}
}

void CompHuffman::CreateTree()
{
	while (nodes.size() != 1)
	{
		nodes.sort(MyCompare());

		Node* SonLeft = nodes.front();
		nodes.pop_front();
		Node* SonRight = nodes.front();
		nodes.pop_front();

		Node* parent = new Node(SonLeft, SonRight);
		nodes.push_back(parent);
	}
	root = nodes.front();
	BuildTable(root);
}

void CompHuffman::LoadCharFrequency(std::ofstream& fout)
{
	std::size_t size = charFrequency.size();

	fout.write(reinterpret_cast<const char*>(&size), sizeof(size));

	for (auto i : charFrequency)
	{
		fout.write(reinterpret_cast<const char*>(&i.first), sizeof(i.first));
		fout.write(reinterpret_cast<const char*>(&i.second), sizeof(i.second));
	}
}

void CompHuffman::UnloadCharFrequency(std::ifstream& fin)
{
	std::size_t size = 0;

	fin.read(reinterpret_cast<char*>(&size), sizeof(size));

	for (auto i = std::size_t(0); i < size; i++)
	{
		unsigned char buf = 0;
		fin.read(reinterpret_cast<char*>(&buf), sizeof(buf));

		std::size_t count = 0;
		fin.read(reinterpret_cast<char*>(&size), sizeof(size));

		charFrequency[buf] = size;
	}
}

void CompHuffman::Data—ompression(std::ifstream& fin, std::ofstream& fout)
{
	File obj;
	unsigned _int64 size = 0;
	obj.GetSize(fin, size);

	fout.write(reinterpret_cast<const char*>(&size), sizeof(size));

	std::size_t count = 0;
	unsigned char buf = 0;

	std::vector<char> vecBuf(4096);
	std::size_t resultRead = 0;

	do
	{

		fin.read(&vecBuf[0], 4096);
		resultRead = fin.gcount();

		for (std::size_t i = 0; i < resultRead; i++)
		{
			unsigned char tmp_byte = vecBuf[i];
			std::vector<bool> tmp = table[tmp_byte];

			for (auto i = std::size_t(0); i < tmp.size(); i++)
			{
				buf = buf | tmp[i] << (7 - count);
				count++;
				if (count == 8)
				{
					count = 0;
					fout << buf;
					buf = 0;
				}
			}
		}
	} while (resultRead == 4096);


	/*while (!fin.eof())
	{
		unsigned char tmp_byte = fin.get();
		std::vector<bool> tmp = table[tmp_byte];
		for (auto i = std::size_t(0); i < tmp.size(); i++)
		{
			buf = buf | tmp[i] << (7 - count);
			count++;
			if (count == 8)
			{
				count = 0;
				fout << buf;
				buf = 0;
			}
		}
	}*/
}

void CompHuffman::Compress(std::ifstream& fin, std::ofstream& fout)
{
	CreateCharFrequency(fin);
	CreateNodes();
	CreateTree();
	LoadCharFrequency(fout);

	fin.clear();
	Data—ompression(fin, fout);
}

void CompHuffman::Decompress(std::ifstream& fin, std::ofstream& fout)
{
	UnloadCharFrequency(fin);

	CreateNodes();
	CreateTree();

	DataDecompression(fin, fout);
}

void CompHuffman::DataDecompression(std::ifstream& fin, std::ofstream& fout)
{
	unsigned _int64 size = 0;

	fin.read(reinterpret_cast<char*>(&size), sizeof(size));

	Node* p = root;
	std::size_t count = 0;
	unsigned char buf = 0;
	buf = fin.get();
	for (auto i = std::size_t(0); i < size;)
	{
		bool b = buf & (1 << (7 - count));
		if (b) p = p->right;
		else p = p->left;
		if (p->left == nullptr && p->right == nullptr)
		{
			fout << std::hex << p->byte;
			i++;
			p = root;
		}
		count++;
		if (count == 8)
		{
			count = 0;
			buf = fin.get();
		}
	}
}