/* -- THIS FILE IS GENERATED - DO NOT EDIT *//* -*- Mode: C; c-basic-offset: 4 -*- */

#include <Python.h>



#line 30 "appindicator.override"
#include <Python.h>
#include "../../src/app-indicator.h"
#include "../../src/app-indicator-enum-types.h"
#include <glib.h>
#include "pygobject.h"
#include "pyglib.h"
#include <pygtk/pygtk.h>

typedef PyObject* (*to_pyobject_func) (gpointer data);

#define APP_TYPE_INDICATOR APP_INDICATOR_TYPE

void
_appindicator_add_constants(PyObject *module, const gchar *strip_prefix)
{
#ifdef VERSION
        PyModule_AddStringConstant(module, "__version__", VERSION);
#endif
        pyg_enum_add(module,
                     "IndicatorCategory", 
                     strip_prefix,
                     APP_INDICATOR_TYPE_INDICATOR_CATEGORY);

        pyg_enum_add(module,
                     "IndicatorStatus", 
                     strip_prefix,
                     APP_INDICATOR_TYPE_INDICATOR_STATUS);

        if (PyErr_Occurred())
                PyErr_Print();
}
#line 40 "./appindicator.c"


/* ---------- types from other modules ---------- */
static PyTypeObject *_PyGObject_Type;
#define PyGObject_Type (*_PyGObject_Type)
static PyTypeObject *_PyGtkMenu_Type;
#define PyGtkMenu_Type (*_PyGtkMenu_Type)


/* ---------- forward type declarations ---------- */
PyTypeObject G_GNUC_INTERNAL PyAppIndicator_Type;

#line 53 "./appindicator.c"



/* ----------- AppIndicator ----------- */

