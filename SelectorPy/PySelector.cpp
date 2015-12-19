// PySelector.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
Selector *sel;
extern "C"
{
	static PyObject *init_selector(PyObject *self, PyObject *args)
	{
		sel = new Selector;
		return Py_BuildValue("i",1);
	}
	static PyObject *select(PyObject *self, PyObject *args)
	{
		int x = 0;
		if (!PyArg_ParseTuple(args,"i",&x))
		{
			return NULL;
		}
		Selector &selector = *sel;
		Info item = selector.sequence_read(x);
		char id[20], ads_id[20], pos_id[20], ip_id[20];
		item.id.c_str(id);
		item.ads_id.c_str(ads_id);
		item.pos_id.c_str(pos_id);
		item.ip_id.c_str(ip_id);
		return Py_BuildValue("ssssisLii", id, ads_id, pos_id, ip_id, item.lang
			, item.OS_info, item.timeStamp, item.stable, item.click);
	}
	static PyObject *sel_close(PyObject *self, PyObject *args)
	{
		delete sel;
		cout << "closed" << endl;
		return Py_BuildValue("i", 1);
	}

	static PyMethodDef selMethods[]=
	{
		{"init",(PyCFunction)init_selector,METH_VARARGS,"open"},
		{"select",(PyCFunction)select,METH_VARARGS,"select(int i)"},
		{"close",(PyCFunction)sel_close,METH_VARARGS,"close"},
		{NULL,NULL,0,NULL}
	};

	PyMODINIT_FUNC initselector()
	{
		Py_InitModule("selector", selMethods);
	}

}

