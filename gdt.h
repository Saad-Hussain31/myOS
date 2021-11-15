#pragma once
#include "types.h"

class GlobalDescriptorTable
{
    public:
	class SegmentDescriptor
	{
		private:
			uint16_t limit_lo; //16 bits for size of segment
			uint16_t base_lo; // 16 bits for pointer to the RAM
			uint8_t base_hi; //8 more bits to pointer to the RAM(high address)
			uint8_t type; //8 bits for access rights
			uint8_t flags_limit_hi; //8 bits for flags
			uint8_t base_vhi; //8 more bits for size of segment
		public:
			/*the constructor takes regular base and limits and 
			 * moves the stuff according to us. this is being done
			 *  manually because its the way its designed*/
			SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
			
			/* methods to return that pointer and limit */
			uint32_t Base();
			uint32_t Limit();
	} __attribute__ ((packed)); //coz we want it to be byte perfect. this stops compiler from optimizing


	/*4 segments spread thruout memory. Not good ITO security,
	 * but its not our concern RN */
	SegmentDescriptor nullSegmentSelector;
	SegmentDescriptor unusedSegmentSelector;
	SegmentDescriptor codeSegmentSelector;
	SegmentDescriptor dataSegmentSelector;

    public:
	GlobalDescriptorTable();
	~GlobalDescriptorTable();

	uint16_t CodeSegmentSelector();
	uint16_t DataSegmentSelector();
};
