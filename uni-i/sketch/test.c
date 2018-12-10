#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Display structure for testing, holding the filename, the expected calls, the
// number of calls made, and the current actual call.
struct display { char *file; char **calls; int n; char call[100]; };

// Forward declarations of findTest and fail, which are at the end of this file.
static char **findTest(char *file);
static void fail(display *d, char *format);

// Check an actual call against the next expected call.
static void check(display *d) {
    char *expect = d->calls[d->n];
    if (strcmp(d->call, expect) != 0) fail(d, "  Call %s\n  Expecting %s\n");
    else if (expect == NULL) fail(d, "  Unexpected extra call %s\n");
    d->n = d->n + 1;
}

// Create a dummy display object containing the expected calls for the file.
display *newDisplay(char *file, int width, int height) {
    display *d = malloc(sizeof(display));
    *d = (struct display) { file, findTest(file), 0 };
    return d;
}

// Check that this call to line(...) is the expected one.
void line(display *d, int x0, int y0, int x1, int y1) {
    sprintf(d->call, "line(d,%d,%d,%d,%d)", x0, y0, x1, y1);
    check(d);
}

// Check that this call to pause(...) is the expected one.
void pause(display *d, int ms) {
    sprintf(d->call, "pause(d,%d)", ms);
    check(d);
}

// Check that this call to colour(...) is the expected one.
void colour(display *d, int rgba) {
    sprintf(d->call, "colour(d,0x%08x)", rgba);
    check(d);
}

// Check that this call to clear(...) is the expected one.
void clear(display *d) {
    sprintf(d->call, "clear(d)");
    check(d);
}

// Check that this call to key(...) is the expected one.
char key(display *d) {
    sprintf(d->call, "key(d)");
    check(d);
    return '?';
}

// Check that this call to end(...) is the last expected call.
void end(display *d) {
    sprintf(d->call, "end(d)");
    check(d);
//    if (d->calls[d->n] != NULL) fail(d, "  Call %s\n  Expecting %s\n");
    printf("Sketch %s OK\n", d->file);
}

// ------------ The test data --------------------------------------------------
// Each test is a series of calls, stored in a variable-length array of strings.

// The calls that should be made for lines.sketch.
static char *linesTest[] = {
    "line(d,30,30,60,30)", "line(d,60,30,60,60)", "end(d)"
};

// The calls that should be made for square.sketch.
static char *squareTest[] = {
    "line(d,30,30,60,30)", "line(d,60,30,60,60)",
    "line(d,60,60,30,60)", "line(d,30,60,30,30)", "end(d)"
};

// The calls that should be made for oxo.sketch.
static char *oxoTest[] = {
    "line(d,30,40,60,40)", "line(d,30,50,60,50)",
    "line(d,40,30,40,60)", "line(d,50,30,50,60)", "end(d)"
};

// The calls that should be made for diag.sketch.
static char *diagTest[] = {
    "line(d,30,30,60,60)", "end(d)"
};

// The calls that should be made for cross.sketch.
static char *crossTest[] = {
    "line(d,30,30,60,60)", "line(d,60,30,30,60)", "end(d)"
};

// The calls that should be made for field.sketch.
static char *fieldTest[] = {
    "line(d,30,30,170,30)", "line(d,170,30,170,170)",
    "line(d,170,170,30,170)", "line(d,30,170,30,30)", "end(d)"
};

