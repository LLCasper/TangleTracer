// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "stdafx.h"
#include "Sampler.h"
#include "RGBColor.h"
#include "Light.h"

class AmbientOccluder: public Light {
	public:
	
		AmbientOccluder(void); 

		AmbientOccluder(const AmbientOccluder& a); 					 
	
		virtual Light* 									
		clone(void) const;	
		
		AmbientOccluder& 									
		operator= (const AmbientOccluder& rhs);									
		
		virtual 									
		~AmbientOccluder(void);
				
		void
		scale_radiance(const float b);
		
		void
		set_color(const float c);
		
		void
		set_color(const RGBColor& c);
		
		void
		set_color(const float r, const float g, const float b); 

		void
		set_sampler(Sampler* s_ptr);

		void
		set_min_amount(float m);
	
		virtual Vector3D						
		get_direction(ShadeRec& sr);
	
		virtual bool									
		in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
		virtual RGBColor
		L(ShadeRec& sr);
	
	private:
	
		float		ls;
		RGBColor	color;
		float 		min_amount;	    
		Vector3D 	u, v, w;		
		Sampler*	sampler_ptr;
};

// ------------------------------------------------------------------------------- scale_radiance

inline void
AmbientOccluder::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const RGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
AmbientOccluder::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

//

inline void
AmbientOccluder::set_min_amount(float m)
{
	this->min_amount = m;
}