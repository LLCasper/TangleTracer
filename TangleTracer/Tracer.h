// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#pragma once

#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"

class World;

class Tracer {
	public:
	
		Tracer(void);									
		
		Tracer(World* _world_ptr);						
				
		virtual											
		~Tracer(void);									

		virtual RGBColor	
		trace_ray(const Ray& ray) const;

		virtual RGBColor	
		trace_ray(const Ray ray, const int depth) const;

		virtual RGBColor	
		trace_ray(const Ray ray, double &t, const int depth) const;
				
	protected:
	
		World* world_ptr;
};
