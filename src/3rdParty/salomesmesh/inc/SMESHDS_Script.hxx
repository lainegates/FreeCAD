//  Copyright (C) 2007-2008  CEA/DEN, EDF R&D, OPEN CASCADE
//
//  Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
//  CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
//  See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//
//  SMESH SMESHDS : management of mesh data and SMESH document
//  File   : SMESHDS_Script.hxx
//  Module : SMESH
//
#ifndef _SMESHDS_Script_HeaderFile
#define _SMESHDS_Script_HeaderFile

#include "SMESH_SMESHDS.hxx"

#include "SMESHDS_Command.hxx"

#include <list>
#include <vector>


class SMESHDS_EXPORT SMESHDS_Script
{
  public:
	SMESHDS_Script(bool theIsEmbeddedMode);
	~SMESHDS_Script();
  
        void SetModified(bool theModified);
        bool IsModified();

	void AddNode(int NewNodeID, double x, double y, double z);
	void Add0DElement(int New0DElementID, int idnode);
	void AddEdge(int NewEdgeID, int idnode1, int idnode2);
	void AddFace(int NewFaceID, int idnode1, int idnode2, int idnode3);
	void AddFace(int NewFaceID, int idnode1, int idnode2, int idnode3,
  		int idnode4);
	void AddVolume(int NewVolID, int idnode1, int idnode2, int idnode3,
  		int idnode4);
	void AddVolume(int NewVolID, int idnode1, int idnode2, int idnode3,
  		int idnode4, int idnode5);
	void AddVolume(int NewVolID, int idnode1, int idnode2, int idnode3,
  		int idnode4, int idnode5, int idnode6);
	void AddVolume(int NewVolID, int idnode1, int idnode2, int idnode3,
  		int idnode4, int idnode5, int idnode6, int idnode7, int idnode8);

        void AddPolygonalFace (const int NewFaceID,
                               std::vector<int> nodes_ids);
	void AddPolyhedralVolume (const int NewVolID,
                                  std::vector<int> nodes_ids,
                                  std::vector<int> quantities);

        // special methods for quadratic elements
	void AddEdge(int NewEdgeID, int n1, int n2, int n12);
        void AddFace(int NewFaceID, int n1, int n2, int n3,
                     int n12, int n23, int n31);
        void AddFace(int NewFaceID, int n1, int n2, int n3, int n4,
                     int n12, int n23, int n34, int n41);
        void AddVolume(int NewVolID, int n1, int n2, int n3, int n4,
                       int n12, int n23, int n31, int n14, int n24, int n34);
        void AddVolume(int NewVolID, int n1, int n2, int n3, int n4, int n5,
                       int n12, int n23, int n34, int n41,
                       int n15, int n25, int n35, int n45);
        void AddVolume(int NewVolID, int n1, int n2, int n3,
                       int n4, int n5, int n6,
                       int n12, int n23, int n31,
                       int n45, int n56, int n64,
                       int n14, int n25, int n36);
        void AddVolume(int NewVolID, int n1, int n2, int n3, int n4,
                       int n5, int n6, int n7, int n8,
                       int n12, int n23, int n34, int n41,
                       int n56, int n67, int n78, int n85,
                       int n15, int n26, int n37, int n48);
        void MoveNode(int NewNodeID, double x, double y, double z);
	void RemoveNode(int NodeID);
	void RemoveElement(int ElementID);
	void ChangeElementNodes(int ElementID, int nodes[], int nbnodes);
	void ChangePolyhedronNodes(const int        ElementID,
                                   std::vector<int> nodes_ids,
                                   std::vector<int> quantities);
	void Renumber (const bool isNodes, const int startID, const int deltaID);
	void ClearMesh();
	void Clear();
	const std::list<SMESHDS_Command*> & GetCommands();

  private:
	SMESHDS_Command* getCommand(const SMESHDS_CommandType aType);

	std::list<SMESHDS_Command*> myCommands;

        bool myIsEmbeddedMode;
        bool myIsModified;
};

#endif
