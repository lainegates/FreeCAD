/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#include "PreCompiled.h"
#ifndef _PreComp_
# include <gp_Circ.hxx>
# include <Geom_Circle.hxx>
# include <gp_Elips.hxx>
# include <Geom_Ellipse.hxx>
# include <Geom_TrimmedCurve.hxx>
# include <GC_MakeArcOfCircle.hxx>
# include <GC_MakeArcOfEllipse.hxx>
#endif

#include "ArcPy.h"
#include "ArcPy.cpp"
#include "CirclePy.h"
#include "EllipsePy.h"

#include <Base/VectorPy.h>
#include <Base/GeometryPyCXX.h>

using namespace Part;

extern const char* gce_ErrorStatusText(gce_ErrorType et);

// returns a string which represents the object e.g. when printed in python
std::string ArcPy::representation(void) const
{
    return "<Arc object>";
}

PyObject *ArcPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // never create such objects with the constructor
    return new ArcPy(new GeomTrimmedCurve());
}

// constructor method
int ArcPy::PyInit(PyObject* args, PyObject* /*kwd*/)
{
    PyObject* o;
    double u1, u2;
    int sense=1;
    if (PyArg_ParseTuple(args, "O!dd|i", &(Part::CirclePy::Type), &o, &u1, &u2, &sense)) {
        try {
            Handle_Geom_Circle circle = Handle_Geom_Circle::DownCast
                (static_cast<CirclePy*>(o)->getGeomCirclePtr()->handle());
            GC_MakeArcOfCircle arc(circle->Circ(), u1, u2, sense);
            if (!arc.IsDone()) {
                PyErr_SetString(PyExc_Exception, gce_ErrorStatusText(arc.Status()));
                return -1;
            }

            getGeomTrimmedCurvePtr()->setHandle(arc.Value());
            return 0;
        }
        catch (Standard_Failure) {
            Handle_Standard_Failure e = Standard_Failure::Caught();
            PyErr_SetString(PyExc_Exception, e->GetMessageString());
            return -1;
        }
        catch (...) {
            PyErr_SetString(PyExc_Exception, "creation of arc failed");
            return -1;
        }
    }

    PyErr_Clear();
    PyObject *pV1, *pV2, *pV3;
    if (PyArg_ParseTuple(args, "O!O!O!", &(Base::VectorPy::Type), &pV1,
                                         &(Base::VectorPy::Type), &pV2,
                                         &(Base::VectorPy::Type), &pV3)) {
        Base::Vector3d v1 = static_cast<Base::VectorPy*>(pV1)->value();
        Base::Vector3d v2 = static_cast<Base::VectorPy*>(pV2)->value();
        Base::Vector3d v3 = static_cast<Base::VectorPy*>(pV3)->value();

        GC_MakeArcOfCircle arc(gp_Pnt(v1.x,v1.y,v1.z),
                               gp_Pnt(v2.x,v2.y,v2.z),
                               gp_Pnt(v3.x,v3.y,v3.z));
        if (!arc.IsDone()) {
            PyErr_SetString(PyExc_Exception, gce_ErrorStatusText(arc.Status()));
            return -1;
        }

        getGeomTrimmedCurvePtr()->setHandle(arc.Value());
        return 0;
    }

    PyErr_Clear();
    if (PyArg_ParseTuple(args, "O!dd|i", &(Part::EllipsePy::Type), &o, &u1, &u2, &sense)) {
        try {
            Handle_Geom_Ellipse ellipse = Handle_Geom_Ellipse::DownCast
                (static_cast<EllipsePy*>(o)->getGeomEllipsePtr()->handle());
            GC_MakeArcOfEllipse arc(ellipse->Elips(), u1, u2, sense);
            if (!arc.IsDone()) {
                PyErr_SetString(PyExc_Exception, gce_ErrorStatusText(arc.Status()));
                return -1;
            }

            getGeomTrimmedCurvePtr()->setHandle(arc.Value());
            return 0;
        }
        catch (Standard_Failure) {
            Handle_Standard_Failure e = Standard_Failure::Caught();
            PyErr_SetString(PyExc_Exception, e->GetMessageString());
            return -1;
        }
        catch (...) {
            PyErr_SetString(PyExc_Exception, "creation of arc failed");
            return -1;
        }
    }

    // All checks failed
    PyErr_SetString(PyExc_TypeError, "Arc constructor expects a conic curve and a parameter range");
    return -1;
}

PyObject *ArcPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int ArcPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}
