#include <stdio.h>
#include <stdlib.h>
#include <libxml2/libxml/parser.h>

int main() {
    xmlDocPtr doc;
    xmlNodePtr root;

    // open xml file
    doc = xmlParseFile("catalog.xml");
    if(doc == NULL) {
        fprintf(stderr, "Bad XML Document\n");
        return EXIT_FAILURE;
    }

    // get root
    root = xmlDocGetRootElement(doc);
    if(root == NULL) {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return EXIT_FAILURE;
    }

    printf("Root document : %s\n", root->name);

    //free memory
    xmlFreeDoc(doc);

    return EXIT_SUCCESS;
}