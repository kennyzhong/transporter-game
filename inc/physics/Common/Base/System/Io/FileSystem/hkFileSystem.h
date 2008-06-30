/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_FILESYSTEM
#define HK_FILESYSTEM

class hkStreamReader;
class hkStreamWriter;

/// Interface for hkStreamReader/hkStreamWriter creation and filesystem browsing.
/// When streams and archives are given a resource to open by name, they
/// ask the FileSystem to open it for them. The user may wish to
/// replace the default factory with one which reads from packed files
/// or searches in several locations for instance.
class hkFileSystem : public hkReferencedObject, public hkSingleton<hkFileSystem>
{
	public:

		hkFileSystem() {}
			/// Havok has two 'standard' console streams - stdout and stderr.
		enum StdStream { STDOUT=1, STDERR };

			/// Returns a stream reader for file 'name' or null if unable.
		virtual hkStreamReader* openReader(const char* name) = 0;

			/// Returns a stream reader for file 'name' or null if unable.
		virtual hkStreamWriter* openWriter(const char* name) = 0;

		struct DirectoryListing
		{
			~DirectoryListing() 
			{ 
				clear();	
			}

			void clear() 
			{
				for (int i=0; i < m_directories.getSize(); ++i)
				{
					hkDeallocate( m_directories[i] );
				}
				m_directories.clear();
				for (int i=0; i < m_files.getSize(); ++i)
				{
					hkDeallocate( m_files[i] );
				}
				m_files.clear();
			}

				/// adds a copy of name to the directory names list
			void addDirectory(const char* name) 
			{
				m_directories.pushBack( hkString::strDup(name) ); 
			}

				/// adds a copy of name to the file names list
			void addFile(const char* name) 
			{
				m_files.pushBack( hkString::strDup(name) );
			}

				/// const access
			const hkArray<char*>& getDirectories() const { return m_directories; };
			const hkArray<char*>& getFiles() const { return m_files; };

			hkBool isEmpty() const { return (m_directories.isEmpty() && m_files.isEmpty()); };

		private:
				// list of directory names
			hkArray<char*> m_directories;
				// list of file names
			hkArray<char*> m_files;
		}; // DirectoryListing
		
			/// list all the directories and files in the "path" directory, returns HK_FAILURE if the path is not valid
		virtual hkResult listDirectory(const char* basePath, DirectoryListing& listingOut) { return HK_FAILURE; };
};

#endif //HK_FILESYSTEM

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
