#ifndef _MARKDOWN_D
#define _MARKDOWN_D

#include "cstring.h"

/* reference-style links (and images) are stored in an array
 * of footnotes.
 */
typedef struct footnote {
    Cstring tag;		/* the tag for the reference link */
    Cstring link;		/* what this footnote points to */
    Cstring title;		/* what it's called (TITLE= attribute) */
    int height, width;		/* dimensions (for image link) */
} Footnote;

/* each input line is read into a Line, which contains the line,
 * the offset of the first non-space character [this assumes 
 * that all tabs will be expanded to spaces!], and a pointer to
 * the next line.
 */
typedef struct line {
    Cstring text;
    struct line *next;
    int dle;
} Line;

/* a paragraph is a collection of Lines, with links to the next paragraph
 * and (if it's a QUOTE, UL, or OL) to the reparsed contents of this
 * paragraph.
 */
typedef struct paragraph {
    struct paragraph *next;	/* next paragraph */
    struct paragraph *down;	/* recompiled contents of this paragraph */
    struct line *text;		/* all the text in this paragraph */
    enum { FORCED, CODE=1, QUOTE, MARKUP, HTML, UL, OL, HR } typ;
    int para;
    enum { LEFT, RIGHT, CENTER} align;
} Paragraph;


extern int mkd_firstnonblank(Line *);

#endif/*_MARKDOWN_D*/