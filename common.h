//
// Created by Frityet on 2021-07-09.
//

#ifndef THUNDERGEN_COMMON
#define THUNDERGEN_COMMON

#include <stdio.h>

static const char VERSION[] = "v1.0.0";

static const char MANIFEST_TEMPLATE[] = "{\n"
                                        "    \"name\": \"\",\n"
                                        "    \"version_number\": \"1.0.0\",\n"
                                        "    \"website_url\": \"\",\n"
                                        "    \"description\": \"\",\n"
                                        "    \"dependencies\": [ ]\n"
                                        "}";
static const char EXAMPLE_MANIFEST[] = "{\n"
                                       "    \"name\": \"H3VRUtilities\",\n"
                                       "    \"version_number\": \"8.0.3\",\n"
                                       "    \"website_url\": \"https://github.com/WFIOST/H3VRUtilities\",\n"
                                       "    \"description\": \"H3VR Utilities is a dependency mod that is required for many custom items.\",\n"
                                       "    \"dependencies\":\n"
                                       "    [\n"
                                       "        \"nrgill28-Sodalite-1.0.0\",\n"
                                       "        \"nrgill28-HookGenPatcher_H3VR-1.2.3\"\n"
                                       "    ]\n"
                                       "}";

int
throw_error(const char*, int);

char*
input_str(const char*);

char*
read_all_lines(const char*);

char*
fread_all_lines(FILE*);

int
check_ptr(void*);

#endif //THUNDERGEN_COMMON
