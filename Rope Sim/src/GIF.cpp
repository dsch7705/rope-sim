#include  "GIF.h"


Frame::~Frame()
{
	free(data);
}
GIF::~GIF()
{
	while (first != nullptr)
	{
		Frame* temp = first->next;
		delete first;
		first = temp;
	}
}
void GIF::RecordFrame(uint8_t* data)
{
	if (first == nullptr)
	{
		first = new Frame(data, w * h * 4);
		last = first;
	}
	else
	{
		last->next = new Frame(data, w * h * 4);
		last = last->next;
	}
}
void GIF::SaveGIF(const std::string& filename)
{
	if (first == nullptr)
	{
		std::cerr << "No gif data to save!\n";
		return;
	}

	MsfGifState gifState = {};
	msf_gif_begin(&gifState, w, h);

	Frame* current = first;
	while (current != nullptr)
	{
		msf_gif_frame(&gifState, current->data, frameTimeCS, 16, w * 4);
		current = current->next;
	}
	MsfGifResult result = msf_gif_end(&gifState);
	if (result.data)
	{
		std::string dir = saveDirectory + filename + ".gif";
		std::ofstream file(dir, std::ios::binary);
		if (!file.is_open())
		{
			std::string err = "Error opening '" + dir + "'";
			perror(err.c_str());
		}
		else
		{
			file.write((char*)result.data, result.dataSize);
			file.close();
		}
	}
	msf_gif_free(result);
};