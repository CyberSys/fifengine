#!/usr/bin/env python
# -*- coding: utf-8 -*-

# ####################################################################
#  Copyright (C) 2005-2009 by the FIFE team
#  http://www.fifengine.de
#  This file is part of FIFE.
#
#  FIFE is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the
#  Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
# ####################################################################

from swig_test_utils import *

class TestVideo(unittest.TestCase):
	
	def setUp(self):
		self.engine = getEngine()
		
	def tearDown(self):
		self.engine.destroy()

	def testDrawLine(self):
		points = (
			(1,1), (50,20), (20,50), (200,500), (500,200), (100,200),
			(10,10), (70,40), (80,30), (300,520), (340,220), (170,600),
		)
		self.engine.initializePumping()
		
		be = self.engine.getRenderBackend()
		
		clipb = fife.Rect(0,0, be.getWidth(), be.getHeight())
		
		be.pushClipArea(clipb, False)
		self.engine.getSettings().setBackBufferClearing(False)

		for i in xrange(200):
			prevPt = fife.Point(*points[1])
			for pt in points[1:]:
				curPt = fife.Point(*pt)
				be.drawLine(prevPt, curPt, 255, 255, 255)
				prevPt = curPt
			self.engine.pump()
			be.renderVertexArrays()

		be.popClipArea()

		self.engine.finalizePumping()
	

TEST_CLASSES = [TestVideo]

if __name__ == '__main__':
    unittest.main()

