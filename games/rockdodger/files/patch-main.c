
$FreeBSD$

--- main.c.orig
+++ main.c
@@ -459,7 +459,7 @@
     else {
 	char s[1024];
 	umask(0177);
-	sprintf(s,"%s/.rockdodger_high",getenv("HOME"));
+	snprintf(s,1024,"%s/.rockdodger_high",getenv("HOME"));
 	if (f=fopen(s,mode)) {
 	    umask(mask);
 	    return f;
@@ -478,7 +478,7 @@
 	for (i=0; i<8; i++) {
 	    char s[1024];
 	    int highscore;
-	    if (fscanf (f, "%d %[^\n]", &highscore, s)!=2)
+	    if (fscanf (f, "%d %1023[^\n]", &highscore, s)!=2)
 		break;
 	    if (high[i].allocated)
 		free(high[i].name);
