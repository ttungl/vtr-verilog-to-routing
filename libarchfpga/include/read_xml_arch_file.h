#ifndef READ_XML_ARCH_FILE_H
#define READ_XML_ARCH_FILE_H

#include "util.h"
#include "arch_types.h"

#ifdef __cplusplus 
extern "C" {
#endif

/* special type indexes, necessary for initialization, everything afterwards
 should use the pointers to these type indices*/

#define NUM_MODELS_IN_LIBRARY 4
#define EMPTY_TYPE_INDEX 0
#define IO_TYPE_INDEX 1

/* function declarations */
void
XmlReadArch(const char *ArchFile, const bool timing_enabled,
		struct s_arch *arch, t_type_descriptor ** Types,
		int *NumTypes);

const char* get_arch_file_name();

#ifdef __cplusplus 
}
#endif

#endif