static int
_wrap_app_indicator_new_with_path(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "id", "icon_name", "category", "icon_theme_path", NULL };
    char *id, *icon_name, *icon_theme_path = NULL;
    PyObject *py_category = NULL;
    AppIndicatorCategory category;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"ssO|z:App.Indicator.__init__", kwlist, &id, &icon_name, &py_category, &icon_theme_path))
        return -1;
    if (pyg_enum_get_value(APP_INDICATOR_TYPE_INDICATOR_CATEGORY, py_category, (gpointer)&category))
        return -1;
    self->obj = (GObject *)app_indicator_new_with_path(id, icon_name, category, icon_theme_path);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create AppIndicator object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_app_indicator_set_status(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "status", NULL };
    PyObject *py_status = NULL;
    AppIndicatorStatus status;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O:App.Indicator.set_status", kwlist, &py_status))
        return NULL;
    if (pyg_enum_get_value(APP_INDICATOR_TYPE_INDICATOR_STATUS, py_status, (gpointer)&status))
        return NULL;
    
    app_indicator_set_status(APP_INDICATOR(self->obj), status);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_set_attention_icon_full(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "icon_name", "icon_desc", NULL };
    char *icon_name, *icon_desc = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|z:App.Indicator.set_attention_icon", kwlist, &icon_name, &icon_desc))
        return NULL;
    
    app_indicator_set_attention_icon_full(APP_INDICATOR(self->obj), icon_name, icon_desc);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_set_menu(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "menu", NULL };
    PyGObject *menu;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"O!:App.Indicator.set_menu", kwlist, &PyGtkMenu_Type, &menu))
        return NULL;
    
    app_indicator_set_menu(APP_INDICATOR(self->obj), GTK_MENU(menu->obj));
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_set_icon_full(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "icon_name", "icon_desc", NULL };
    char *icon_name, *icon_desc = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"s|z:App.Indicator.set_icon", kwlist, &icon_name, &icon_desc))
        return NULL;
    
    app_indicator_set_icon_full(APP_INDICATOR(self->obj), icon_name, icon_desc);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_set_label(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "label", "guide", NULL };
    char *label, *guide = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"z|z:App.Indicator.set_label", kwlist, &label, &guide))
        return NULL;
    
    app_indicator_set_label(APP_INDICATOR(self->obj), label, guide);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_set_ordering_index(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "ordering_index", NULL };
    unsigned long ordering_index;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"k:App.Indicator.set_ordering_index", kwlist, &ordering_index))
        return NULL;
    
    app_indicator_set_ordering_index(APP_INDICATOR(self->obj), ordering_index);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_set_icon_theme_path(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "icon_theme_path", NULL };
    char *icon_theme_path;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"z:App.Indicator.set_icon_theme_path", kwlist, &icon_theme_path))
        return NULL;
    
    app_indicator_set_icon_theme_path(APP_INDICATOR(self->obj), icon_theme_path);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_get_id(PyGObject *self)
{
    const gchar *ret;

    
    ret = app_indicator_get_id(APP_INDICATOR(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_get_category(PyGObject *self)
{
    gint ret;

    
    ret = app_indicator_get_category(APP_INDICATOR(self->obj));
    
    return pyg_enum_from_gtype(APP_INDICATOR_TYPE_INDICATOR_CATEGORY, ret);
}

static PyObject *
_wrap_app_indicator_get_status(PyGObject *self)
{
    gint ret;

    
    ret = app_indicator_get_status(APP_INDICATOR(self->obj));
    
    return pyg_enum_from_gtype(APP_INDICATOR_TYPE_INDICATOR_STATUS, ret);
}

static PyObject *
_wrap_app_indicator_get_icon(PyGObject *self)
{
    const gchar *ret;

    
    ret = app_indicator_get_icon(APP_INDICATOR(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_get_icon_desc(PyGObject *self)
{
    const gchar *ret;

    
    ret = app_indicator_get_icon_desc(APP_INDICATOR(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_get_icon_theme_path(PyGObject *self)
{
    const gchar *ret;

    
    ret = app_indicator_get_icon_theme_path(APP_INDICATOR(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_get_attention_icon(PyGObject *self)
{
    const gchar *ret;

    
    ret = app_indicator_get_attention_icon(APP_INDICATOR(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_get_attention_icon_desc(PyGObject *self)
{
    const gchar *ret;

    
    ret = app_indicator_get_attention_icon_desc(APP_INDICATOR(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_get_menu(PyGObject *self)
{
    GtkMenu *ret;

    
    ret = app_indicator_get_menu(APP_INDICATOR(self->obj));
    
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_app_indicator_get_label(PyGObject *self)
{
    const gchar *ret;

    
    ret = app_indicator_get_label(APP_INDICATOR(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_get_label_guide(PyGObject *self)
{
    const gchar *ret;

    
    ret = app_indicator_get_label_guide(APP_INDICATOR(self->obj));
    
    if (ret)
        return PyString_FromString(ret);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_app_indicator_get_ordering_index(PyGObject *self)
{
    guint32 ret;

    
    ret = app_indicator_get_ordering_index(APP_INDICATOR(self->obj));
    
    return PyLong_FromUnsignedLong(ret);

}

static PyObject *
_wrap_app_indicator_build_menu_from_desktop(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "desktop_file", "desktop_profile", NULL };
    char *desktop_file, *desktop_profile;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,"ss:App.Indicator.build_menu_from_desktop", kwlist, &desktop_file, &desktop_profile))
        return NULL;
    
    app_indicator_build_menu_from_desktop(APP_INDICATOR(self->obj), desktop_file, desktop_profile);
    
    Py_INCREF(Py_None);
    return Py_None;
}

static const PyMethodDef _PyAppIndicator_methods[] = {
    { "set_status", (PyCFunction)_wrap_app_indicator_set_status, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_attention_icon", (PyCFunction)_wrap_app_indicator_set_attention_icon_full, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_menu", (PyCFunction)_wrap_app_indicator_set_menu, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_icon", (PyCFunction)_wrap_app_indicator_set_icon_full, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_label", (PyCFunction)_wrap_app_indicator_set_label, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_ordering_index", (PyCFunction)_wrap_app_indicator_set_ordering_index, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "set_icon_theme_path", (PyCFunction)_wrap_app_indicator_set_icon_theme_path, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { "get_id", (PyCFunction)_wrap_app_indicator_get_id, METH_NOARGS,
      NULL },
    { "get_category", (PyCFunction)_wrap_app_indicator_get_category, METH_NOARGS,
      NULL },
    { "get_status", (PyCFunction)_wrap_app_indicator_get_status, METH_NOARGS,
      NULL },
    { "get_icon", (PyCFunction)_wrap_app_indicator_get_icon, METH_NOARGS,
      NULL },
    { "get_icon_desc", (PyCFunction)_wrap_app_indicator_get_icon_desc, METH_NOARGS,
      NULL },
    { "get_icon_theme_path", (PyCFunction)_wrap_app_indicator_get_icon_theme_path, METH_NOARGS,
      NULL },
    { "get_attention_icon", (PyCFunction)_wrap_app_indicator_get_attention_icon, METH_NOARGS,
      NULL },
    { "get_attention_icon_desc", (PyCFunction)_wrap_app_indicator_get_attention_icon_desc, METH_NOARGS,
      NULL },
    { "get_menu", (PyCFunction)_wrap_app_indicator_get_menu, METH_NOARGS,
      NULL },
    { "get_label", (PyCFunction)_wrap_app_indicator_get_label, METH_NOARGS,
      NULL },
    { "get_label_guide", (PyCFunction)_wrap_app_indicator_get_label_guide, METH_NOARGS,
      NULL },
    { "get_ordering_index", (PyCFunction)_wrap_app_indicator_get_ordering_index, METH_NOARGS,
      NULL },
    { "build_menu_from_desktop", (PyCFunction)_wrap_app_indicator_build_menu_from_desktop, METH_VARARGS|METH_KEYWORDS,
      NULL },
    { NULL, NULL, 0, NULL }
};

PyTypeObject G_GNUC_INTERNAL PyAppIndicator_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                 /* ob_size */
    "appindicator.Indicator",                   /* tp_name */
    sizeof(PyGObject),          /* tp_basicsize */
    0,                                 /* tp_itemsize */
    /* methods */
    (destructor)0,        /* tp_dealloc */
    (printfunc)0,                      /* tp_print */
    (getattrfunc)0,       /* tp_getattr */
    (setattrfunc)0,       /* tp_setattr */
    (cmpfunc)0,           /* tp_compare */
    (reprfunc)0,             /* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,             /* tp_hash */
    (ternaryfunc)0,          /* tp_call */
    (reprfunc)0,              /* tp_str */
    (getattrofunc)0,     /* tp_getattro */
    (setattrofunc)0,     /* tp_setattro */
    (PyBufferProcs*)0,  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL,                        /* Documentation string */
    (traverseproc)0,     /* tp_traverse */
    (inquiry)0,             /* tp_clear */
    (richcmpfunc)0,   /* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,          /* tp_iter */
    (iternextfunc)0,     /* tp_iternext */
    (struct PyMethodDef*)_PyAppIndicator_methods, /* tp_methods */
    (struct PyMemberDef*)0,              /* tp_members */
    (struct PyGetSetDef*)0,  /* tp_getset */
    NULL,                              /* tp_base */
    NULL,                              /* tp_dict */
    (descrgetfunc)0,    /* tp_descr_get */
    (descrsetfunc)0,    /* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_app_indicator_new_with_path,             /* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- functions ----------- */

static PyObject *
_wrap_app_indicator_get_type(PyObject *self)
{
    GType ret;

    
    ret = app_indicator_get_type();
    
    return pyg_type_wrapper_new(ret);
}

const PyMethodDef pyappindicator_functions[] = {
    { "app_indicator_get_type", (PyCFunction)_wrap_app_indicator_get_type, METH_NOARGS,
      NULL },
    { NULL, NULL, 0, NULL }
};


/* ----------- enums and flags ----------- */

void
pyappindicator_add_constants(PyObject *module, const gchar *strip_prefix)
{
#ifdef VERSION
    PyModule_AddStringConstant(module, "__version__", VERSION);
#endif
  pyg_enum_add(module, "IndicatorCategory", strip_prefix, APP_INDICATOR_TYPE_INDICATOR_CATEGORY);
  pyg_enum_add(module, "IndicatorStatus", strip_prefix, APP_INDICATOR_TYPE_INDICATOR_STATUS);

  if (PyErr_Occurred())
    PyErr_Print();
}

/* initialise stuff extension classes */
void
pyappindicator_register_classes(PyObject *d)
{
    PyObject *module;

    if ((module = PyImport_ImportModule("gobject")) != NULL) {
        _PyGObject_Type = (PyTypeObject *)PyObject_GetAttrString(module, "GObject");
        if (_PyGObject_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name GObject from gobject");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gobject");
        return ;
    }
    if ((module = PyImport_ImportModule("gtk")) != NULL) {
        _PyGtkMenu_Type = (PyTypeObject *)PyObject_GetAttrString(module, "Menu");
        if (_PyGtkMenu_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Menu from gtk");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk");
        return ;
    }


#line 520 "./appindicator.c"
    pygobject_register_class(d, "AppIndicator", APP_TYPE_INDICATOR, &PyAppIndicator_Type, Py_BuildValue("(O)", &PyGObject_Type));
}
