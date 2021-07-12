#include <stdio.h>

#include "common.h"
#include "manifest.h"

int
main(int    argc,
     char   *argv[])
{
    printf("ThunderGen %s\n", VERSION);

    manifest test = create_manifest_file();

    test.name           = input("%s", "Name: ");
    test.version        = input("%s", "Version: ");
    test.website        = input("%s", "Website: ");
    test.description    = input("%s", "Description: ");

    test.dependency_count = (size_t)input("%zu", "Number of dependencies: ");
    for (int i = 0; i < test.dependency_count; ++i)
    {
        printf("Dependency %d/%zu\n", i, test.dependency_count);
        test.dependencies[i] = input("%s", "Dependency: ");
    }

    set_manifest_file(test);

    printf("Done!");


    return 0;
}