// The calls that should be made for box.sketch.
static char *boxTest[] = {
    "line(d,30,30,32,30)", "pause(d,50)", "line(d,32,30,34,30)", "pause(d,50)",
    "line(d,34,30,36,30)", "pause(d,50)", "line(d,36,30,38,30)", "pause(d,50)",
    "line(d,38,30,40,30)", "pause(d,50)", "line(d,40,30,42,30)", "pause(d,50)",
    "line(d,42,30,44,30)", "pause(d,50)", "line(d,44,30,46,30)", "pause(d,50)",
    "line(d,46,30,48,30)", "pause(d,50)", "line(d,48,30,50,30)", "pause(d,50)",
    "line(d,50,30,52,30)", "pause(d,50)", "line(d,52,30,54,30)", "pause(d,50)",
    "line(d,54,30,56,30)", "pause(d,50)", "line(d,56,30,58,30)", "pause(d,50)",
    "line(d,58,30,60,30)", "pause(d,50)", "line(d,60,30,60,32)", "pause(d,50)",
    "line(d,60,32,60,34)", "pause(d,50)", "line(d,60,34,60,36)", "pause(d,50)",
    "line(d,60,36,60,38)", "pause(d,50)", "line(d,60,38,60,40)", "pause(d,50)",
    "line(d,60,40,60,42)", "pause(d,50)", "line(d,60,42,60,44)", "pause(d,50)",
    "line(d,60,44,60,46)", "pause(d,50)", "line(d,60,46,60,48)", "pause(d,50)",
    "line(d,60,48,60,50)", "pause(d,50)", "line(d,60,50,60,52)", "pause(d,50)",
    "line(d,60,52,60,54)", "pause(d,50)", "line(d,60,54,60,56)", "pause(d,50)",
    "line(d,60,56,60,58)", "pause(d,50)", "line(d,60,58,60,60)", "pause(d,50)",
    "line(d,60,60,58,60)", "pause(d,50)", "line(d,58,60,56,60)", "pause(d,50)",
    "line(d,56,60,54,60)", "pause(d,50)", "line(d,54,60,52,60)", "pause(d,50)",
    "line(d,52,60,50,60)", "pause(d,50)", "line(d,50,60,48,60)", "pause(d,50)",
    "line(d,48,60,46,60)", "pause(d,50)", "line(d,46,60,44,60)", "pause(d,50)",
    "line(d,44,60,42,60)", "pause(d,50)", "line(d,42,60,40,60)", "pause(d,50)",
    "line(d,40,60,38,60)", "pause(d,50)", "line(d,38,60,36,60)", "pause(d,50)",
    "line(d,36,60,34,60)", "pause(d,50)", "line(d,34,60,32,60)", "pause(d,50)",
    "line(d,32,60,30,60)", "pause(d,50)", "line(d,30,60,30,58)", "pause(d,50)",
    "line(d,30,58,30,56)", "pause(d,50)", "line(d,30,56,30,54)", "pause(d,50)",
    "line(d,30,54,30,52)", "pause(d,50)", "line(d,30,52,30,50)", "pause(d,50)",
    "line(d,30,50,30,48)", "pause(d,50)", "line(d,30,48,30,46)", "pause(d,50)",
    "line(d,30,46,30,44)", "pause(d,50)", "line(d,30,44,30,42)", "pause(d,50)",
    "line(d,30,42,30,40)", "pause(d,50)", "line(d,30,40,30,38)", "pause(d,50)",
    "line(d,30,38,30,36)", "pause(d,50)", "line(d,30,36,30,34)", "pause(d,50)",
    "line(d,30,34,30,32)", "pause(d,50)", "line(d,30,32,30,30)", "pause(d,50)",
    "end(d)"
};

// The calls that should be made for clear.sketch.
static char *clearTest[] = {
    "line(d,30,40,60,40)", "line(d,30,50,60,50)", "line(d,40,30,40,60)",
    "line(d,50,30,50,60)", "pause(d,2000)", "clear(d)", "line(d,30,30,60,60)",
    "line(d,60,30,30,60)", "end(d)"
};

// The calls that should be made for key.sketch.
static char *keyTest[] = {
    "line(d,30,40,60,40)", "line(d,30,50,60,50)", "line(d,40,30,40,60)",
    "line(d,50,30,50,60)", "key(d)", "clear(d)",
    "line(d,30,30,60,60)", "line(d,60,30,30,60)", "end(d)"
};

// The calls that should be made for field.sketch.
static char *lawnTest[] = {
    "colour(d,0x00ff00ff)",
    "line(d,30,30,170,30)", "line(d,170,30,170,170)",
    "line(d,170,170,30,170)", "line(d,30,170,30,30)",
    "end(d)"
};

struct sketch { char *name, *file, **test; };
static struct sketch sketches[] = {
    {"lines", "lines.sketch", linesTest},
    {"square", "square.sketch", squareTest},
    {"oxo", "oxo.sketch", oxoTest},
    {"diag", "diag.sketch", diagTest},
    {"cross", "cross.sketch", crossTest},
    {"field", "field.sketch", fieldTest},
    {"box", "box.sketch", boxTest},
    {"clear", "clear.sketch", clearTest},
    {"key", "key.sketch", keyTest},
    {"lawn", "lawn.sketch", lawnTest},
};

// Find the right test for the given sketch filename.
static char **findTest(char *file) {
    int n = sizeof(sketches) / sizeof(struct sketch);
    for (int i = 0; i < n; i++) {
        if (strcmp(file, sketches[i].name) == 0) return sketches[i].test;
        if (strcmp(file, sketches[i].file) == 0) return sketches[i].test;
    }
    fprintf(stderr, "Can't find test for %s\n", file);
    exit(1);
    return NULL;
}

// Report failure and exit.
static void fail(display *d, char *format) {
    fprintf(stderr, "Failure in %s\n", d->file);
    fprintf(stderr, format, d->call, d->calls[d->n]);
    exit(1);
}
