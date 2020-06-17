#include "pch.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <thread>

int main(int argc , char* argv[])
{
	SetConsoleTitleA("xor-bin");
        std::cout << "- starting xor-bin" << std::endl; 

	DeleteFileA("out");

	std::thread thread_object([&]() 
	{
		auto xor_key = 34891223;
		auto add_statist = 1;

		std::ifstream input(argv[1], std::ios::binary);
		std::ofstream output_xored(std::string("out"), std::ios::binary);

		std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
		std::cout << "in  :" << buffer.size() << std::endl;

		input.close();

		for (auto c = 0; c < buffer.size(); c++) buffer[c] ^= xor_key;
		for (auto c = 0; c < buffer.size(); c++) buffer[c] += add_statist;

		for (auto obj : buffer) output_xored.write((const char*)&obj, sizeof(obj));
		output_xored.close();

		std::cout << "out :" << buffer.size() << std::endl;

	});

	thread_object.join();
	DeleteFileA(argv[1]);
	
	return 1;
}
