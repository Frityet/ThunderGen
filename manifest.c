//
// Created by Frityet on 2021-07-10.
//

#include <string.h>
#include <json-c/json.h>

#include "common.h"
#include "manifest.h"

static const char FILENAME[] = "manifest.json";

manifest
load_manifest_from_string(const char *template)
{
    manifest tsmanifest;
    json_object *json = json_tokener_parse(template);

    json_object *name;
    json_object *ver;
    json_object *web;
    json_object *desc;

    json_object *deps;
    size_t      deps_len;

    json_object_object_get_ex(json, "name", &name);
    json_object_object_get_ex(json, "version_number", &ver);
    json_object_object_get_ex(json, "website_url", &web);
    json_object_object_get_ex(json, "description", &desc);

    json_object_object_get_ex(json, "dependencies", &deps);
    deps_len = json_object_array_length(deps);

    tsmanifest.name         = json_object_get_string(name);
    tsmanifest.version      = json_object_get_string(ver);
    tsmanifest.website      = json_object_get_string(web);
    tsmanifest.description  = json_object_get_string(desc);

    for (int i = 0; i < deps_len; ++i)
    {
        tsmanifest.dependencies[i] = json_object_get_string(json_object_array_get_idx(deps, i));
    }

    tsmanifest.dependency_count = deps_len;
    return tsmanifest;
}

manifest
create_manifest_file(void)
{
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) throw_error(strcat("Could not open file: ", FILENAME), -1);
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%s", MANIFEST_TEMPLATE);
    fclose(file);

    //"but frityet what if the formatting or something of the file is differemt?!?!?!" touch some grass kid and stfu
    return load_manifest_from_string(MANIFEST_TEMPLATE);
}

int
set_manifest_file(manifest data)
{

    return 1;
}
