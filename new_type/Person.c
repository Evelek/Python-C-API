#include "Python.h"
#include "structmember.h"

typedef struct {
	PyObject_HEAD
	PyObject *name;
	PyObject *surname;
	int age;
} Person;

static void
Person_dealloc(Person *self) {
	Py_XDECREF(self->name);
	Py_XDECREF(self->surname);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
Person_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
	Person *self;

	self = (Person *)type->tp_alloc(type, 0);
	if (self != NULL) {
		self->name = PyUnicode_FromString("");
		if (self->name == NULL) {
			Py_DECREF(self);
			return NULL;
		}

		self->surname = PyUnicode_FromString("");
		if (self->surname == NULL) {
			Py_DECREF(self);
			return NULL;
		}

		self->age = 0;
	}
	return (PyObject *)self;
}

static int
Person_init(Person *self, PyObject *args, PyObject *kwds) {
	PyObject *name = NULL, *surname = NULL, *tmp;

	static char *kwlist[] = { "name", "surname", "age", NULL };

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|SSi", kwlist, &name, &surname, &self->age))
		return -1;

	if (name) {
		tmp = self->name;
		Py_INCREF(name);
		self->name = name;
		Py_DECREF(tmp);
	}

	if (surname) {
		tmp = self->surname;
		Py_INCREF(surname);
		self->surname = surname;
		Py_DECREF(tmp);
	}

	return 0;
}

static PyMemberDef Person_members[] = {
	{ "age", T_INT, offsetof(Person, age), 0, "Person age" },
	{ NULL }
};

static PyObject*
Person_getname(Person *self, void *closure) {
	Py_INCREF(self->name);
	return self->name;
}

static int
Person_setname(Person *self, PyObject *value, void *closure) {
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "Cannot delete `name` attribute");
		return -1;
	}

	if (!PyUnicode_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "The `name` attribute must be a string");
		return -1;
	}

	Py_DECREF(self->name);
	Py_INCREF(value);
	self->name = value;

	return 0;
}

static PyObject*
Person_getsurname(Person *self, void *closure) {
	Py_INCREF(self->surname);
	return self->surname;
}

static int
Person_setsurname(Person *self, PyObject *value, void *closure) {
	if (value == NULL) {
		PyErr_SetString(PyExc_TypeError, "Cannot delete the `surname` attribute");
		return -1;
	}

	if (!PyUnicode_Check(value)) {
		PyErr_SetString(PyExc_TypeError, "The `surname` attribute value must be a string");
		return -1;
	}

	Py_DECREF(self->surname);
	Py_INCREF(value);
	self->surname = value;

	return 0;
}

static PyGetSetDef Person_getsetter[] = {
	{ "name", (getter)Person_getname, (setter)Person_setname, "name", NULL },
	{ "surname", (getter)Person_getsurname, (setter)Person_setsurname, "surname", NULL },
	{ NULL }
};

static PyObject*
Person_data(Person *self) {
	return PyUnicode_FromFormat("%S %S %i", self->name, self->surname, self->age);
}

static PyMethodDef Person_methods[] = {
	{ "data", (PyCFunction)Person_data, METH_NOARGS, "Return name and surname and age" },
	{ NULL }
};

static PyTypeObject PersonType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"person.Person",             /* tp_name */
	sizeof(Person),             /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)Person_dealloc, /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_reserved */
	0,                         /* tp_repr */
	0,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,	   /* tp_flags */
	"Person objects",           /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	Person_methods,             /* tp_methods */
	Person_members,             /* tp_members */
	Person_getsetter,           /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)Person_init,      /* tp_init */
	0,                         /* tp_alloc */
	Person_new,                 /* tp_new */
};

static PyModuleDef personmodule = {
	PyModuleDef_HEAD_INIT,
	"Person",
	"Creating Person objects containing name, surname, age",
	-1,
	NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit_Person(void) {
	PyObject *m;

	if (PyType_Ready(&PersonType) < 0)
		return NULL;

	m = PyModule_Create(&personmodule);
	if (m == NULL)
		return NULL;

	Py_INCREF(&PersonType);
	PyModule_AddObject(m, "Person", (PyObject*)&PersonType);
	return m;
}
