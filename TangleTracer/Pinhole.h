// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This file contains the declaration of the class Pinhole

#pragma once

#include "Point2D.h"
#include "World.h"    // we can #include "World.h" here

//--------------------------------------------------------------------- class Pinhole

class Pinhole: public Camera {
	public:
	
		Pinhole();   							

		Pinhole(const Pinhole& ph);	
		
		virtual Camera*						
		clone(void) const;			

		Pinhole& 							
		operator= (const Pinhole& rhs);	
		
		virtual
		~Pinhole();   						
			
		void
		set_view_distance(const float vpd);

		void
		set_vpd(const float vpd);		// This function is used initially from 14.21
		
		void
		set_zoom(const float zoom_factor);
		
		Vector3D								
		get_direction(const Point2D& p) const;
		
		virtual void 												
		render_scene(World& w);
		
		void
		render_stereo(World& w, float x, int pixel_offset);
	private:
			
		float	d;		// view plane distance
		float	zoom;	// zoom factor
		
};




//-------------------------------------------------------------------------- set_vpd

inline void
Pinhole::set_view_distance(float _d) {
	d = _d;
}	

//-------------------------------------------------------------------------- set_vpd

inline void
Pinhole::set_vpd(float _d) {
	d = _d;
}	
	


//-------------------------------------------------------------------------- set_zoom

inline void
Pinhole::set_zoom(float zoom_factor) {
	zoom = zoom_factor;
}	
