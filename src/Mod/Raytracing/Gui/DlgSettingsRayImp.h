/***************************************************************************
 *   Copyright (c) 2002 J�rgen Riegel <juergen.riegel@web.de>              *
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


#ifndef RAYTRACINGGUI_DLGSETTINGSRAYIMP_H
#define RAYTRACINGGUI_DLGSETTINGSRAYIMP_H

#include "ui_DlgSettingsRay.h"
#include <Gui/PropertyPage.h>

namespace RaytracingGui {

/**
 * The DlgSettings3DViewImp class implements a preference page to change settings
 * for the Inventor viewer.
 * \author J�rgen Riegel
 */
class DlgSettingsRayImp : public Gui::Dialog::PreferencePage, public Ui_DlgSettingsRay
{
    Q_OBJECT

public:
    DlgSettingsRayImp( QWidget* parent = 0 );
    ~DlgSettingsRayImp();

protected:
    void saveSettings();
    void loadSettings();
    void changeEvent(QEvent *e);
};

} // namespace RaytracingGui

#endif // RAYTRACINGGUI_DLGSETTINGSRAYIMP_H
