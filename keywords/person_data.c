#include "Python.h"

static PyObject*
set_data(PyObject *self, PyObject *args, PyObject *kwargs) {
	const char *name = "";
	const char *surname = "";
	const char *city = "";
	int age = 0;

	static char *kwlist[] = {
		"name",
		"surname",
		"city",
		"age",
		NULL
	};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|sssi", kwlist, &name, &surname, &city, &age))
		return NULL;

	return Py_BuildValue("(sssi)", name, surname, city, age);
}

static PyObject*
print_data(PyObject *self, PyObject *args) {
	const char *name;
	const char *surname;
	const char *city;
	int age;

	if (!PyArg_ParseTuple(args, "(sssi)", &name, &surname, &city, &age))
		return NULL;

	printf("Name: %s\n", name);
	printf("Surname: %s\n", surname);
	printf("City: %s\n", city);
	printf("Age: %d\n", age);

	Py_RETURN_NONE;
}

static PyMethodDef person_methods[] = {
	{ "set_data", (PyCFunction)set_data, METH_VARARGS | METH_KEYWORDS, "set name, surname, city and age" },
	{ "print_data", print_data, METH_VARARGS, "print name, surname, city and age" },
	{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef person_module = {
	PyModuleDef_HEAD_INIT,
	"keywords",
	NULL,
	-1,
	person_methods
};

PyMODINIT_FUNC
PyInit_keywords(void) {
	return PyModule_Create(&person_module);
}
