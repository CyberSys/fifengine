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
#include <algorithm>

// 3rd party library includes
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <zlib.h>

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "vfs/raw/rawdata.h"
#include "vfs/vfs.h"
#include "util/exception.h"

#include "rawdatadat2.h"

namespace FIFE {

	RawDataDAT2::RawDataDAT2(const std::string& datfile, const s_info& info) :
		RawDataMemSource(info.unpackedLength) {

		boost::scoped_ptr<RawData> input (VFS::instance()->open(datfile));
		input->setIndex(info.offset);

		if (info.type == 1) { // compressed
			boost::scoped_array<uint8_t> compressed(new uint8_t[info.packedLength]);
			input->readInto(compressed.get(), info.packedLength);

			uLongf dstlen = info.unpackedLength;
			if (uncompress(getRawData(), &dstlen, compressed.get(), info.packedLength) != Z_OK || dstlen != info.unpackedLength) {
				throw InvalidFormat("failed to decompress " + info.name + " (inside: " + datfile + ")");
			}
		} else {
			input->readInto(getRawData(), info.unpackedLength);
		}
	}

}
