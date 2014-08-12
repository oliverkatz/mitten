/******************************************************************************
 *                                 _ _   _                                    *
 *                           /\/\ (_) |_| |_ ___ _ __                         *
 *                          /    \| | __| __/ _ \ '_ \                        *
 *                         / /\/\ \ | |_| ||  __/ | | |                       *
 *                         \/    \/_|\__|\__\___|_| |_|                       *
 *                                                                            *
 ******************************************************************************/

/*
 * Copyright (c) 2014, Oliver Katz
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "PostScriptDocumentParser.h"

using namespace std;

namespace mitten
{
	void PostScriptDocumentParser::onTitle(string t)
	{
		header += "%%Title: "+t+"\n";

		titles += "% Document Title\n";
		titles += "/Avenir-Book findfont\n";
		titles += "48 scalefont\n";
		titles += "setfont\n";
		titles += "newpath\n";
		titles += to_string(100)+" "+to_string(height-95)+" moveto\n";
		titles += "0 0 0 setrgbcolor\n";
		titles += "("+t+") show\n";
		titles += "newpath\n";
		titles += to_string(100)+" "+to_string(height-105)+" moveto\n";
		titles += to_string(500)+" "+to_string(height-105)+" lineto\n";
		titles += "closepath\n";
		titles += "0.8 0.2 0.2 setrgbcolor\n";
		titles += "4 setlinewidth\n";
		titles += "stroke\n";
		titles += "\n";
	}

	void PostScriptDocumentParser::onSubtitle(string t)
	{
		titles += "% Document Subtitle\n";
		titles += "/Avenir-Book findfont\n";
		titles += "24 scalefont\n";
		titles += "setfont\n";
		titles += "newpath\n";
		titles += to_string(120)+" "+to_string(height-130)+" moveto\n";
		titles += "0 0 0 setrgbcolor\n";
		titles += "("+t+") show\n";
	}

	void PostScriptDocumentParser::onAuthor(string a)
	{
		header += "%%Creator: "+a+"\n";

		titles += "% Document Author\n";
		titles += "/Avenir-Book findfont\n";
		titles += "18 scalefont\n";
		titles += "setfont\n";
		titles += "newpath\n";
		titles += to_string(120)+" "+to_string(height-200)+" moveto\n";
		titles += "0 0 0 setrgbcolor\n";
		titles += "("+a+") show\n";
	}

	void PostScriptDocumentParser::onDate(string d)
	{
		header += "%%CreationDate: "+d+"\n";

		titles += "% Document Author\n";
		titles += "/Avenir-Book findfont\n";
		titles += "18 scalefont\n";
		titles += "setfont\n";
		titles += "newpath\n";
		titles += to_string(120)+" "+to_string(height-235)+" moveto\n";
		titles += "0 0 0 setrgbcolor\n";
		titles += "("+d+") show\n";
	}

	PostScriptDocumentParser::PostScriptDocumentParser()
	{
		width = 595;
		height = 842;

		header = "%!PS-Adobe-3.0 EPSF-3.0\n";
		header += "%%BoundingBox: 0 0 "+to_string(width)+" "+to_string(height)+"\n";
		header += "%%LanguageLevel: 2\n";

		titles = "% Titles and Document Info\n";
		titles += "newpath\n";
		titles += to_string(20)+" "+to_string(height-20)+" moveto\n";
		titles += to_string(width-40)+" "+to_string(height-20)+" lineto\n";
		titles += "closepath\n";
		titles += "0.8 0.2 0.2 setrgbcolor\n";
		titles += "2 setlinewidth\n";
		titles += "stroke\n";
		titles += "newpath\n";
		titles += to_string(20)+" "+to_string(20)+" moveto\n";
		titles += to_string(width-40)+" "+to_string(20)+" lineto\n";
		titles += "closepath\n";
		titles += "0.8 0.2 0.2 setrgbcolor\n";
		titles += "2 setlinewidth\n";
		titles += "stroke\n\n";
		
		toc = "% Table of Contents\n";
		toc += "/Avenir-Book findfont\n";
		toc += "24 scalefont\n";
		toc += "setfont\n";
		toc += "newpath\n";
		toc += to_string(100)+" "+to_string(height-100)+" moveto\n";
		toc += "0 0 0 setrgbcolor\n";
		toc += "(Table of Contents) show\n";
		toc += "newpath\n";
		toc += to_string(20)+" "+to_string(height-20)+" moveto\n";
		toc += to_string(width-40)+" "+to_string(height-20)+" lineto\n";
		toc += "closepath\n";
		toc += "0.8 0.2 0.2 setrgbcolor\n";
		toc += "2 setlinewidth\n";
		toc += "stroke\n";
		toc += "newpath\n";
		toc += to_string(20)+" "+to_string(20)+" moveto\n";
		toc += to_string(width-40)+" "+to_string(20)+" lineto\n";
		toc += "closepath\n";
		toc += "0.8 0.2 0.2 setrgbcolor\n";
		toc += "2 setlinewidth\n";
		toc += "stroke\n\n";

		document = "";
	}

	string PostScriptDocumentParser::dumpPS()
	{
		return header+"%%EndComments\n\n"+titles+"\nshowpage\n"+toc+"\nshowpage\n"+document+"\nshowpage\n";
	}
}
