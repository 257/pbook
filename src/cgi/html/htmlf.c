#include "html.h"

void
html_header(char *title){
	printf("Content-Type: text/html; charset=utf-8\n\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>%s</title>\n", title);
	printf("</head>\n");
	printf("<body>\n");
	printf("<pre>\n");
}
void
html_footer(void) {
	printf("</pre>\n");
	printf("</body>\n");
	printf("</html>\n");
}
