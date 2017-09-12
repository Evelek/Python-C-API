#include "Python.h"
#include "functions.h"

static PyObject*
add(PyObject *self, PyObject *args) {
	int first_value;
	int second_value;

	if (!PyArg_ParseTuple(args, "ii", &first_value, &second_value))
		return NULL;

	int result = addition(first_value, second_value);

	return Py_BuildValue("i", result);
}

static PyObject*
subtract(PyObject *self, PyObject *args) {
	int first_value;
	int second_value;

	if (!PyArg_ParseTuple(args, "ii", &first_value, &second_value))
		return NULL;

	int result = subtraction(first_value, second_value);

	return Py_BuildValue("i", result);
}

static PyObject*
multiply(PyObject *self, PyObject *args) {
	int first_value;
	int second_value;

	if (!PyArg_ParseTuple(args, "ii", &first_value, &second_value))
		return NULL;

	int result = multiplication(first_value, second_value);

	return Py_BuildValue("i", result);
}

static PyObject*
divide(PyObject *self, PyObject *args) {
	int first_value;
	int second_value;

	if (!PyArg_ParseTuple(args, "ii", &first_value, &second_value))
		return NULL;

	int result = division(first_value, second_value);

	return Py_BuildValue("i", result);
}

static PyMethodDef math_methods[] = {
	{ "add", add, METH_VARARGS, "returns sum of 2 values" },
	{ "subtract", subtract, METH_VARARGS, "returns subtraction of 2 values" },
	{ "multiply", multiply, METH_VARARGS, "returns multiplication of 2 values" },
	{ "divide", divide, METH_VARARGS, "returns division of 2 values" },
	{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef math_modul = {
	PyModuleDef_HEAD_INIT,
	"4 functions used for basic mathematical operations",
	NULL,
	-1,
	math_methods
};

PyMODINIT_FUNC
PyInit_math_functions(void) {
	return PyModule_Create(&math_modul);
}
