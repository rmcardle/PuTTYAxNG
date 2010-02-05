//
// Ax.cpp
//

#include <windows.h>
#include <vector>

#include "CCritSec.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _SMemRegionInfo
{
	_SMemRegionInfo( CHAR* _pszName, VOID* _pvMem, INT _iMemSize ) : pszName ( _pszName ), pvMem ( _pvMem ), iMemSize ( _iMemSize )
	{
	}

	CHAR*			pszName;
	VOID*			pvMem;
	INT				iMemSize;

} SMemRegionInfo;

static CCriticalSection					s_csGetPointerAccess;
static std::vector< SMemRegionInfo >	s_vsMemRegionInfo; // acquire s_csGetPointerAccess before accessing.

//////////////////////////////////////////////////////////////////////////////////////////////////

static VOID* ReturnIfAllocated_NOLOCK( CHAR* name, INT size )
{
	// already allocated ?

	for( int i=0; i<s_vsMemRegionInfo.size (); i ++ )
	{
		SMemRegionInfo*		p = & s_vsMemRegionInfo[ i ];
		if ( ::strcmp( p->pszName, name ) == 0 )
		{
			if ( p->iMemSize != size )
				throw;
			else
				return p->pvMem;
		}
	}

	return NULL;
}

static VOID* ForceAllocate_NOLOCK( CHAR* name, INT size )
{
	// allocate.

	VOID*			mem = ::malloc( size );
	if ( mem == NULL )
		return NULL;

	::memset( mem, 0, size );

	s_vsMemRegionInfo.push_back( SMemRegionInfo( name, mem, size ) );
	return mem;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" VOID* AX_GET_POINTER( CHAR* name, INT size )
{
	CCriticalSection::scope			__access__( s_csGetPointerAccess );

	// already allocated ?

	VOID*		pvExist = ::ReturnIfAllocated_NOLOCK( name, size );
	if ( pvExist )
		return pvExist;

	// allocate.

	return ::ForceAllocate_NOLOCK( name, size );
}

extern "C" VOID* AX_GET_POINTER_INT( CHAR* name, INT size, INT init )
{
	CCriticalSection::scope			__access__( s_csGetPointerAccess );

	if ( size != sizeof( INT ) )
		throw;

	VOID*		pvExist = ::ReturnIfAllocated_NOLOCK( name, size );
	if ( pvExist )
		return pvExist;

	INT* p = (INT*) ::ForceAllocate_NOLOCK( name, size );
	* p = init;
	return p;
}

extern "C" VOID* AX_GET_POINTER_UINT( CHAR* name, INT size, UINT init )
{
	CCriticalSection::scope			__access__( s_csGetPointerAccess );

	if ( size != sizeof( UINT ) )
		throw;

	VOID*		pvExist = ::ReturnIfAllocated_NOLOCK( name, size );
	if ( pvExist )
		return pvExist;

	UINT* p = (UINT*) ::ForceAllocate_NOLOCK( name, size );
	* p = init;
	return p;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
