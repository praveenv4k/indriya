#include "stdafx.h"
#include "resource.h"
#include "Signature.h"

using namespace Eyw;

static catalog_class_registrant gCatalog( 
	catalog_class_registrant::catalog_id( EYW_EXPHRIMOT_CATALOG_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "ExPhriMot Catalog" )
			.description( "This is the signature module for all the blocks and datatypes developed for ExPhriMot Project" )
			.bitmap( IDB_EXPHRIMOT_CATALOG )
		.end_language()	
	);

static company_registrant gCompany( 
	company_registrant::company_id( EYW_EXPHRIMOT_COMPANY_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "GVLab" )
			.description( "Head: Prof.Gentiane VENTURE\n"
						  "Tokyo University of Agriculture and Technology\n" 
						  "Department of Mechanical Systems Engineering\n"
						  "2-24-16 Nakacho Koganei-shi 184-8588 Tokyo - Japan\n"
						  "Focus Areas: Robotics & Control, Human Motion analysis and Human Robot Interaction" )
		.end_language()	
	);

static licence_registrant gLicense( 
	licence_registrant::licence_id( EYW_EXPHRIMOT_LICENSE_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "MIT-like license" )
			.description( "Copyright (c) 2015 Praveenkumar VASUDEVAN\n"
				"Permission is hereby granted, free of charge, to any person obtaining a copy "
					"of this software and associated documentation files (the \"Software\"), to "
					"deal in the Software without restriction, including without limitation the "
					"rights to use, copy, modify, merge, publish, distribute, sublicense, and/or "
					"sell copies of the Software, and to permit persons to whom the Software is "
					"furnished to do so, subject to the following conditions:\n\n"
				"The above copyright notice and this permission notice shall be included in all "
					"copies or substantial portions of the Software.\n\n"
				"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
					"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
					"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL "
					"THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
					"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, "
					"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE "
					"SOFTWARE." )
		.end_language()	
	);

static author_registrant gAuthor( 
	author_registrant::author_id( EYW_EXPHRIMOT_CATALOG_AUTHOR_ID )
		.begin_language( EYW_LANGUAGE_US_ENGLISH )
			.name( "Praveenkumar VASUDEVAN" )
			.description( 
			    "Graduate Student - European Master in Advanced Robotics\n"
				"University of Genova/Ecole Centrale de Nantes/GVLab\n"
			    "email: praveenv4k@gmail.com" )
		.end_language()	
	);


