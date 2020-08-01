#ifndef TEST_BUILD
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cstdint>
#include "shell/command-line-parser.h"
#include "imaging/bitmap.h"
#include "imaging/bmp-format.h"
#include "imaging/bmp-format.h"
#include <midi.h>
using namespace midi;
using namespace std;
using namespace shell;
using namespace imaging;

void draw_rectangle(Bitmap& bitmap, const Position& pos, const uint32_t& width, const uint32_t& height, const Color& color, const Color& border)
{
	for (uint32_t i = 0; i < width; i++)
	{
		for (uint32_t j = 0; j < height; j++)
		{
			if (i < 1 || j < 1 || i > width - 2 || j > height - 2)
			{
				bitmap[Position(pos.x + i, pos.y + j)] = border;
			}
			else
			{
				bitmap[Position(pos.x + i, pos.y + j)] = color;
			}
		}
	}
}
int getWidth(vector<NOTE> notes)
{
	int lastNote = 0;
	for (NOTE var : notes)
	{
		if (value(var.start + var.duration) > lastNote)
		{
			lastNote = value(var.start + var.duration);

		}

	}
	cout << "Width:  " << lastNote << endl;
	return lastNote;
}

int getLowest(vector<NOTE> notes)
{
	int lowest = 127;
	for (NOTE var : notes)
	{
		if (value(var.note_number) < lowest)
		{
			lowest = value(var.note_number);

		}

	}
	cout << "Lowest note:  " << lowest << endl;
	return lowest;
}

int getHighest(vector<NOTE> notes)
{
	int highest = 0;
	for (NOTE var : notes)
	{
		if (value(var.note_number) > highest)
		{
			highest = value(var.note_number);

		}

	}
	cout << "Highest note:  " << highest << endl;
	return highest;
}
Color rgb_color_code()
{
	double r = rand() % 256;
	double g = rand() % 256;
	double b = rand() % 256;
	if (r == 1 && g == 1 && b == 1)
	{
		g = rand() % 256;
		b = rand() % 256;
		return Color(0, g, b);
	}
	return Color(r, g, b);

}

int main(int argn, char* argv[])
{
	string file;
	string output;

	uint32_t width = 0;
	uint32_t step = 1;
	uint32_t scale = 10;
	uint32_t height = 16;

	CommandLineParser parser;
	parser.add_argument(string("-w"), &width);
	parser.add_argument(string("-d"), &step);
	parser.add_argument(string("-s"), &scale);
	parser.add_argument(string("-h"), &height);
	parser.process(vector<string>(argv + 1, argv + argn));
	vector<string> arguments = parser.positional_arguments();
	//non bound arguments (input and output)
	if (arguments.size() != 2) {
		cout << "please provide an input file" << endl;
		return 0;
	}
	if (arguments.size() >= 1)
	{
		file = arguments[0];
	}
	if (arguments.size() >= 2)
	{
		
		output = arguments[1];
	}

	ifstream in(file, ifstream::binary);
	vector<NOTE> notes = read_notes(in);
	uint32_t mapwidth = getWidth(notes) / scale;
	if (width == 0)
	{
		width = mapwidth;
	}
	int lowest = getLowest(notes);
	int highest = getHighest(notes);
	cout << "Bitmap size :   " << mapwidth << " X " << (highest - lowest + 1) * height << endl;
	Bitmap bitmap(mapwidth, 127 * height);

	for (int i = 0; i <= 127; i++) {
		for (NOTE n : notes) {
			if (n.note_number == NoteNumber(i)) {
				draw_rectangle(bitmap, Position(value(n.start) / scale, (127 - i) * height), value(n.duration) / scale, height, rgb_color_code(), Color(0, 0, 0));
			}
		}
	}
	cout << "Notes have been read" << endl;

	// Zwarte randen wegknippen
	bitmap = *bitmap.slice(0, height * (127 - highest), mapwidth, (highest - lowest + 1) * height).get();
	// opslaan
	for (int i = 0; i <= mapwidth - width; i += step)
	{
		Bitmap tempMap = *bitmap.slice(i, 0, width, (highest - lowest + 1) * height).get();
		stringstream numbers;
		numbers << setfill('0') << setw(5) << (i / step);
		string outfile = output;
		save_as_bmp(outfile.replace(outfile.find("%d"), 2, numbers.str()), tempMap);

		cout << "Frame: " << (i / step) << " created" << endl;
	}

}
#endif
