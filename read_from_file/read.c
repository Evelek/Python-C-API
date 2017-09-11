#include "Python.h"
#include <stdio.h>

static PyObject*
read_file(PyObject *self, PyObject *args) {
	const char *file_name;
	int bufsize = 4; // default size of buffer
	
	if (!PyArg_ParseTuple(args, "s|i", &file_name, &bufsize))
		return NULL;

	// buffsize must be at least 2
	if (bufsize < 2) {
		PyErr_SetString(PyExc_ValueError, "bufsize is too small");
		return NULL;
	}

	FILE *file;
	file = fopen(file_name, "r");
	if (!file) {
		PyErr_SetString(PyExc_IOError, "File opening failed!");
		return NULL;
	}

	// alloc memory for buffer
	// if there's no memory, malloc() returns null pointer
	char *buf = (char*)malloc(bufsize);
	if (!buf) {
		return PyErr_NoMemory();
	}

	while (fgets(buf, bufsize, file) != NULL)
		printf("%s", buf);

	if (ferror(file))
		puts("Error while reading");
	if (feof(file))
		puts("\nEnd of file");

	free(buf);
	fclose(file);

	Py_RETURN_NONE;
}

static PyMethodDef read_file_methods[] = {
	{"read_file", read_file, METH_VARARGS, "reading data from file"},
};

static struct PyModuleDef read_file_modul = {
	PyModuleDef_HEAD_INIT,
	"Reading from file",
	NULL,
	-1,
	read_file_methods
};

PyMODINIT_FUNC
PyInit_read_from_file(void) {
	return PyModule_Create(&read_file_modul);
}
