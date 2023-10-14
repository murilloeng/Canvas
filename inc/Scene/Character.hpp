#pragma once

namespace canvas
{
	class Font;
}
class FT_FaceRec_;

namespace canvas
{
	class Character
	{
	public:
		//constructors
		Character(void);

		//destructor
		~Character(void);

		//setup
		void setup(FT_FaceRec_*, char);

	private:
		//data
		char m_code;
		int m_offset[2];
		unsigned m_width;
		unsigned m_height;
		unsigned m_advance;
		const unsigned char* m_data;

		//friends
		friend class Font;
	};
}