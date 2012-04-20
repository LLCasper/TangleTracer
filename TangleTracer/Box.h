#pragma once

#include "GeometricObject.h"
#include "Normal.h"


#include "Point3D.h"

//-------------------------------------------------------------------- class Box

class Box: public GeometricObject {
	
	public:
	
		Box(void);   												// default constructor									
						
		Box(	const double x0, const double x1,			
				const double y0, const double y1, 
				const double z0, const double z1);

		Box(const Point3D p0, const Point3D p1);				
	
		Box(const Box& Box); 									// copy constructor
		
		virtual Box* 												// virtual copy constructor
		clone(void) const;

		Box& 														// assignment operator
		operator= (const Box& rhs);	
		
		virtual														// destructor
		~Box(void);   											
					
		virtual bool 																								 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		bool shadow_hit(const Ray& ray, float& tmin) const;
		
		Normal	
		Box::get_normal(const int face_hit) const;

	private:

		double x0, x1, y0, y1, z0, z1;
				
		static const double kEpsilon;   // for shadows and secondary rays
};
