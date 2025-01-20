# XML

XPath:

Allows 

Use attribute for identifier of elements, and use subelements for contents.

<![CDATA[...]]>

Document schema: DTD, XML Schema

DTD

Contains structure (element, attributes, ), Does not contain data type.

<!ELEMENT element (subelement-specification)>

subelement-specification: plain, regexp |, +, *, ?

<!ATTRLIST element (attributes)>

name, type (CDATA, ID, IDREF, IDREFS), #REQUIRED|default_value|#IMPLIED

PCDATA - Parsed CDATA.

XML Schema: Allow for data type definition

XPath: Path specification

Returns nodes, or returns text when /text() is appended

/...[predicate]

/...@attribute

functions: count, ...

XQuery:

FLWOR (FOR, LET, WHERE, ORDER BY, RETURN)

Use {} for evaluating node.


