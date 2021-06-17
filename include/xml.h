/** \file xml.h
 ** \brief Declares all the Xml related stuff.
 **/
#ifndef XML_H
	#define XML_H
	#include <stdio.h>
	#include "constants.h"
	#include "list.h"

	typedef struct XmlAttributeBody {
		char name[XML_MAX_ATTRIBUTE_NAME_SIZE];
		char value[XML_MAX_ATTRIBUTE_VAL_SIZE];
	} XmlAttribute;
	XmlAttribute* initialize_xattr(XmlAttribute*, const char*, const char*);
	char* toString_xattr(char*, const XmlAttribute*);

	#define ASSERT_XMLATTRIBUTE(attribute)									\
		ASSERT_NOT_NULL(attribute);											\
		ASSERT_NOT_EMPTY(attribute->name);									\
		ASSERT_NOT_TOO_LONG(attribute->name, XML_MAX_ATTRIBUTE_NAME_SIZE);	\
		ASSERT_NOT_TOO_LONG(attribute->value, XML_MAX_ATTRIBUTE_VAL_SIZE)

	DECLARE_ARRAY_OF(XmlAttribute,XML_MAX_ATTRIBUTES,size,array,xattra);
	DECLARE_LIST_OF(XmlAttribute,XML_MAX_ATTRIBUTES,size,list,xattrl);

	#define ASSERT_XMLATTRIBUTEARRAY(array)				\
		ASSERT_ARRAY(array,size,XML_MAX_ATTRIBUTES)
	#define ASSERT_XMLATTRIBUTELIST(list)				\
		ASSERT_LIST(list,size,XML_MAX_ATTRIBUTES)

	typedef struct XmlNodeBody {
		struct XmlNodeBody* parent;
		char tag[XML_MAX_TAG_SIZE];
		char content[XML_MAX_CHILDREN+1][XML_MAX_CONTENT_SIZE];
		struct XmlNodeBody* children[XML_MAX_CHILDREN];
		unsigned int nChildren;
		XmlAttributeArray attributes[1];
	} XmlNode;
	XmlNode* initialize_xmln(XmlNode*, XmlNode*);
	char* toString_xmln(char*, const XmlNode*);
	char* toContent_xmln(char*, const XmlNode*);

	#define ASSERT_XMLNODE(node)									\
		ASSERT_NOT_NULL(node);										\
		ASSERT_NOT_EMPTY(node->tag);								\
		ASSERT_NOT_TOO_LONG(node->tag, XML_MAX_TAG_SIZE);			\
		ASSERT_FITS_IN_BOUND(node->nChildren, XML_MAX_CHILDREN);	\
		ASSERT_XMLATTRIBUTEARRAY(node->attributes)

	DECLARE_ARRAY_OF(XmlNode,XML_MAX_NODES,size,nodes,xmlna);
	DECLARE_LIST_OF(XmlNode,XML_MAX_NODES,size,nodes,xmlnl);

	#define ASSERT_XMLNODEARRAY(array)	\
		ASSERT_ARRAY(array,size,XML_MAX_NODES)
	#define ASSERT_XMLNODELIST(list)	\
		ASSERT_LIST(list,size,XML_MAX_NODES)

	typedef struct XmlBody {
		char meta[XML_META_MAX_SIZE];
		XmlNodeArray tree[1];
	} Xml;

	#define ASSERT_XML(xml)									\
		ASSERT_NOT_NULL(xml);								\
		ASSERT_NOT_TOO_LONG(xml->meta, XML_META_MAX_SIZE);	\
		ASSERT_XMLNODEARRAY(xml->tree)

	Xml* initialize_xml(Xml*);
	Xml* fromString_xml(Xml*, const char*);
	Xml* fromStream_xml(Xml*, FILE*);
	Xml* fromFile_xml(Xml*, const char*);
	char* toString_xml(char*, const Xml*);
#endif
