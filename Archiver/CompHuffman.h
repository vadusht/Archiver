#pragma once
#include "ICompression.h"
#include "File.h"

class CompHuffman :
	public ICompression
{
	struct Node
	{
		std::size_t count;
		unsigned char byte;
		Node *left, *right;

		Node() :left{ nullptr }, right{ nullptr } {}

		Node(Node* left, Node* right) :left{ left }, right{ right }, count{ left->count + right->count } {}
	};

	struct MyCompare
	{
		bool operator() (const Node* left, const Node* right) const { return left->count < right->count; }
	};

	std::vector<bool> code;
	std::map<unsigned char, std::vector<bool>> table;
	void BuildTable(Node* root);
	Node* root = nullptr;
	std::map<unsigned char, std::size_t> charFrequency;
	void CreateCharFrequency(std::ifstream& fin);

	void LoadCharFrequency(std::ofstream& fout);
	void UnloadCharFrequency(std::ifstream& fout);

	std::list<Node*> nodes;
	void CreateNodes();
	void CreateTree();
	void Data—ompression(std::ifstream& fin, std::ofstream& fout);
	void DataDecompression(std::ifstream& fin, std::ofstream& fout);
public:
	virtual void Compress(std::ifstream& fin, std::ofstream& fout) override;
	virtual void Decompress(std::ifstream& fin, std::ofstream& fout) override;
	CompHuffman();
	~CompHuffman();
};

