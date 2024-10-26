#pragma once

//std
#include <cstdint>

namespace canvas
{
	class IBO
	{
	public:
		//constructor
		IBO(void);

		//destructor
		~IBO(void);

		//data
		uint32_t id(void) const;

		uint32_t size(uint32_t);
		uint32_t size(void) const;

		uint32_t* data(void);
		uint32_t* data(const uint32_t*);
		const uint32_t* data(void) const;

		//GPU
		void setup(void);

		void bind(void) const;
		static void unbind(void);

		void transfer(void) const;

	private:
		//data
		uint32_t m_id;
		uint32_t m_size;
		uint32_t* m_data;
	};
}