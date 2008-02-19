/***************************************************************************
 *   Copyright (C) 2005-2008 by the FIFE team                              *
 *   http://www.fifengine.de                                               *
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

// 3rd party library includes

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "image_location.h"

namespace FIFE {
	ImageLocation::ImageLocation(const std::string& filename): 
		ResourceLocation(filename),
		m_xshift(0),
		m_yshift(0),
		m_width(0),
		m_height(0),
		m_parent_image(NULL) {
	}

	bool ImageLocation::operator ==(const ResourceLocation& loc) const {
		if (!ResourceLocation::operator==(loc)) {
			return false;
		}
		const ImageLocation* r = dynamic_cast<const ImageLocation*>(&loc);
		if (!r) {
			return true;
		}
		
		if (m_xshift != r->m_xshift) {
			return false;
		}
		if (m_yshift != r->m_yshift) {
			return false;
		}
		if (m_width != r->m_width) {
			return false;
		}
		if (m_height != r->m_height) {
			return false;
		}
		if (m_parent_image != r->m_parent_image) {
			return false;
		}
 		return true;
	}

	bool ImageLocation::operator <(const ResourceLocation& loc) const {
		if (!ResourceLocation::operator <(loc)) {
			return false;
		}

		const ImageLocation* r = dynamic_cast<const ImageLocation*>(&loc);
		if (m_xshift < r->m_xshift) {
			return false;
		}
		if (m_yshift < r->m_yshift) {
			return false;
		}
		if (m_width < r->m_width) {
			return false;
		}
		if (m_height < r->m_height) {
			return false;
		}
		if (m_parent_image < r->m_parent_image) {
			return false;
		}
 		return true;
	}

	ResourceLocation* ImageLocation::clone() const {
		ImageLocation* l = new ImageLocation(getFilename());
		l->m_xshift = m_xshift;
		l->m_yshift = m_yshift;
		l->m_width = m_width;
		l->m_height = m_height;
		l->m_parent_image = m_parent_image;
		return l;
	}

};//FIFE
/* vim: set noexpandtab: set shiftwidth=2: set tabstop=2: */
