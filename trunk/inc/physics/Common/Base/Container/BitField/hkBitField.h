/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HKBASE_HKBITFIELD_H
#define HKBASE_HKBITFIELD_H

	/// A fixed size array of bits.  Use this class sparingly, as bit twiddling
	/// is not efficient on all platforms.
class hkBitField
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ARRAY, hkBitField );
		HK_DECLARE_REFLECTION();

			/// Construct a bit field of size numBits.
		hkBitField( int numBits = 0 );

			/// Construct a bit field of size numBits, and set all the bits
			/// to the low bit in the initialValue parameter.
		hkBitField( int numBits, int initialValue );

			/// Non copying initialization from an memory buffer.
			/// Note this does not copy but uses it in place.
			/// Care needs to be taken that the data pointer points to is valid for the scope
			/// of this bitField. Pointer will not be deallocated on destruction.
		hkBitField( hkUint32* ptr, int numBits );

			/// Destructor.
		~hkBitField();

			/// Returns (in the lowest bit position) the bit at the given index.
		int get( int index ) const;

			/// Set the bit at the given index to 1.
		void set( int index );

			/// Clear the bit at the given index to 0.
		void clear( int index );

			/// Assign the bit at the given index to the low bit of the value parameter.
		void assign( int index, int value );
	
			/// Set all the bits to the given value.
		void assignAll( int value );

			/// Resize the bit field, new elements initialized with 'value'.
		void setSize( int numBits, int fillValue = 0 );

			/// Get the number of bits the bit field is set to.
		int getSize() const;

			/// Get the word given the word index
		const hkUint32 getWord( int wordIndex ) const;

			/// Get number of words in the bitset
		const int getNumWords() const;

	private:

		enum
		{
			NUM_BITS_MASK = int(0x7FFFFFFF),
			DONT_DEALLOCATE_FLAG = int(0x80000000),
		};

			// an array of words which hold the bits
		hkUint32* m_words;

			// the number of words in the above array
			// note: we store this in addition to m_numBits to satisfy the serialization conventions for arrays
		int m_numWords;

			// the number of bits the bit field is set to, and a deallocation flag
		int m_numBitsAndFlags;

	private:

			// fill the bits that are beyond m_numBits but within m_numWords
		void fillUnusedBits( int fillValue );

			// whether or not to deallocate the memory
		inline hkBool32 shouldDeallocate() const;

	public:

		hkBitField( hkFinishLoadedObjectFlag flag );
};

#include <Common/Base/Container/BitField/hkBitField.inl>

#endif // HKBASE_HKBITFIELD_H

/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20080529)
*
* Confidential Information of Havok.  (C) Copyright 1999-2008 
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
*
* Use of this software for evaluation purposes is subject to and indicates 
* acceptance of the End User licence Agreement for this product. A copy of 
* the license is included with this software and is also available at
* www.havok.com/tryhavok
*
*/
