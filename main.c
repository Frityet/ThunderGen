#include <stdio.h>

#include "common.h"
#include "manifest.h"

int
main(int    argc,
     char   *argv[])
{
    printf("ThunderGen %s\n", VERSION);

    manifest test = create_manifest_file();

    test.name           = input_str("Name: ");
    test.version        = input_str("Version: ");
    test.website        = input_str("Website: ");
    test.description    = input_str("Description: ");

    printf("Number of Dependencies: ");
    //TODO: Use strtoul instead
    scanf("%d", &test.dependency_count);

    if (test.dependency_count > 16) throw_error("Dependency count is too high, possible error", -1);

    for (int i = 0; i < test.dependency_count; ++i)
    {
        printf("Dependency %d/%d\n", i, test.dependency_count);
        test.dependencies[i] = input_str("Dependency: ");
    }

    printf("Result: %s\n", manifest_to_json_str(test));

    set_manifest_file(test);

    printf("Done!");


    return 0;
}
