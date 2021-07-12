//
// Created by Frityet on 2021-07-09.
//

#ifndef THUNDERGEN_MANIFEST
#define THUNDERGEN_MANIFEST

#include <stdio.h>
#include <json-c/json.h>

static const char FILE_NAME[] = "manifest.json";

typedef struct {
    json_object *root;

    json_object *name;
    json_object *version;
    json_object *website;
    json_object *description;

    int         dependency_count;
    json_object *dependencies;

} manifest_jobject;

typedef struct {
    char    *name;
    char    *version;
    char    *website;
    char    *description;

    int     dependency_count;
    char    **dependencies;
} manifest;


manifest
create_manifest_file(void);

int
set_manifest_file(manifest);

const char*
manifest_to_json_str(manifest);

static manifest
load_manifest_from_string(const char*);

static manifest_jobject
manifest_to_json_obj(manifest);

static manifest
json_obj_to_manifest(manifest_jobject);

#endif //THUNDERGEN_MANIFEST
