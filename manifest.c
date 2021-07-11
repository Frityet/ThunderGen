//
// Created by Frityet on 2021-07-10.
//

#include <string.h>
#include <json-c/json.h>

#include "common.h"
#include "manifest.h"

manifest
create_manifest_file(void)
{
    FILE *file = fopen(FILE_NAME, "w");
    check_ptr(file);
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%s", MANIFEST_TEMPLATE);
    fclose(file);

    //"but frityet what if the formatting or something of the file is differemt?!?!?!" touch some grass kid and stfu
    return load_manifest_from_string(MANIFEST_TEMPLATE);
}

int
set_manifest_file(manifest data)
{
    char *raw = read_all_lines(FILE_NAME);

    FILE *file = fopen(FILE_NAME, "w");
    check_ptr(file);



    fclose(file);

    return 1;
}

static manifest
load_manifest_from_string(const char *template)
{
    manifest tsmanifest;

    manifest_jobject tsmanifest_raw;

    tsmanifest_raw.root = json_tokener_parse(template);

    json_object_object_get_ex(tsmanifest_raw.root, "name", &tsmanifest_raw.name);
    json_object_object_get_ex(tsmanifest_raw.root, "version_number", &tsmanifest_raw.version);
    json_object_object_get_ex(tsmanifest_raw.root, "website_url", &tsmanifest_raw.website);
    json_object_object_get_ex(tsmanifest_raw.root, "description", &tsmanifest_raw.description);

    json_object_object_get_ex(tsmanifest_raw.root, "dependencies", &tsmanifest_raw.dependencies);
    tsmanifest_raw.dependency_count = json_object_array_length(tsmanifest_raw.dependencies);

    tsmanifest.name         = json_object_get_string(tsmanifest_raw.name);
    tsmanifest.version      = json_object_get_string(tsmanifest_raw.version);
    tsmanifest.website      = json_object_get_string(tsmanifest_raw.website);
    tsmanifest.description  = json_object_get_string(tsmanifest_raw.description);

    for (int i = 0; i < tsmanifest_raw.dependency_count; ++i)
    {
        tsmanifest.dependencies[i] = json_object_get_string(json_object_array_get_idx(tsmanifest_raw.dependencies, i));
    }

    tsmanifest.dependency_count = tsmanifest_raw.dependency_count;
    return tsmanifest;
}

static char*
manifest_to_json_str(manifest tsmanifest)
{

}

static manifest_jobject
manifest_to_json_obj(manifest tsmanifest)
{
    manifest_jobject obj;

    obj.root =
}
