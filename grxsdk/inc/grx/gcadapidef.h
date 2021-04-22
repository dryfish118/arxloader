#pragma once

#ifndef GCADAPIDEF_H
#define GCADAPIDEF_H

#ifndef _GSOFT_MAC_
#ifndef GCAD_PORT
	#ifdef GCAD_API
		#define GCAD_PORT _declspec(dllexport)
	#else
		#define GCAD_PORT _declspec(dllimport)
	#endif
#endif
#else
#define GCAD_PORT
#endif 


#endif 