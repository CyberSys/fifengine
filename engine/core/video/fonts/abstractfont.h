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

#ifndef FIFE_ABSTRACT_FONT_H
#define FIFE_ABSTRACT_FONT_H

// Standard C++ library includes
#include <string>

// Platform specific includes

// 3rd party library includes
#include <SDL.h>

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder

namespace FIFE {
	class Image;

	/** Pure abstract Font interface
	 */
	class AbstractFont {
	public:
		virtual ~AbstractFont() {}

		/**
		 * Sets the spacing between rows in pixels. Default is 0 pixels.
		 * The spacing can be negative.
		 *
		 * @param spacing the spacing in pixels.
		 */
		virtual void setRowSpacing (int spacing) = 0;

		/**
		 * Gets the spacing between rows in pixels.
		 *
		 * @return the spacing.
		 */
		virtual int getRowSpacing() const = 0;

		/**
		 * Sets the spacing between letters in pixels. Default is 0 pixels.
		 * The spacing can be negative.
		 *
		 * @param spacing the spacing in pixels.
		 */
		virtual void setGlyphSpacing(int spacing) = 0;

		/**
		 * Gets the spacing between letters in pixels.
		 *
		 * @return the spacing.
		 */
		virtual int getGlyphSpacing() const = 0;

		/**
		 * Sets the use of anti aliasing..
		 *
		 * @param antaAlias true for use of antia aliasing.
		 */
		virtual void setAntiAlias(bool antiAlias) = 0;

		/**
		 * Checks if anti aliasing is used.
		 *
		 * @return true if anti aliasing is used.
		 */
		virtual bool isAntiAlias() = 0;

		virtual int getStringIndexAt(const std::string &text, int x) = 0;

		/** Gets given text as Image
		 *  The rsulting image is pooled, so it's not that time critical
		 */
		virtual Image* getAsImage(const std::string& text) = 0;

		/** Set the color the text should be rendered in
		 */
		virtual void setColor(uint8_t r,uint8_t g,uint8_t b) = 0;

		/** Get the color the text was rendered in
		 */
		virtual SDL_Color getColor() const = 0;
		
		/** gets width of given text
		 */
		virtual int getWidth(const std::string& text) const = 0;
		
		/** gets height of this font
		 */
		virtual int getHeight() const = 0;
	};
}

#endif