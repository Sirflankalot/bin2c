//
// bin2c.cpp
// bin2c - Convert binary file into c array
//
// Created by Connor Fitzgerald on 2017-07-16
// BSD-2 License
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

struct binary_file {
	binary_file(const char* fn, const char* an) : filename(fn), array_name(an){};
	const char* filename;
	const char* array_name;
};

int usage() {
	std::cerr << "bin2c.cpp [-h output_header.hpp] [-o output_source] [-l input_bytes_per_line] "
	             "[-a array_name filename]... \n\n"
	          << "-o  output file for the arrays\n"
	          << "-h  if a header name is provided, extern declarations\n    for all arrays will "
	             "be put in it\n"
	          << "-l  amount of (source) bytes to put on one line (4 output bytes per input byte)\n"
	          << "-a  add array\n";
	return 1;
}

std::string file_contents(const char* filename) {
	std::ifstream f(filename, std::ios::binary);
	std::string str;

	if (!f.is_open()) {
		std::cerr << "Can't open " << filename << "\n";
		return std::string();
	}

	f.seekg(0, std::ios::end);
	str.reserve(std::size_t(f.tellg()));
	f.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

	return str;
}

void bin2c(const char* output_source_name, const char* output_header_name, int bytes, std::vector<binary_file>& files) {
	std::unique_ptr<std::ostream> source;
	std::unique_ptr<std::ostream> header;

	bool using_source = output_source_name != nullptr;
	bool using_header = output_header_name != nullptr;

	if (using_source) {
		source = std::make_unique<std::ofstream>(output_source_name, std::ios::binary);
	}
	if (using_header) {
		header = std::make_unique<std::ofstream>(output_header_name, std::ios::binary);
		(*header) << "#pragma once\n";
	}

	for (binary_file& f : files) {
		auto contents = file_contents(f.filename);
		contents.push_back('\0');
		auto length = contents.length();

		if (using_header) {
			(*header) << "extern unsigned char " << f.array_name << "[" << length + 1 << "];\n";
		}
		(*source) << "unsigned char " << f.array_name << "[" << std::dec << length + 1 << "] = {\n\t";
		int byte_count = 0;
		(*source) << std::hex << std::setfill('0');
		for (char c : contents) {
			int num = uint8_t(c);
			(*source) << "0x" << std::setw(2) << num << ", ";
			if (byte_count % bytes == bytes - 1) {
				(*source) << "\n\t";
			}
			byte_count++;
		}
		(*source) << "\n};\n";
	}
}

int main(int argc, char** argv) {
	const char* output_source_name = "bin2coutput.c";
	const char* output_header_name = nullptr;
	int bytes_per_line = 16;

	std::vector<binary_file> files_to_process;

	// Iterate through arguments
	for (int i = 0; i < argc; ++i) {
		// Parse options
		if (argv[i][0] == '-') {
			if (argv[i][1] == '\0') {
				return usage();
			}
			switch (argv[i++][1]) {
				case 'h':
					output_header_name = argv[i];
					break;
				case 'o':
					output_source_name = argv[i];
					break;
				case 'l':
					bytes_per_line = atoi(argv[i]);
					break;
				case 'a':
					if (i + 1 < argc) {
						files_to_process.emplace_back(argv[i + 1], argv[i]);
					}
					else {
						return usage();
					}
					break;
			}
		}
	}

	if (files_to_process.size() == 0) {
		return usage();
	}

	bin2c(output_source_name, output_header_name, bytes_per_line, files_to_process);
}
