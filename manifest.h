//
// Created by Frityet on 2021-07-09.
//

#ifndef THUNDERGEN_MANIFEST
#define THUNDERGEN_MANIFEST

#include <stdio.h>

static const char FILE_NAME[] = "manifest.json";

typedef struct {
    char    *name;
    char    *version;
    char    *website;
    char    *description;

    size_t  dependency_count;
    char    *dependencies[];
} manifest;

manifest
load_manifest_from_string(const char*);

manifest
create_manifest_file(void);

int
set_manifest_file(manifest);

#endif //THUNDERGEN_MANIFEST
