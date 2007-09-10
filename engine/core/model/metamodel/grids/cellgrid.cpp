/***************************************************************************
 *   Copyright (C) 2005-2007 by the FIFE Team                              *
 *   fife-public@lists.sourceforge.net                                     *
 *   This file is part of FIFE.                                            *
 *                                                                         *
 *   FIFE is free software; you can redistribute it and/or modify          *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
 ***************************************************************************/

// Standard C++ library includes
#include <assert.h>

// 3rd party library includes

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "cellgrid.h"

namespace FIFE {
	CellGrid::CellGrid():
		m_matrix(),
		m_inverse_matrix(),
		m_xshift(0),
		m_yshift(0),
		m_scale(1),
		m_rotation(0) {
		updateMatrices();
	}

	CellGrid::~CellGrid() {
	}

	void CellGrid::getAccessibleCoordinates(const Point& curpos, std::vector<Point>& coordinates) {
		coordinates.clear();
		for (int x = curpos.x - 1; x <= curpos.x + 1; x++) {
			for (int y = curpos.y - 1; y <= curpos.y + 1; y++) {
				Point pt;
				pt.x = x;
				pt.y = y;
				if (isAccessible(curpos, pt)) {
					coordinates.push_back(pt);
				}
			}
		}
	}

	void CellGrid::updateMatrices() {
		double s = 1/m_scale;
		m_matrix.loadScale(s, s, s);
		m_matrix.applyRotate(m_rotation, 0.0, 0.0, 1.0);
		m_matrix.applyTranslate(-m_xshift, -m_yshift, 0);
		m_inverse_matrix = m_matrix.inverse();
	}

	DoublePoint CellGrid::toElevationCoordinates(const Point& layer_coords) {
		return toElevationCoordinates(intPt2doublePt(layer_coords));
	}
	
	int CellGrid::orientation(const DoublePoint& pt, const DoublePoint& pt1, const DoublePoint& pt2) {
		double o = (pt2.x - pt1.x) * (pt.y - pt1.y) - (pt.x - pt1.x) * (pt2.y - pt1.y);
		if (o > 0.0) {
			return 1;
		} else if (o < 0.0) {
			return -1;
		}
		return 0;
	}
	
	bool CellGrid::ptInTriangle(const DoublePoint& pt, const DoublePoint& pt1, const DoublePoint& pt2, const DoublePoint& pt3) {
		double o1 = orientation(pt1, pt2, pt);
		double o2 = orientation(pt2, pt3, pt);
		double o3 = orientation(pt3, pt1, pt);
		return (o1 == o2) && (o2 == o3);
	}
}
