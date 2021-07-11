#include <stdio.h>

#include "common.h"
#include "manifest.h"

int
main(int    argc,
     char   *argv[])
{
    printf("ThunderGen %s\n", VERSION);

    manifest test = create_manifest_file();

    test.name =             input("%s", "Name: ");
    test.version =          input("%s", "Version: ");
    test.website =          input("%s", "Website: ");
    test.description =      input("%s", "Description: ");


    return 0;
}
