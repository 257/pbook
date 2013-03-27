#include "html.h"

void
html_header(char *title){
	printf("Content-Type: text/html; charset=us-ascii\n\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>%s</title>\n", title);
	printf("</head>\n");
	printf("<body>\n");
}
void
html_footer(void) {
	printf("</body>\n");
	printf("</html>\n");
}
