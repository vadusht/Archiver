// Archiver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CompHuffman.h"
#include "Directory.h"
#include "File.h"
#include "Archiving.h"
#include "Contents.h"
#include <ctime>

int main()
{

	unsigned int start_time = clock();
	setlocale(LC_ALL, "rus");
	Ñontents obj;
	Archiving obj1;

	/*obj1.Compression("D:\\Programming\\C", "D:\\Your", obj, 1);*/
	obj1.Decompression("D:\\Your\\C.myrar", "D:\\Library", obj, 1);
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	std::cout << search_time / 1000 << std::endl;
	/*obj1.Decompression("D:\\Your\\Còðîêè.myrar", "D:\\Library", obj, 1);*/
	/*std::ofstream fout("D:\\My.bin", std::ios_base::binary);
	fout << obj;*/

	//std::ifstream fin("D:\\My.bin", std::ios_base::binary);
	//fin >> obj;

	//obj.Show();
	
    return 0;
}

