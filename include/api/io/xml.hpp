#ifndef __XML__H__
#define __XML__H__

    #include <iostream>
    using namespace std;
    #include <cstring>

    // reading

    int ends_with(const char* haystack, const char* needle);

    struct _XMLAttribute
    {
        char* key;
        char* value;
    };
    typedef struct _XMLAttribute XMLAttribute;

    void XMLAttribute_free(XMLAttribute* attr);

    struct _XMLAttributeList
    {
        int heap_size;
        int size;
        XMLAttribute* data;
    };
    typedef struct _XMLAttributeList XMLAttributeList;

    void XMLAttributeList_init(XMLAttributeList* list);
    void XMLAttributeList_add(XMLAttributeList* list, XMLAttribute* attr);

    struct _XMLNodeList
    {
        int heap_size;
        int size;
        struct _XMLNode** data;
    };
    typedef struct _XMLNodeList XMLNodeList;

    void XMLNodeList_init(XMLNodeList* list);
    void XMLNodeList_add(XMLNodeList* list, struct _XMLNode* node);
    struct _XMLNode* XMLNodeList_at(XMLNodeList* list, int index);
    void XMLNodeList_free(XMLNodeList* list);

    struct _XMLNode
    {
        char* tag;
        char* inner_text;
        struct _XMLNode* parent;
        XMLAttributeList attributes;
        XMLNodeList children;
    };
    typedef struct _XMLNode XMLNode;

    XMLNode* XMLNode_new(XMLNode* parent);
    void XMLNode_free(XMLNode* node);
    XMLNode* XMLNode_child(XMLNode* parent, int index);
    XMLNodeList* XMLNode_children(XMLNode* parent, const char* tag);
    char* XMLNode_attr_val(XMLNode* node, const char* key);
    XMLAttribute* XMLNode_attr(XMLNode* node, char* key);

    struct _XMLDocument
    {
        XMLNode* root;
        char* version;
        char* encoding;
    };
    typedef struct _XMLDocument XMLDocument;

    int XMLDocument_load(XMLDocument* doc, const char* path);
    int XMLDocument_write(XMLDocument* doc, const char* path, int indent);
    void XMLDocument_free(XMLDocument* doc);

#endif // !__XML__H__