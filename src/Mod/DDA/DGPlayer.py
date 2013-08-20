#***************************************************************************
#*                                                                         *
#*   Copyright (c) 2009, 2010                                              *  
#*   Xiaolong Cheng <lainegates@163.com>                                   *  
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU Lesser General Public License (LGPL)    *
#*   as published by the Free Software Foundation; either version 2 of     *
#*   the License, or (at your option) any later version.                   *
#*   for detail see the LICENCE text file.                                 *
#*                                                                         *
#*   This program is distributed in the hope that it will be useful,       *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU Library General Public License for more details.                  *
#*                                                                         *
#*   You should have received a copy of the GNU Library General Public     *
#*   License along with this program; if not, write to the Free Software   *
#*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
#*   USA                                                                   *
#*                                                                         *
#***************************************************************************


import os
import time
import FreeCADGui

class DGPlayer:
    def GetResources(self):
        return {
#                'Pixmap'  : 'Test1',
                'MenuText':  'PlayDF',
                'ToolTip': "play animation of DF ."
        }
                
    def Activated(self, name="None"):
        path = os.getcwd()
        import Base
        os.chdir(Base.__workbenchPath__)
        import DDAGui
        FreeCADGui.runCommand("DDA_Test")  # it is in DDAGui.pyd
        os.chdir(path)

FreeCADGui.addCommand('PlayDF', DGPlayer())