//
// Created by Frityet on 2021-07-10.
//

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
    FILE *file = fopen(FILE_NAME, "w");
    check_ptr(file);

    fprintf(file, "%s", manifest_to_json_str(data));

    fclose(file);

    return 1;
}

static manifest
load_manifest_from_string(const char *template)
{
    manifest_jobject tsmanifest_raw;

    tsmanifest_raw.root = json_tokener_parse(template);

    json_object_object_get_ex(tsmanifest_raw.root, "name", &tsmanifest_raw.name);
    json_object_object_get_ex(tsmanifest_raw.root, "version_number", &tsmanifest_raw.version);
    json_object_object_get_ex(tsmanifest_raw.root, "website_url", &tsmanifest_raw.website);
    json_object_object_get_ex(tsmanifest_raw.root, "description", &tsmanifest_raw.description);

    json_object_object_get_ex(tsmanifest_raw.root, "dependencies", &tsmanifest_raw.dependencies);
    tsmanifest_raw.dependency_count = json_object_array_length(tsmanifest_raw.dependencies);

    ++tsmanifest_raw.dependency_count;

    return json_obj_to_manifest(tsmanifest_raw);
}

const char*
manifest_to_json_str(manifest tsmanifest)
{
    //printf("%s", tsmanifest.dependencies[0]);
    return json_object_to_json_string_ext(manifest_to_json_obj(tsmanifest).root, JSON_C_TO_STRING_PRETTY_TAB + JSON_C_TO_STRING_NOSLASHESCAPE);
}

int
destroy_manifest(manifest tsmanifest)
{
    free_ptr(tsmanifest.name);
    free_ptr(tsmanifest.version);
    free_ptr(tsmanifest.website);
    free_ptr(tsmanifest.description);

    for (int i = 0; i < tsmanifest.dependency_count; ++i)
    {
        free_ptr(tsmanifest.dependencies[i]);
    }

    free_ptr(tsmanifest.dependencies);
    return 0;
}

int
destroy_json_obj(manifest_jobject jobj)
{
    json_object_object_del(jobj.root, "name");
    jobj.name = NULL;
    json_object_object_del(jobj.root, "version_number");
    jobj.version = NULL;
    json_object_object_del(jobj.root, "website_url");
    jobj.website = NULL;
    json_object_object_del(jobj.root, "description");
    jobj.description = NULL;
    json_object_object_del(jobj.root, "dependencies");
    jobj.dependencies = NULL;
    return 0;
}

static manifest_jobject
manifest_to_json_obj(manifest tsmanifest)
{
    manifest_jobject jobj;

    jobj.root = json_object_new_object();
    check_ptr(jobj.root);

    //Move the information into the root object
    json_object_object_add(jobj.root, "name", json_object_new_string(tsmanifest.name));
    json_object_object_add(jobj.root, "version_number", json_object_new_string(tsmanifest.version));
    json_object_object_add(jobj.root, "website_url", json_object_new_string(tsmanifest.website));
    json_object_object_add(jobj.root, "description", json_object_new_string(tsmanifest.description));

    //Dependencies has to be it's own object
    jobj.dependencies = json_object_new_array();
    json_object_object_add(jobj.root, "dependencies", jobj.dependencies);

    for (int i = 0; i < tsmanifest.dependency_count; ++i)
    {
        //For every dependency in the manifest, add it to the array
        json_object_array_add(jobj.dependencies, json_object_new_string(tsmanifest.dependencies[i]));
    }

    //Assign the values from the root object to the struct fields
    json_object_object_get_ex(jobj.root, "name", &jobj.name);
    json_object_object_get_ex(jobj.root, "version_number", &jobj.version);
    json_object_object_get_ex(jobj.root, "website_url", &jobj.website);
    json_object_object_get_ex(jobj.root, "description", &jobj.description);

    return jobj;
}

static manifest
json_obj_to_manifest(manifest_jobject jobj)
{
    manifest tsmanifest;

    tsmanifest.name         = json_object_get_string(jobj.name);
    tsmanifest.version      = json_object_get_string(jobj.version);
    tsmanifest.website      = json_object_get_string(jobj.website);
    tsmanifest.description  = json_object_get_string(jobj.description);

    tsmanifest.dependencies = malloc(sizeof(char**) * jobj.dependency_count);
    for (int i = 0; i < jobj.dependency_count; ++i)
    {
        tsmanifest.dependencies[i] = json_object_get_string(json_object_array_get_idx(jobj.dependencies, i));
    }

    tsmanifest.dependency_count = jobj.dependency_count;

    return tsmanifest;
}
